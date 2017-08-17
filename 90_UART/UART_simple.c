#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"

char str[80];
char key_input;

int main(void) {
	uart_init(9600UL);

	stdout = &uart_output;
	stdin = &uart_input;

	printf("\rHello world!");
	do {
		printf("\rPress any key ... (Q:quit) \r\n");
		key_input = getchar();
		printf("%c\r", key_input);
		_delay_ms(200);
	} while (key_input!='Q');

	printf("\rGood bye");
	return 0;
}
