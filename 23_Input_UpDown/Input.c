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
	Byte SEG[10] =
			{ 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90 };

	signed char Index=0;

	Initialize_Ports();

	while (1)  // 무한루프 실행
	{
		PORTF = SEG[Index];

		if( bit_is_set(PIND, PD0) )
			Index++;
		if( bit_is_clear(PIND, PD0) )
			Index--;

		if( Index> 10 )
			Index = 0;
		if( Index < 0 )
			Index = 9;

		_delay_ms(200);  // 200ms 지연시킴
	}
}
