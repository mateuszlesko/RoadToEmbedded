/*
 * TimerInterruptBlink.cpp
 *
 * Created: 16.09.2022 21:10:35
 * Author : mateuszlesko
 */ 

#define F_CPU 20000000 // define CPU base FREQ
#include <avr/io.h>
#include <avr/interrupt.h>


 unsigned char extra_time = 0;

int main(void)
{
  //SETTING IN & OUT PORTS
  DDRD |= (1<<3); //output on pin D3
  DDRD &= ~(1<<2); //input on pin D2
  
  //SETTING TIMER for tick every 1s
  TCCR0A = (1 << WGM01); // set CTC bit - after timer count specific value it iterrupting and clearing time counter value
  OCR0A = 195;// set compare timer register = count clock ticks
  TIMSK0 = (1 << OCIE0A);//register controling time interrupts; execute interrupt when match comperation occured
  sei();//enable interrupt 
  TCCR0B = (1 << CS02) | (1 << CS00); //set prescaler to 1/1024
  
  while (1) 
  {
  }
}

//TIMER INTERRUPT HANDLER
ISR(TIMER0_COMPA_vect){
  extra_time++;
  //every 1s
  if(extra_time > 10){
    PORTD ^= (1 << 3);
    extra_time = 0;
  }
}