/*
 * WaterLevelSensorADC.c
 *
 * Created: 29.09.2022 18:59:33
 * Author : leskers606
 */ 
#define F_CPU 20000000 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	//REGION START : SETUP:
	
	ADMUX |= (1<<REFS0) | (1<<MUX1) || (1<<MUX0); //select voltage refernce as external and ADC3 as source


    //REGION END : SETUP:
    while (1) 
    {
    }
}

