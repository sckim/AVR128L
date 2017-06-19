#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define cDelayTime	50

unsigned char SEG[10] = {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 0XD8,0X80,0X90};
unsigned char POWER[4] = { 0x01, 0x02, 0x04, 0x08};
unsigned char strDigits[5];

int Number=2589;

int main(void) {
	unsigned char Index;
	unsigned int temp;

	DDRA = 0xff;
	DDRB = 0xff;

	while (1) {
		itoa(Number, strDigits, 10);
		for(int i=0;i<4; i++) {
			PORTA = ~POWER[i];
			PORTB = SEG[strDigits[i]-0x30];
			_delay_ms(cDelayTime);
		}
	}
}
