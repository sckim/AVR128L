/*
 * Blink.c
 *
 *  Created on: 2017. 3. 22.
 *      Author: Soochan Kim
 */
#include <avr/io.h>
#include <util/delay.h>

void Init(void) {
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
}

void AllPort(unsigned char flag) {
	PORTA = flag;
	PORTB = flag;
	PORTC = flag;
	PORTD = flag;
	PORTE = flag;
	PORTF = flag;
	PORTG = flag;
}

int main(void) {
	unsigned char temp;
	Init();

	while (1) {
		for (int i = 0; i < 8; i++) {
			temp = 0xFE << i;
			PORTA = temp ^ 0xFF;
			_delay_ms(50);
		}
		for (int i = 0; i < 8; i++) {
			temp = 0xFE << i;
			PORTB = temp ^ 0xFF;
			_delay_ms(50);
		}
		for (int i = 0; i < 8; i++) {
			temp = 0xFE << i;
			PORTC = temp ^ 0xFF;
			_delay_ms(50);
		}
		for (int i = 0; i < 8; i++) {
			temp = 0xFE << i;
			PORTD = temp ^ 0xFF;
			_delay_ms(50);
		}
		for (int i = 0; i < 8; i++) {
			temp = 0xFE << i;
			PORTE = temp ^ 0xFF;
			_delay_ms(50);
		}
		for (int i = 0; i < 8; i++) {
			temp = 0xFE << i;
			PORTF = temp ^ 0xFF;
			_delay_ms(50);
		}
		for (int i = 0; i < 8; i++) {
			temp = 0xFE << i;
			PORTG = temp ^ 0xFF;
			_delay_ms(50);
		}
		AllPort(0x00);
		_delay_ms(500);
		AllPort(0xFF);
		_delay_ms(500);
		AllPort(0x00);
		_delay_ms(500);
	}
}

