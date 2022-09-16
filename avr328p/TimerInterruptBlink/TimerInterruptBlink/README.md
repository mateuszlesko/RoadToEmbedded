# AVR Atmega 328p - Time Interrupt

## Blink diode every 1s

### Interrupt:
The interrupt is a event that has been caused by some doing, for example: timer counted, or on some pin was detected high level. The interrupts are handled by interrupt handler.

**The interrupt handler has to:**
- detect interrupt and choose the right method to handle it
- save the state of microprocessor before interrupted (states of registers, and next command to execute after interrupt will be handled)
- when more than 1 interrupt occured at one time set priorities to handle interrupts.

#### There are 2 common interrupt handler implementation 

##### 1. Software:
Additonal register for interrupts, microprocessor over and over asking for example device register about interrupt occuring.

##### 2. Hardware:
Realising as additional lines for interrupt, connected by OR gate to system bus + embedded priority decoder as additonal sequentional unit, that needs to be programmed  

### Timers:
Timers are measurement time by counting clock's ticks. The clock ticking speed are varried by clock frequency.

Every timer has a setted counting limit, that is going to reach limit value or setted value, when it comes and we can use interrupt to handle 

Atmega 328p has equipment in 2 kinds of timers:
- 8 bits
- 16 bits

Registers that opperates on timers:

- TCRR0B = set prescaler; (see below)
- TCCR0A = timer control register
- TIMSK0 = iterrupt mask regiser, enable timer interrupt

### PRESCALER
Prescaler enable to slow down counting ticks, by increasing time interval between ticks.
the formula for it :

*1/(F_CPU /prescaler value)*