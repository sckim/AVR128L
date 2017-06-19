#include <avr/io.h>
#include <util/delay.h>

#define cDelayTime	20

unsigned char SEG[10] = {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 0XD8,0X80,0X90};
unsigned char POWER[4] = { 0x01, 0x02, 0x04, 0x08};

unsigned int Number=1234;

int main(void) {
	unsigned char Index;
	unsigned int temp;

	DDRA = 0xff;
	DDRB = 0xff;

	while (1) {
		temp = Number;

		Index = temp/1000;
		PORTA = ~POWER[3];
		PORTB = SEG[Index];
		temp = temp%1000;
		_delay_ms(cDelayTime);

		Index = temp/100;
		PORTA = ~POWER[2];
		PORTB = SEG[Index];
		temp = temp%100;
		_delay_ms(cDelayTime);

		Index = temp/10;
		PORTA = ~POWER[1];
		PORTB = SEG[Index];
		temp = temp%10;
		_delay_ms(cDelayTime);

		Index = temp;
		PORTA = ~POWER[0];
		PORTB = SEG[Index];
		_delay_ms(cDelayTime);
	}
}
