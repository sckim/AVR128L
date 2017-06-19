#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char Byte;

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

	while(1)	{
		if( bit_is_set(PIND, PD0) )
			PORTA |= 0x01;
		else
			PORTA &= ~0x01;

		if( bit_is_set(PIND, PD1) )
			PORTA |= 0x02;
		else
			PORTA &= ~0x02;

		if( bit_is_set(PIND, PD2) )
			PORTA |= 0x04;
		else
			PORTA &= ~0x04;
		
		if( bit_is_set(PIND, PD3) )
			PORTA |= 0x08;
		else
			PORTA &= ~0x08;

		_delay_ms(10);  // 10ms Áö¿¬½ÃÅ´
	}
}
