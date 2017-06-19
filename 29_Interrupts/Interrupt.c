
/*=======================================================*/
//인터텁트 0와 1을 사용
//인터럽트 트리거은 하강엣지에서 인터럽트를 요구
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef unsigned char BYTE;

int Index=0;

volatile BYTE	SEG[10]= {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 0XD8,0X80,0X90};
volatile BYTE	LED[9] = {0xFF, 0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00};


SIGNAL(SIG_INTERRUPT0)		//외부인터럽트 0실행 프로그램
{
	Index++;

	if(Index==9) Index = 8;
	
	PORTB = LED[Index];
	PORTF = SEG[Index];
}

SIGNAL(SIG_INTERRUPT1)		//외부인터럽트 0실행 프로그램
{
	Index--;

	if(Index<0) Index = 0;

	PORTB = LED[Index];
	PORTF = SEG[Index];
}


int main(void)
{
	DDRB = 0xFF;
	DDRD = 0x00;
	DDRF = 0xFF;

	PORTB = LED[Index];
	PORTF = SEG[Index];


	// External Interrupt Mask Register
	EIMSK=0x03;		//2진수 (16진주:0x41)

 	// External Interrupt Control Register 
	EICRA=0x0f;		//상승 에지

	SREG=0x80;		//16진수(2진수:0b10000000)


	while(1) {

    }
}

