#!/bin/sh
/home/maciek/Downloads/kk-multicopter-multiwii/arduino-1.6.5/hardware/tools/avr/bin/avrdude -C/home/maciek/Downloads/kk-multicopter-multiwii/arduino-1.6.5/hardware/tools/avr/etc/avrdude.conf  -v -v -v -v -patmega328p -cusbasp -Pusb -Uflash:w:Release/Drone_ELT_clean.hex:i 
