#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char Byte;

// Common anode에 대한 값
unsigned char SEG[16]= {0xC0, 0xF9,0xA4,0xB0,0x99,0x92,0x82, 0xD8,0x80,0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8e};

void Initialize_Ports(void) {
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
//	DDRD = 0xF0;
	DDRE = 0xFF;
	DDRF = 0xFF;
}

int main(void) {
	Initialize_Ports();

	PORTF = 0xFF;
	while(1)	{
		if( !(PIND & 0x01) )  {//key pressed	
			PORTF = SEG[1];
//			PORTA = PORTA | 0x01;
		} 
		if( !(PIND & 0x02) )	{
			PORTF = SEG[2];
//			PORTA = PORTA | 0x02;
		} 

		_delay_ms(10);  // 500ms 지연시킴
	}
}
