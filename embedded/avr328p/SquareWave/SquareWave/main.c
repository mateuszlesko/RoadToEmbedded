/*
 * SquareWave.c
 *
 * Created: 07.11.2022 20:37:06
 * Author : mateuszlesko
 */ 

//define CPU frequency = 16 MHz
#define F_CPU 16000000 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int direction = 0;

int main(void)
{
    /*
   EXPLAINATION:
   the square wave works in CTC mode. The square wave is generated by using compare register OCR1A or OCR1B; 
   the counter is counting till selected value is reached, in that moment the interrupt caused reset of counter
   Output on PINS with OCR1A or OCR1B (PB0 or PB1 - compare registers: COMPA or COMB)
  
   OCR1A is 16bit register for 16bit-timer
   The counting for timer has place in TCNTn register (also 16bit). TCNTn counting up till value from OCR1A has been reached. When that come, TCNT is reseted.
   And on the selected output we can observe state change.
   By changing value of OCR1A we can have control frequency of generated signal.

  Calculating prescaler value:
  prescaler = 256 steps (2^8); 
  max limit counter value = 65535 (2^16)
  the goal is to change state on output every 1s; the state should be keep by 1s
  1000000 us = OCR1A * 1/16us * 256
  OCR1A = (1000000 * 16) / 256 = 62500
      
  */
    //set direction PB1 as output
    DDRB |= (1 << 1);
    TCCR1A |= (1 << COM1A0); // setting CTC mode : toggle OC1A on compare match
    TCCR1B |= (1 << WGM12) | (1 << CS12); //WGM12 is responsible for generating square wave - CTC1; CS12 = 256 selecting prescaler
    
    OCR1A = 62500;
	
	TIMSK1 |= (1 << OCIE1A);
	//enable interrupt
	sei();
	while (1)
	{
    
	}
}

/* change width of impulse is making during interrupt execution*/
ISR(TIMER1_COMPA_vect)
{
	if(direction == 0)
	{
		OCR1A += 2000;
		if(OCR1A >= 62500)
		{
			direction = -1;
		}
	}
	else
	{
		OCR1A -= 2000;
		if(OCR1A < 4000)
		{
			direction = 1;
		}
	}
}
