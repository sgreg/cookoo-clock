/*
 * cook'oo clock - the smack-'n-go reverse kitchen timer
 *
 * Copyright (C) 2020 Sven Gregori <sven@craplab.fi>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * ATtiny85 pinout usage
 *
 * /RESET 1     8 VCC
 *  XTAL1 2     7 OLED SCK
 *  XTAL2 3     6 PB1 (unused)
 *    GND 4     5 OLED SDA
 */

#include <string.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>

#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>

#include "clock.h"
#include "font8x16clock.h"
#include "font24x48clock.h"

/**
 * Power saving mode.
 *
 * Set to 1 to power down the device after long period of idle.
 * Set to 0 to keep running for all eternity.
 */
#define POWER_SAVING 0

/**
 * If power saving mode is enabled (POWER_SAVING == 1), number of minutes
 * after which the clock will power down.
 *
 * Note that the counter itself will reset from 99:99 back to 00:00, so
 * values over 99 minutes will be ignored / never occur. To power down
 * after exactly 100 minutes, set the value here to 0, as the check is
 * performed while updating the minutes in increment_time().
 */
#define POWER_DOWN_MINUTES 60


/**
 * Struct to store the counted time.
 *
 * Stored in .noinit section so value can be retained during external reset
 * and displayed as last counted time.
 */
static clock_time_t clock_time __attribute__((section(".noinit")));
/** Struct to store which digits have changed in the last time increment */
static clock_time_t clock_time_changes;

/** Indicate the timer interrupt happened and another second has passed */
static volatile uint8_t timer_triggered;

/** Store MCU status register (MCSRU) value after reset */
static volatile uint8_t mcusr;
/** Check if last reset was power-on reset */
#define is_power_on_reset() ((mcusr & (1 << PORF)))
/** Check if last reset was external reset */
#define is_external_reset() ((mcusr & (1 << EXTRF)))

/** Keeps track whether device was powered down for power saving reasons */
static uint8_t power_down_triggered __attribute__((section(".noinit")));

/* Display arrangements */

/** X offset from the left in pixels, the first digit it drawn from here */
const uint8_t x_offset = 4;
/** Y position in pages (i.e. 8bit rows) from the top */
const uint8_t y = 0;
/** Width of each digit in pixels */
const uint8_t w = TinyOLED4kfont24x48Clock.width;

/** X position of the ten minute digit x_:__ */
const uint8_t x_tenmins = x_offset;
/** X position of the one minute digit _x:__ */
const uint8_t x_minutes = x_offset + w;
/** X position of the colon */
const uint8_t x_colon   = x_offset + 2 * w;
/** X position of the ten second digit __:x_ */
const uint8_t x_tensecs = x_offset + 3 * w;
/** X position of the one minute digit __:_x */
const uint8_t x_seconds = x_offset + 4 * w;

/** X position in pixels to display the last counted time */
const uint8_t x_lasttime = 44;
/** y position in pages  to display the last counted time */
const uint8_t y_lasttime =  6;

/**
 * Shortcut to display a single digit.
 *
 * Note that this expects a single digit as value - and only really works
 * properly that way. It adds the '0' offset to turn it into an ASCII character
 * of the given value (i.e. 5 -> '5'), making live easier to display the digit.
 *
 * No checks are performed here, so mess it up at your own risk.
 *
 * @param x_pos X position of the digit in px (should be one of the X_* macros)
 * @param val value to set, for best results, use an actual integer [0,9] here
 */
#define set_digit(x_pos, val) do {\
    oled.setCursor(x_pos, y); \
    oled.write(val + '0'); \
} while (0);


/**
 * Set up the OLED.
 *
 * Initialize OLED at 128x64 and check the reset source.
 *
 * If power-on reset happened (i.e. regular powering up), the displayed is
 * cleared behind the scenes and initialized showing "00:00".
 *
 * If external reset happened (i.e. reset button pressed), the display is
 * inverted to show a quick flashing and reset to the initial "00:00", but
 * additionally the last counter value is shown at the bottom.
 */
void setup_oled(void)
{
    oled.begin(128, 64, sizeof(tiny4koled_init_128x64r), tiny4koled_init_128x64r);

    /* Clear display or invert it and add the last timer value */
    if (is_power_on_reset() || power_down_triggered) {
        oled.off();
        oled.clear();
    } else if (is_external_reset()) {
        oled.setInverse(1);
        oled.setFont(FONT8X16CLOCK);
        oled.setCursor(x_lasttime, y_lasttime);
        oled.write(&clock_time);
    }

    /* Use big font from now on and initialize "00:00" time */
    oled.setFont(FONT24X48CLOCK);
    oled.setCursor(x_offset, y);
    oled.write("00:00");

    /* Turn display on in any case */
    oled.on();

    /* Invert display back if needed */
    if (is_external_reset()) {
        oled.setInverse(0);
    }
}


/**
 * Increment the clock's time by one second and update the structs.
 *
 * Updates the time itself as well as the clock_time_changes struct, as each
 * digit is stored individually for easier display updating.
 */
void increment_time(void)
{
    memset(&clock_time_changes, 0, sizeof(clock_time_t));

    if (++clock_time.seconds == 10) {
        clock_time.seconds = 0;
        clock_time_changes.tensecs = 1;

        if (++clock_time.tensecs == 6) {
            clock_time.tensecs = 0;
            clock_time_changes.minutes = 1;

            if (++clock_time.minutes == 10) {
                clock_time.minutes = 0;
                clock_time_changes.tenmins = 1;

                if (++clock_time.tenmins == 10) {
                    /*
                     * This isn't really the right device for timing stuff
                     * you cook over 1h40min. But hey, who am I to judge.
                     * Not gonna support a third minutes digits though,
                     * so simply wrapping around to zero in that case.
                     */
                    clock_time.tenmins = 0;
                }
            }

#if POWER_SAVING == 1
            /*
             * Minutes are updated, check if the threshold to power down
             * the clock for power saving reasons was reached - and go
             * ahead with it if it was.
             */
            if (clock_time.minutes == (POWER_DOWN_MINUTES % 10) &&
                    (clock_time.tenmins == (POWER_DOWN_MINUTES / 10)))
            {
                power_down_triggered = 1;
                oled.off();
                set_sleep_mode(SLEEP_MODE_PWR_DOWN);
                sleep_mode();
            }
#endif

        }
    }
}


/**
 * Display the current time on the OLED.
 *
 * Each digit is updated individually, so only the ones that are actually
 * changing are updated and the rest of the display content remains as is,
 * thus speeding up the whole process.
 */
void show_time(void)
{
    set_digit(x_seconds, clock_time.seconds);

    if (clock_time_changes.tensecs) {
        set_digit(x_tensecs, clock_time.tensecs);
    }

    if (clock_time_changes.minutes) {
        set_digit(x_minutes, clock_time.minutes);
    }

    if (clock_time_changes.tenmins) {
        set_digit(x_tenmins, clock_time.tenmins);
    }
}


/**
 * Set up the hardware timer to cause an interrupt every ~1s.
 *
 * Timer/Counter1 is used here, since it allows larger prescaler values
 * compared to Timer/Counter0, easily allowing to get the required ~1Hz.
 */
void setup_timer()
{
    /* Set CTC mode (and implicitly stop timer as CS1x values are all zero) */
    TCCR1 = (1 << CTC1);

    /* Reset counter register */
    TCNT1 = 0;

    /*
     * Set registers to match ~1s, i.e ~1Hz:
     *
     * OCR1A value triggers Compare MatchA interrupt when TCNT1 reaches it
     * OCR1C value resets TCNT1 back to zero when it reaches it
     * -> both get same value here
     *
     *
     *  F_CPU      cnt      prescaler
     * 1000000 / ((242 + 1) * 4096) -> 1.004693930 Hz  -> ~4s fast per 10min
     * 1000000 / ((243 + 1) * 4096) -> 1.000576332 Hz  -> ~1s fast per 10min
     * 1000000 / ((244 + 1) * 4096) -> 0.996492347 Hz  -> ~4s slow per 10min
     *
     * TODO use a 8.192MHz crystal instead of 8.0MHz, that way, with div8
     *      1024000 / ((249 + 1) * 4096) == 1 exactly
     */
    OCR1A = 243;
    OCR1C = OCR1A;

    /* Enable Compare MatchA interrupt */
    TIMSK |= (1 << OCIE1A);

    /* Set clock prescale to 4096 and start the timer that way */
    TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS10);
}

/**
 * Timer/Counter1 Compare MatchA interrupt handler.
 *
 * Executed whenever TCNT1 register reaches the value set in OCR1A.
 * Interrupt itself will wake up the CPU from its idle sleep mode,
 * and the handler here will simply set a flag that the interrupt
 * occurred, which is then evaluated and hanlded in the main loop.
 */
ISR(TIMER1_COMPA_vect)
{
    timer_triggered = 1;
}


/**
 * Main - duh.
 *
 * Chcks for all eternity whether the timer interrupt happened, and if so,
 * increases the timer by a second and update the OLED content. As that's
 * all there is to do, go to idle sleep mode until the next interrupt has
 * to be handled.
 */
int main(void)
{
    /* Copy MCU status register (MCUSR) value and clear it */
    mcusr = MCUSR;
    MCUSR = 0x00;

    /* Disable interrupts for now */
    cli();

    /* Set all GPIO pins as input for now and enable pullup on unused PB1 */
    DDRB = 0x00;
    PORTB = (1 << PB1);

    /* Set up everything */
    setup_timer();
    setup_oled();
    set_sleep_mode(SLEEP_MODE_IDLE);

    /* Zero the variables in .noinit section, they've done their job now */
    memset(&clock_time, 0, sizeof(clock_time));
    power_down_triggered = 0;

    /* Enable interrupts and get going */
    sei();

    while (1) {
        /*
         * Check if a second has passed and update the time / OLED content.
         *
         * While the Compare MatchA interrupt will wake up the CPU, so might
         * other things, so best not to imply that reaching here means the
         * timer interrupt happened - hence the timer_triggered flag.
         */
        if (timer_triggered) {
            timer_triggered = 0;
            increment_time();
            show_time();
        }

        /* Nothing to do until another second passes - take a nap */
        sleep_mode();
    }
}

