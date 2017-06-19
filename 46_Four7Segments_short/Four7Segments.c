#include <avr/io.h>
#include <util/delay.h>

#define cDelayTime	50

unsigned char SEG[10] = {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 0XD8,0X80,0X90};
unsigned char POWER[4] = { 0x01, 0x02, 0x04, 0x08};
unsigned int  Digits[4] = {1, 10, 100, 1000};

unsigned int Number=2589;

int main(void) {
	unsigned char Index;
	unsigned int temp;

	DDRA = 0xff;
	DDRB = 0xff;

	while (1) {
		temp = Number;

		for(int i=3;i>=0; i--) {
			Index = temp/Digits[i];
			PORTA = ~POWER[3-i];
			PORTB = SEG[Index];
			temp = temp%Digits[i];
			_delay_ms(cDelayTime);
		}
	}
}
