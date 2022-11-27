#define f_CPU 16000000

#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

//linie wyswietlacza lcd
//rs = przestaw kursor; 0 - komendy dla sterownika, 1 - wyswietlenie znakow ascii
//rw = ; 0 - zapis do sterownika lcd (stale podlaczony do ) , 1 - odczyt ze sterownika lcd
//e = impuls aktywujacy, strop; 1 = wykonanie komendy
//2 rodzaje
//8 liniowy: D0 - D7
//4 liniowy = D4 - D7

//incicjalizacja zgodna z karta katalogowa

//function set = ustawienie wyswietlacza
//display on off
//entry mode set = przesuwanie kursora w trakcie zapisu
//display clear = jedynie w ini czyszczenie; normalnie nadpisuje sie pole spacja; nigdy NIE czysci sie wyswietlacza podczas pracy
//DDRAM set = ustawienie kursora

#define D7	7
#define D6	6
#define D5	5
#define D4	4
#define E	3
#define RS	2

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

char znak = 65;

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

//kodowanie binarnych na kolumny dziesietne i wyswietlenie na wyswietlaczu
//dzielenie na kolumny binarne:
//liczba / 1000
//liczba % 1000
//reszta / 100
//reszta %100
//reszta reszty / 10
//reszta reszty % 10
//reszta reszty reszty / 1

void setup(void){
    //w lini 16
    lcd_ini();
   
    //kolumny dziesietne
    uint8_t lsb = 0b11011100;//z czujnka odebrane
    uint8_t msb = 0b00000101;// z czujnika odebrane
    uint16_t a = msb << 8 | lsb; // przesuniecie o 8 pozycji suma lsb
    uint8_t tys,set,dz,jed;
    tys = a/1000;
    set = a%1000/100;
    dz = a%1000%100/10;
    jed = a%1000%100%10; 

    PORTD &= ~(1<<RS); //rozkaz dla sterownika; stan 0
    lcd_bajt(128); //kursor ustaw na gorna linie lewy skraj
    PORTD |= (1<<RS); // wyswietl bajty ascii

    //liczby zaczynaja sie w ascii od nr 48
    //dla hex uzyc sumy binarnej: | 0x30
    lcd_bajt(tys+48);
    lcd_bajt(set+48);
    lcd_bajt(dz+48);
    lcd_bajt(jed+48);

}

int main(void){
    setup();
    //setupZnakiRogi();
    while(1){
        loop();
    }
}