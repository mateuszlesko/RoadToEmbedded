#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define F_CPU 16000000
#define BAUD 9600
#define UBBR FCPU/16/BAUND-1


#define D7	7
#define D6	6
#define D5	5
#define D4	4
#define E	3
#define RS	2
char znak = 65;


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


void setupZnakiRogi(void){
    //w lini max 16
    lcd_ini();
    
    PORTD &= ~(1<<RS); //rozkaz dla sterownika; stan 0
    lcd_bajt(128); //kursor ustaw na gorna linie lewy skraj
    PORTD |= (1<<RS); // bajty do wyswietlenia ascii
    lcd_bajt('A');
    lcd_bajt(' '); //nadpisywanie pozycji

    PORTD &= ~(1<<RS);
    lcd_bajt(128+15); //ustaw kursor na gorny prawy
    PORTD |= (1<<RS); 
    lcd_bajt('A');
    
    PORTD &= ~(1<<RS);
    lcd_bajt(192);//ustaw na dole linie lewy skraj
    PORTD |= (1<<RS); 
    lcd_bajt('A');

    PORTD &= ~(1<<RS);
    lcd_bajt(192+15); //ustaw kursor na dol prawo
    PORTD |= (1<<RS); 
    lcd_bajt('A');
}

void setup_wyswietlacz(){
    //w lini 16
    lcd_ini();
    PORTD &= ~(1<<RS); //rozkaz dla sterownika; stan 0
    lcd_bajt(128); //kursor ustaw na gorna linie lewy skraj
    PORTD |= (1<<RS); // wyswietl bajty ascii

}

void setup_nadawanie(void){
    //ustawienia: tylko nadawanie
    
    UBRR0 = UBRR; //ustawienie predkosci
    UCSR0C |= (1<<USCZ01) | (1<<USCZ00); // znak 8 bitowy, 1 bit stopu, bez parzystosci : 8n1
    UCSR0B |= (1<<TXEN0) | (1<<TXIE0)// wlaczony lacznik nadajnika, maska nadawcza zdjeta //zakomentowanie spowoduje brak nadawnia
    sei();
   // UDR0 = znak;

}

void setup_odbior(void){
    //ustawienia: tylko odbieranie
    UBRR0 = UBRR; //ustawienie predkosci
    UCSR0B |= (1<<RXEN0) | (1<<RXIE0)// wlaczony odbiornik, maska odbiorcza zdjeta
    sei();
   // UDR0 = znak;

}

void setup(void){
    setup_nadawanie();
    setup_odbior();
    setup_wyswietlacz();
}

char znak = 'A'; //65 //max 255, po 255 kolejna (modulo 256) 2^8 = 256, znak w ascii

void loop(void){

}

//wektor przerwania nadawczego transmisji szeregowej
ISR(USART_TX_vect){
    //podanie kolejnego znaku z ASCII; co 1.04 ms = 10*1/9600 ;10 bo 10 bitĂłw wysyĹ‚a siÄ™
    UDR0=znak++; 
}

ISR(USART_RX_vect){
    //odbior znaku
    char odp = UDR0;
    PORTD &= ~(1<<RS);
    lcd_bajt(128);
    PORTD |= (1<<RS);
    lcd_bajt(odp);
}

int main(void){
    setup_nadawanie();
    setup_odbior();
    while(1){
        loop();
    }
}