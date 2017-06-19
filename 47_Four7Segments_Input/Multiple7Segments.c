#include <avr/io.h>
#include <util/delay.h>

unsigned char SEG[6] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92 };
unsigned char POWER[6] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20 };

int main(void) {
	int Index;

	DDRA = 0xff;
	DDRB = 0xff;

	while (1) {
		for(Index=5;Index>=0;Index--) {
			PORTA = ~POWER[Index];
			PORTB = SEG[Index];
			_delay_ms(100);
		}
	}
}
