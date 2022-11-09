# AVR PWM
 ## How works PWM:
 PWM - Pulse Width Modulation:
 - timer counts till reach specific value (for example timer counter max value), after it have reached, it will not reset its value. The Reset is made when timer overflow interrupt comes
 - changing width of impulse : change value of timer compare register
 - PWM can be configured on OCRXA and OCRXB output X depends on timer number which is used. Atmega328p has 2x timer 0 and timer 1 

## GOAL
 create 1KHz impulse duration
 
## REALISATION
 so for creating so frequently impulse i will choose timer 0 (8bit)
 prescaler = 64
 timer 0 = 8bit = 2^8 = 256
 256 * 1/16 * 64 = 1024 us = 1ms 
 1ms = 1KHz
 As an output I have selected pin PB6 which has PWM capability. 
