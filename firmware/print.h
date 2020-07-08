/*
 * Print class header file
 * Used for *very* limited compatibility with Arduino's Print class,
 * only supports necessary clock-related write functions
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
#ifndef PRINT_H
#define PRINT_H

#include "clock.h"


class Print {
    public:
        /**
         * Write a single character.
         * Implemented by Tiny4kOLED library.
         *
         * @param c Character to write
         * @return Number of characters written
         */
        virtual size_t write(byte c);

        /**
         * Write a string to the OLED.
         *
         * @param str String to write, can be NULL
         * @return Number of characters written
         */
        size_t write(const char *str)
        {
            if (str == NULL) return 0;
            return write((const uint8_t *) str, strlen(str));
        }

        /**
         * Write given buffer of given size to the OLED.
         *
         * @param buffer Buffer to write
         * @param size Size of the buffer to write
         * @return Number of characters written
         */
        size_t write(const uint8_t *buffer, size_t size)
        {
            size_t n = 0;
            while (size--) {
                if (write(*buffer++)) n++;
                else break;
            }
            return n;
        }

        /**
         * Write the time based on the given clock_time_t data to the OLED.
         *
         * @param clock_time clock_time_t struct data
         * @return Number of characters written
         */
        size_t write(clock_time_t *clock_time)
        {
            char buf[5];
            buf[0] = clock_time->tenmins + '0';
            buf[1] = clock_time->minutes + '0';
            buf[2] = ':';
            buf[3] = clock_time->tensecs + '0';
            buf[4] = clock_time->seconds + '0';
            return write((uint8_t *) buf, sizeof(buf));
        }
};

#endif // PRINT_H
