/*
 * Fake Arduino header file
 * Implements just the bare necessity to make the libraries happy
 * Obviously don't use this if you're actually planning on doing Arduino stuff
 *
 * Part of cook'oo clock - the smack-'n-go reverse kitchen timer
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

#ifndef Arduino_h
#define Arduino_h

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

typedef uint8_t byte;
#define delay _delay_ms

/*
 * Implements a very simple version of Arduino's Print class to use within
 * the Tiny4kOLED library. Only supports the essentials for clock handling.
 */
#include "print.h"

/*
 * This is just to make the compiler happy.
 * This is untested and probably won't end well if ever used.
 * Check Tiny4kOLED library for details to implement this for real
 */
#define DATACUTE_F_MACRO_T void


/*
 * ATtiny85 specific I/O definitions abstracted for tiny-i2c library
 */
#define DDR_USI         DDRB
#define DDR_USI_CL      DDR_USI

#define PORT_USI        PORTB
#define PORT_USI_CL     PORT_USI

#define PIN_USI         PINB
#define PIN_USI_SDA     PINB0
#define PIN_USI_SCL     PINB2
#define PIN_USI_CL      PIN_USI

#endif /* Arduino_h */
