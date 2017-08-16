/*************************************
* Purpose: Understand GPIO registers
*
* DDRn
* PORTn
* PINn
*************************************/

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
			PORTB = 0x00;
		else
			PORTB = 0xFF;

		_delay_ms(10);  // 500ms Áö¿¬½ÃÅ´
	}
}
