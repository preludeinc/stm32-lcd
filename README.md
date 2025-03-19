# STM32_LCD
The author's name and course name are displayed and an alien character scrolls across the second-line of the LCD screen.

The LCD configuration files were ported from files initially writen by the author for the PIC18F4685. 

## Hardware Setup
- PortE bit 8: connected to the RS (register select) input of the LCD
- PortE bit 9: connected to the R/!W (read/write) pin
- PortE bit 10: connected to the EN (enable) pin, 
- PortE bit 11: hard-wired to board's 5V supply to power the LCD back-light
- PortE bits 12-15: connected to LCD data bits 4-7

This file doesn't contain all configuration files included in the initial project (such as stm32f4xx_hal_conf.h, stm32f4xx_it, stm32f4xx_hal_msp.c among others) as some were auto-generated, by the STM32CubeIDE, and the functionality contained in these files was not necessarily heavily utilized in this project - it doesn't use interrupts for example.
