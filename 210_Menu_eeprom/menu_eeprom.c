#include <avr/io.h>
//#include <stdio.h>
//#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "uart.h"
#include "adc.h"


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

	return (char *) str;
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
	puts("3. Write EEPROM");
	puts("4. Read EEPROM");
	puts("\nQ. Exit");
}

volatile uint16_t eepromaddress;

int writeEEPROM(void) {
	unsigned int addr = 0;
	char *ch;

	printf("Enter memory address to write: ");
	ch = GetString();

	if (ch[0] == 'q') {
		puts("Goodbye EERPOM\n");
		ch[0] = 0;
		return 1;
	}

	addr = atoi(ch);
	if (addr > E2END) {
		printf("Out of memory");
		return 1;
	}
	printf("Enter byte data: ");
	ch = GetString();

	eeprom_write_byte((uint8_t*) addr, atoi(ch));
	printf("R/W %d @ %d\r\n", atoi(ch), addr);

	return 0;
}

int readEEPROM(void) {
	unsigned char rw8;
	unsigned int addr = 0;
	char *ch;

	printf("Enter memory address to read: ");
	ch = GetString();
	if (ch[0] == 'q') {
		puts("Goodbye EERPOM\n");
		ch[0] = 0;
		return 1;
	}

	addr = atoi(ch);
	if (addr > E2END) {
		printf("Out of memory");
		return 1;
	}

	rw8 = eeprom_read_byte((uint8_t*) addr);

	printf("R/W %d @ %d\r\n", rw8, addr);
	if (key_input == 'q') {
		puts("Goodbye EERPOM\n");
		return 1;
	}

	return 0;
}

int main(void) {
	uart_init(9600UL);
	printSegment(eeprom_read_byte(0)-0x30);

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
		case '3':
			while (!writeEEPROM())
				;
			break;
		case '4':
			while (!readEEPROM())
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
