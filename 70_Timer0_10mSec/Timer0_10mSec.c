/*************************************
* Purpose: Timer0을 이용하여 1초마다 overflow
* interrupt에 의한 LED Shift
*
* TIMSK
* TCCR1B
* TCNT1
*************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

// from TCNT = (CS / 14745600 ) * (256-x) =10msec
// x = time * (14745600/CS)
#define cDelay 144

unsigned char SEG[10]= {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90};

volatile int sec =0;
volatile int msec =0;

ISR (TIMER0_OVF_vect)
{
	msec++;
	if(msec == 100)	{
		sec++;
		msec = 0;
		PORTE = SEG[sec];
	}
	if (sec==10) {
		sec = 0;
		PORTE = SEG[sec];
	}
	PORTF = SEG[msec/10];

	TCNT0 = 0xFF-cDelay+1;    //초기값
}

int main(void)
{
	DDRE  = 0xFF;
	DDRF  = 0xFF;

	PORTE = SEG[sec];
	PORTF = SEG[msec];
	
	cli();
	TIMSK |= (1<<TOIE0);    // Timer0 오버플로 인터럽트 에이블
	
	// Normal, 1/1024 for 프리스케일
	TCCR0 |= (1<<CS02);
	TCCR0 |= (1<<CS01);
	TCCR0 |= (1<<CS00);
	 
	TCNT0 = 0xFF-cDelay+1;    // 10msec

	sei();         //SRGE  = 0x80;
	while(1)
   {
   }
}
