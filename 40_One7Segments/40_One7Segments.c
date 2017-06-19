#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char Byte;

int main(void) {
	int Index = 0;

	Byte SEG[10]= {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 0XD8,0X80,0X90};

	DDRF = 0xff;

	while (1) {
		PORTF = SEG[Index++];
		if( Index > 10 )
			Index = 0;
		_delay_ms(500);
	}
}
