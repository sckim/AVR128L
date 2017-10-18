/*
 * ADC_hold.c
 *
 *  Created on: 2016. 5. 25.
 *      Author: Soochan Kim
 */
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define strWelcome	"Welcome"
#define strWelcome1	"Microcontroller"

void putch(unsigned char data) {
	//전송준비가 될 때까지 대기
	while ((UCSR0A & (1 << UDRE0)) == 0)
		;
	// while(!(UCSR0A & 0x20)) ;

	UDR0 = data;
}

void printfStr(char data, FILE * stream) {
//void putch(unsigned char data) {
	//전송준비가 될 때까지 대기
	while ((UCSR0A & (1 << UDRE0)) == 0)
		;
	// while(!(UCSR0A & 0x20)) ;

	UDR0 = data;
}

unsigned char getch() {
	unsigned char data;

	//데이터를 받을 때까지 대기
	while ((UCSR0A & (1 << RXC0)) == 0)
		;

	//while (bit_is_set(UCSR0A,RXC0);
	//while (!(UCSR0A & 0x80);

	// Receiver register에 보내고자 하는 데이터를 저장
	data = UDR0;

	return data;
}

#define USART_BAUDRATE 115200
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

void uart_init(unsigned long iBaudrate) {

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
		//UBRR0L = 47; // 14.7456 MHz -> 19200 bps
		UBRR0L = 51; // 16 MHz ->
		break;
	case 115200:
		//UBRR0L = 7;  // 14.7456 MHz -> 115200 bps
		UBRR0L = 8;  // 16 MHz -> 115200 bps
		break;
	default:
		UBRR0L = 95;
	}

//	UBRR0H = (BAUD_PRESCALE >> 8);
//	UBRR0L = BAUD_PRESCALE;
}

static FILE PrnDevice = FDEV_SETUP_STREAM(printfStr, NULL, _FDEV_SETUP_WRITE);

void InitADC() {
	// For Aref=AVcc;
	ADMUX = (1 << REFS0);
	//Rrescalar div factor =128
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ReadADC(uint8_t ch) {
	//Select ADC Channel ch must be 0-7
	ADMUX &= 0xF0;
	ADMUX |= (ch & 0x07);

	//Start Single conversion
	ADCSRA |= (1 << ADSC);

	//Wait for conversion to complete
	while (!(ADCSRA & (1 << ADIF)))
		;

	//Clear ADIF by writing one to it
	//Note you may be wondering why we have write one to clear it
	//This is standard way of clearing bits in io as said in datasheets.
	//The code writes '1' but it result in setting bit to '0' !!!
	ADCSRA |= (1 << ADIF);

	return (ADC);
}

#define nChs 6

int main(void) {
	int temp[nChs];
	float voltage[nChs];

	unsigned char text[] =
			"\r\nWelcome! Serial communication world!!\r\n Good Luck\r\n";

	uart_init(9600UL);
	stdout = &PrnDevice;

	DDRB = 0xFF;

	PORTB = 0;

	InitADC();

	while (1) {
		PORTB = 0x00;
		for (int loop = 0; loop < nChs; loop++) {
			temp[loop] = ReadADC(loop);
			voltage[loop] = (temp[loop] / 1023.0) * 5.0;
			printf("Ch[%d] = %d, %3.2f[V]\r\n", loop, temp[loop], voltage[loop]);
			_delay_ms(100);
		}
		PORTB = 0xFF;
		_delay_ms(100);
	}
}
