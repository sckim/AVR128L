/***********************************************************
* 목적: 포트의 입력 상태에 따라서 숫자를 증가 혹은 감소 시킨다.
*
* PINn
* DDRn
* PORTn
***********************************************************/

#include <avr/io.h>
#include <util/delay.h>

#define	SegmentPort	PORTB
#define LEDPort		PORTB
#define InputPort	PIND

#define cDelay 		500

typedef unsigned char Byte;

// 포트의 초기 상태를 함수를 이용해서 설정
void Initialize_Ports(void)
{
	DDRA = 0xFF;	// 출력: 1, 입력 0
	DDRB = 0xFF;
	DDRC = 0xFF;
	// PORTD의 b0 bit만 0으로 하여 입력으로 설정
	DDRD = 0xFE;	
	DDRE = 0xFF;
	DDRF = 0xFF;
}

int main (void)
{
	Byte LED[9] = {0xFF, 0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80, 0x00};
	Byte SEG[16]= {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 
					0XD8,0X80,0X90, 0X88, 0X83, 0XC6, 0XA1, 0X86, 0X8e};

	signed char Index = 0;
	unsigned char flag = 1;
	
	Initialize_Ports();

	while (1)  // 무한루프 실행
	{
		// 버튼의 입력을 읽음
		flag = PIND&0x01;
		//flag = InputPort & 0x01;
		//flag = InputPort & B0;

		if (flag)
			Index++;
		else
			Index--;

		// 숫자가 8이면 다시 0으로
		if (Index==9)
			Index = 0;
		// Index가 -1이면 최대값 8로
		if (Index==-1)
			Index = 8;

		LEDPort = LED[Index];
		SegmentPort = ~SEG[Index];
		_delay_ms(cDelay);  // 500ms 지연시킴
	}
}
