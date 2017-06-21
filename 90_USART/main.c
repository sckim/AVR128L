/*
 * main.c
 *
 *  Created on: 2017. 6. 20.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "USART.h"

int main() {
	char text[] =
			"\r\nWelcome! Serial communication world!!\r\n Good Luck\r\n";
	char echo[] = "HKNU >> ";

	unsigned char i = 0;
	unsigned char c;

	DDRB = 0xff;
	DDRC = 0x00;

	uart_init(9600UL);

	printString(text);
	printString(echo);
	while (text[i] != '\0') {
		putch(text[i++]);
		_delay_ms(40);
	}
	i = 0;
	while (echo[i] != '\0')
		putch(echo[i++]);

	while (1)	{
		c = getch();
		putch(c);
	}
	return 0;
}
