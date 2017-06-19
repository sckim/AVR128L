#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char Byte;

Byte SEG[10]= {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 0XD8,0X80,0X90};
Byte POWER[6] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20 };

int main(void) {
	int Index;
	int Value=0;

	DDRD = 0xff;
	DDRE = 0xff;

	while (1) {
		for(Index=5;Index>=0;Index--) {
			PORTD = POWER[Index];
			PORTE = SEG[Value];
			if( Value > 10 ) 
				Value = 0;
			_delay_ms(100);
		}
		Value++;
		if( Value > 9 ) 
				Value = 0;
	}
}
