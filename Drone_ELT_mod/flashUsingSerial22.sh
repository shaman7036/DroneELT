#!/bin/sh
/home/maciek/Downloads/kk-multicopter-multiwii/arduino-1.6.7/hardware/tools/avr/bin/avrdude -C/home/maciek/Downloads/kk-multicopter-multiwii/arduino-1.6.7/hardware/tools/avr/etc/avrdude.conf  -v -v -v -v -patmega328p -c arduino -P/dev/ttyUSB0 -b 115200 -Uflash:w:/tmp/build6061988620902112638.tmp/Drone_ELT_mod.cpp.hex:i 
