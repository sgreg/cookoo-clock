#
# cook'oo clock - the smack-'n-go reverse kitchen timer
#
# Copyright (C) 2020 Sven Gregori <sven@craplab.fi>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

TARGET_CONTROLLER=attiny85
TARGET_CPUFREQ_HZ=1000000

PROJECT = clock
MAIN = main.cpp
WIRE = libraries/tiny-i2c/TinyI2CMaster.cpp
OLED = libraries/Tiny4kOLED/src/Tiny4kOLED.cpp

CFLAGS = -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wextra
CFLAGS += -I. -I./libraries/tiny-i2c/ -I./libraries/Tiny4kOLED/src/
CFLAGS += -mmcu=$(TARGET_CONTROLLER) -DF_CPU=$(TARGET_CPUFREQ_HZ)

AVRDUDE_FLAGS = -p $(TARGET_CONTROLLER) -c usbasp

FUSE_LOW = 0x7d
FUSE_HIGH = 0xdf
FUSE_EXTENDED = 0xff

var := $(shell test -e $(WIRE).xx && test -e $(OLED) || echo "oh no")
ifneq ($(.SHELLSTATUS), 0)
	@echo "nope"
	$(error submodules missing)
endif

all: $(PROJECT)

$(PROJECT): check-submodules
	avr-g++ $(CFLAGS) $(WIRE) $(OLED) $(MAIN) -o $(PROJECT).elf
	avr-objcopy -O ihex -R .eeprom $(PROJECT).elf $(PROJECT).hex
	avr-size $(PROJECT).elf

check-submodules:
	@test -f $(WIRE) && test -f $(OLED) && exit 0  || {\
		echo "Libraries missing!" ;\
		echo "" ;\
		echo "Make sure you have git submodules set up properly." ;\
		echo "If in doubt, run: make init" ;\
		echo "" ;\
		exit 1 ;\
	}

init:
	@echo "initializing git submodules"
	@git submodule init
	@git submodule update

check-programmer:
	avrdude $(AVRDUDE_FLAGS) -n && echo "SUCCESS" || echo "FAILED"

fuses:
	avrdude $(AVRDUDE_FLAGS) -U lfuse:w:$(FUSE_LOW):m -U hfuse:w:$(FUSE_HIGH):m -U efuse:w:$(FUSE_EXTENDED):m

program:
	avrdude $(AVRDUDE_FLAGS) -U flash:w:$(PROJECT).hex

clean:
	rm -f $(PROJECT).elf $(PROJECT).hex

.PHONY: all check-submodules init check-programmer fuses program clean

