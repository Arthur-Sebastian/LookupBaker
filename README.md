# LOOKUP BAKER
## Lookup table creator for RGB colorspace animation
### (C) Arthur Sebastian Miller 2021

Build using GNU Make, run the executable in /build/ directory.
Prebuilt Ubuntu 21.04 exectuable included.

Executable only outputs into stdout, and created lookup table
files formatted and ready to be used in AVR C/C++ projects.

Created arrays include PROGMEM keyword for program space storage
on AVR 8bit devices. Otherwise most microcontrollers attempt
loading the data into SRAM which causes a program crash on arrays
exceeding or approaching the maximal heap size. 

Always include <avr/pgmspace.h> into your file containing the tables
when compiling the finished software using avr-gcc toolchain. 
