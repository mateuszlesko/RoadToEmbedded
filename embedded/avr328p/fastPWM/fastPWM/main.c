/*
 * fastPWM.c
 *
 * Created: 09.11.2022 17:56:55
 * Author : mateuszlesko
 
 PWM - Pulse Width Modulation:
 - timer counts till reach specific value, after reached it will not reset its value, reset is made when timer overflow interrupt comes
 - changing width of impulse : change value of timer compare register
 - PWM can be configured on OCRXA and OCRXB output X depends on timer number which is used. Atmega328p has 2x timer #0 and timer #1 
 
 goal: create 1KHz impulse duration
 so for creating so frequently impulse i will choose timer 0 (8bit)
 prescaler = 64
 timer 0 = 8bit = 2^8 = 256
 256 * 1/16 * 64 = 1024 us = 1ms 
 1ms = 1KHz
 
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include<util//delay.h>

#define MAX_BRIGHT 255

int bright = 0;

int main(void)
{
	/* REGION SETUP */
	DDRD |= (1 << 6); //set PB6 as output : PB6 has PWM capatibility
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 <<COM0A1); // timer 0: setting up PWM mode; after max value is reached clear
	TCCR0B |= (1 << CS01) | (1 << CS00); // setting prescaler 64
	OCR0A = 0;
	
	/*REGION LOOP */
	while (1) 
    {
		for(bright = 0; bright < MAX_BRIGHT; bright++)
		{
			OCR0A = bright;
			_delay_ms(20);
		}
		
		for(bright = MAX_BRIGHT; bright > 0; bright--)
		{
			OCR0A = bright;
			_delay_ms(20);
		}
    }
}