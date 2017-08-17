/*
 Quick and dirty functions that make serial communications work.

 Note that receiveByte() blocks -- it sits and waits _forever_ for
 a byte to come in.  If you're doing anything that's more interesting,
 you'll want to implement this with interrupts.

 initUSART requires BAUDRATE to be defined in order to calculate
 the bit-rate multiplier.  9600 is a reasonable default.

 May not work with some of the older chips:
 Tiny2313, Mega8, Mega16, Mega32 have different pin macros
 If you're using these chips, see (e.g.) iom8.h for how it's done.
 These old chips don't specify UDR0 vs UDR1.
 Correspondingly, the macros will just be defined as UDR.
 */

#include <avr/io.h>
#include "USART.h"
#include <util/setbaud.h>

void uart_init(unsigned long iBaudrate) {
	// UBRRnH(L) 레지스터를 이용한 송수신 보레이트 설정
	UBRR0H = 0x00;
	switch (iBaudrate) {
	case 9600:
		UBRR0L = 95; // 14.7456 MHz -> 9600 bps
		break;
	case 19200:
		UBRR0L = 47; // 14.7456 MHz -> 19200 bps
		break;
	case 115200:
		UBRR0L = 7;  // 14.7456 MHz -> 115200 bps
		break;
	default:
		UBRR0L = 95;
	}

#if USE_2X
	UCSR0A |= (1 << U2X0);
#else
	UCSR0A &= ~(1 << U2X0);
#endif
	/* Enable USART transmitter/receiver */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
}

void putch(uint8_t data) {
	/* Wait for empty transmit buffer */
	loop_until_bit_is_set(UCSR0A, UDRE0);

	UDR0 = data; /* send data */
}

uint8_t getch(void) {
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait for incoming data */

	return UDR0; /* return register value */
}

/* Here are a bunch of useful printing commands */

void printString(const char myString[]) {
	uint8_t i = 0;
	while (myString[i]) {
		putch(myString[i]);
		i++;
	}
}

void readString(char myString[], uint8_t maxLength) {
	char response;
	uint8_t i;
	i = 0;
	while (i < (maxLength - 1)) { /* prevent over-runs */
		response = getch();
		putch(response); /* echo */
		if (response == '\r') { /* enter marks the end */
			break;
		} else {
			myString[i] = response; /* add in a letter */
			i++;
		}
	}
	myString[i] = 0; /* terminal NULL character */
}

void printByte(uint8_t byte) {
	/* Converts a byte to a string of decimal text, sends it */
	putch('0' + (byte / 100)); /* Hundreds */
	putch('0' + ((byte / 10) % 10)); /* Tens */
	putch('0' + (byte % 10)); /* Ones */
}

void printWord(uint16_t word) {
	putch('0' + (word / 10000)); /* Ten-thousands */
	putch('0' + ((word / 1000) % 10)); /* Thousands */
	putch('0' + ((word / 100) % 10)); /* Hundreds */
	putch('0' + ((word / 10) % 10)); /* Tens */
	putch('0' + (word % 10)); /* Ones */
}

void printBinaryByte(uint8_t byte) {
	/* Prints out a byte as a series of 1's and 0's */
	uint8_t bit;
	for (bit = 7; bit < 255; bit--) {
		if (bit_is_set(byte, bit))
			putch('1');
		else
			putch('0');
	}
}

char nibbleToHexCharacter(uint8_t nibble) {
	/* Converts 4 bits into hexadecimal */
	if (nibble < 10) {
		return ('0' + nibble);
	} else {
		return ('A' + nibble - 10);
	}
}

void printHexByte(uint8_t byte) {
	/* Prints a byte as its hexadecimal equivalent */
	uint8_t nibble;
	nibble = (byte & 0b11110000) >> 4;
	putch(nibbleToHexCharacter(nibble));
	nibble = byte & 0b00001111;
	putch(nibbleToHexCharacter(nibble));
}

uint8_t getNumber(void) {
	// Gets a numerical 0-255 from the serial port.
	// Converts from string to number.
	char hundreds = '0';
	char tens = '0';
	char ones = '0';
	char thisChar = '0';
	do { /* shift over */
		hundreds = tens;
		tens = ones;
		ones = thisChar;
		thisChar = getch(); /* get a new character */
		putch(thisChar); /* echo */
	} while (thisChar != '\r'); /* until type return */
	return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}
