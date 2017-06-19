#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define cDelayTime	5

unsigned char SEG[10] = {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 0XD8,0X80,0X90};
unsigned char POWER[4] = { 0x01, 0x02, 0x04, 0x08};
unsigned int  Digits[4] = {1, 10, 100, 1000};

volatile int Number=10;

SIGNAL(SIG_INTERRUPT0)
{
	Number++;
	if( Number > 9999 )
		Number = 0;
}

SIGNAL(SIG_INTERRUPT1)
{
	Number--;
	if( Number <0 )
		Number = 9999;
}

int main(void) {
	unsigned char Index;
	unsigned int temp;

	DDRA = 0xff;
	DDRB = 0xff;

    EIMSK = 0b00000011;		//INT0 번 사용 설정
    //EIMSK = 0x01;
    EICRA = 0b00001010; 	//INT0 하강모서리에서 동작되도록 설정
    //EIMSK = 0x02;
    SREG |= 0b10000000;
    //SREG |= 0x80;

	while (1) {
		temp = Number;

		for(int i=3;i>=0; i--) {
			Index = temp/Digits[i];
			PORTA = ~POWER[i];
			PORTB = SEG[Index];
			temp = temp%Digits[i];
			_delay_ms(cDelayTime);
		}
	}
}
