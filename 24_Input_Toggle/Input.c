#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char Byte;

#define SET_BIT(p,n) ((p) |= (1 << (n)))
#define CLR_BIT(p,n) ((p) &= (~(1) << (n)))

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
	unsigned char flag=1;

	Initialize_Ports();
	PORTA = 0xFF;

	while (1)  // 무한루프 실행
	{
		PORTF = SEG[Index];

		if( bit_is_clear(PIND, PD0) )
			flag^=1;

		if( flag )	{
			Index++;
			//PORTA &= 0xFE;	// PORTA.0를 0으로..
			SET_BIT(PORTA, PA0);
		}  else	{
			Index--;
			//PORTA |= 0x01;	// PORTA.0을 1로
			CLR_BIT(PORTA, PA0);
		}

		if( Index> 10 )
			Index = 0;
		if( Index < 0 )
			Index = 9;

		_delay_ms(200);  // 200ms 지연시킴
	}
}
