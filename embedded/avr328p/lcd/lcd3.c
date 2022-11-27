#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

//kontroler - czujnik temperatury komunikacja master - slave
#define F_CPU 16000000

#define D7	7
#define D6	6
#define D5	5
#define D4	4
#define E	3
#define RS	2

#define pinn 2
char znak = 65;

//REGION:sterowanie wyswietlaczem
void lcd_ini(void);
void lcd_4bity(unsigned char bajt);
void lcd_bajt(unsigned char bajt);

void lcd_4bity(unsigned char bajt)
{
	if(bajt & 0x01)  PORTD |= (1<<D4);  else  PORTD  &= ~(1<<D4);
	if(bajt & 0x02)  PORTD |= (1<<D5);  else  PORTD  &= ~(1<<D5);
	if(bajt & 0x04)  PORTD |= (1<<D6);  else  PORTD  &= ~(1<<D6);
	if(bajt & 0x08)  PORTD |= (1<<D7);  else  PORTD  &= ~(1<<D7);
}

void lcd_bajt(unsigned char bajt)
{
	PORTD |= (1<<E);
	lcd_4bity(bajt>>4);
	PORTD  &= ~(1<<E);
	_delay_us(5);
	PORTD |= (1<<E);
	lcd_4bity(bajt);
	PORTD  &= ~(1<<E);
	_delay_us(100);
}

void lcd_ini(void)
{
	DDRD |= (1<<D7)|(1<<D6)|(1<<D5)|(1<<D4)|(1<<E)|(1<<RS);
	PORTD &= ~(1<<E)& ~(1<<RS);

	PORTD |= (1<<E);
	lcd_4bity(0x03);
	PORTD  &= ~(1<<E);
	_delay_ms(20);
	
	PORTD |= (1<<E);
	lcd_4bity(0x03);
	PORTD  &= ~(1<<E);
	_delay_ms(5);
	
	PORTD |= (1<<E);
	lcd_4bity(0x03);
	PORTD  &= ~(1<<E);
	_delay_ms(5);
	
	PORTD |= (1<<E);
	lcd_4bity(0x02);
	PORTD  &= ~(1<<E);
	_delay_ms(2);
	
	lcd_bajt(0b00101000);//Function set         0b001DNFxx
	lcd_bajt(0b00001100);//Display ON/OFF       0b00001DCB
	lcd_bajt(0b00000110);//Entry mode set       0b000001IS
	lcd_bajt(0b00000001);//Display clear        0b00000001
	_delay_ms(2);
	lcd_bajt(0b10000000);//DDRAM set (kursor)   0b1AAAAAAA
}
//ENDREGION

void setup(void){
    lcd_ini();
}

void loop(void){
    DDRB |= (1<<pinn); //1 ustawia output (master transmiter)
    DDRB = DDRB | 0x00000100; //to samo 
    DDRD = DDRB | 0x04; //to samo

    //sterownie linia poprzez PORT
    
    ///MASTER nadanie sygnaĹ‚u 
    PORTB |= (1<<pinn); //sterowanie wejĹ›ciem //stan wysoki
    _delay_us(50);// etap przed startem
    
    PORTB &= ~(1<<pinn); // stan niski ustawia dziaĹ‚ania
    PORTB = PORTB & 0b11111011; //wyzerowanie jednego bitu, nie calosci
    PORTB = PORTB & 0xfb;
    _delay_us(1000); // start

    PORTB |=(1<<pinn); //stan wysoki
    _delay_us(30);

    //MASTER ustawienie na odbiĂłr (master reciver)
    DDRB &= ~(1<<pinn); // ustawienie wejscia
    _delay_us(40); //czas na zewrzenie SLAVE

    //if( PINB &  1<<pinn ) //czytanie TYLKO 2 linii
    if( PINB & 0b00000100 ) //czytanie TYLKO 2 linii
    {
        //nie zwaracie; nie ma slave
        PORTB &= ~(1<<RS);
        lcd_bajt(128);
        PORTD |= (1<<RS);
        lcd_bajt('N'); //No
    }
    else
    {
        //zwarcie; jest slave
          PORTB &= ~(1<<RS);
        lcd_bajt(128);
        PORTD |= (1<<RS);
        lcd_bajt('Y'); //Yes
    }

    _delay_ms(1000); // odczekaj az skonczy wydawac bajty; nowa tura handshake

}

int main(void){
    setup();
    while(1){
        loop();
    }
}