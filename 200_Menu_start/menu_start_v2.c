#include <avr/io.h>
//#include <stdio.h>
//#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "adc.h"

// 7 segments
#define cSegmentPortDir		DDRD
#define cSegmentPortData	PORTD

char str[80];
char key_input;

void printSegment(unsigned char number) {
	cSegmentPortDir |= 0xF0;
	cSegmentPortData = number << 4;
}

char *GetString(void) {
	unsigned char i = 0;

	do {
		key_input = getchar();
		printf("%c", key_input);
		str[i] = key_input;
		i++;            // -> Skip ?
	} while (key_input != 0x20);
	str[--i] = 0x00;
	puts("");

	return str;
}

int SegmentDisplay(void) {

	printf("Enter your number [press 'q' to upper menu]: ");
	key_input = getchar();
	printf("%c\n", key_input);
	_delay_ms(200);
	if (key_input == 'q') {
		puts("Goodbye segment\n");
		return 1;
	}
	printSegment(key_input - 0x30);
	return 0;
}

int GetADC(void) {

	printf("Enter channel number [press 'q' to upper menu]: ");
	key_input = getchar();
	printf("%c\n", key_input);
	_delay_ms(200);
	if (key_input == 'q') {
		puts("Goodbye ADC\n");
		return 1;
	}
	key_input -= 0x30;
	printf("Ch[%d] = %d\n", key_input, ReadADC(key_input));
	return 0;
}

void menu(void) {
	puts("\n===================");
	puts("     Main Menu     ");
	puts("-------------------");
	puts("1. Display Segment");
	puts("2. Get ADC");
	puts("\nQ. Exit");
}

int main(void) {
	uart_init(9600UL);

	stdout = &uart_output;
	stdin = &uart_input;

	printf("Hello world!");
	while (1) {
		menu();
		printf("Choose menu : ");
		key_input = uart_getch();
		printf("%c\n", key_input);
		_delay_ms(200);
		switch (key_input) {
		case '1':
			while (!SegmentDisplay())
				;
			break;
		case '2':
			InitADC();
			while (!GetADC())
				;
			break;
		case 'q':
		case 'Q':
			puts("\nGood bye, Main\n");
			printSegment(4);
			return 0;
		default:
			printf("\n");
		}
	}
	return 0;
}
