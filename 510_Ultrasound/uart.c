#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

#ifndef BAUD
#define BAUD 9600
#endif

#include <util/setbaud.h>

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */
void InitUART(unsigned long iBaudrate) {

	// UCSRnA 레지스터를 초기화시킨다.
	// 0번째 비트, 즉 MPCMn 를 0으로 세트 (USARTn을 멀티 프로세서 통신모드로 설정)
	UCSR0A = 0x00;

	// UCSRnB 레지스터를 이용하여 송신 및 수신 사용설정을 한다.
	// Rx, Tx enable
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// 3번째, 4번째 비트 세트 즉, TXENn (USARTn모듈의 송신부 동작 enable) RXENn (USARTn모듈의 수신부 동작 enable)
	//  2번 비트 UCSZ02 = 0으로 세트

	// UCRnC 레지스터를 이용하여 모드(동기/비동기), 패리티모드, 정지비트,
	// 전송 데이터 비트수를 설정한다.
	// 비동기 방식, No Parity bit, 1 Stop bit, 8bits
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);

	// See http://wormfood.net/avrbaudcalc.php
	// UBRRnH(L) 레지스터를 이용한 송수신 보레이트 설정
	UBRR0H = 0x00;
	switch (iBaudrate) {
	case 9600:
		//UBRR0L = 95; // 14.7456 MHz -> 9600 bps
		UBRR0L = 103; // 16 MHz -> 9600 bps
		break;
	case 19200:
		UBRR0L = 47; // 14.7456 MHz -> 19200 bps
		break;
	case 115200:
		//UBRR0L = 7;  // 14.7456 MHz -> 115200 bps
		UBRR0L = 8;  // 16 MHz -> 115200 bps
		break;
	default:
		UBRR0L = 95;
	}
}

void UART_putch(unsigned char data) {
	//전송준비가 될 때까지 대기
	while ((UCSR0A & (1 << UDRE0)) == 0)
		;
	// while(!(UCSR0A & 0x20)) ;

	UDR0 = data;
}

void UART_putchar(unsigned char data, FILE *stream) {
	if (data == '\n') {
		UART_putchar('\r', stream);
	}
	loop_until_bit_is_set(UCSR0A, UDRE0);

	UDR0 = data;
}

unsigned char UART_getch(void) {
	loop_until_bit_is_set(UCSR0A, RXC0);

	return UDR0;
}

unsigned char UART_getchar(FILE *stream) {
	loop_until_bit_is_set(UCSR0A, RXC0);

	return UDR0;
}

void UART_putString(char *data) {
	while (*data != '\0')
		UART_putch(*data++);
}
// End while( *data != '\0' )

char *UART_getString(void) {
	unsigned char i = 0;
	char key_input;

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
