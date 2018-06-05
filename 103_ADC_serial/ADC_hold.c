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
	//�����غ� �� ������ ���
	while ((UCSR0A & (1 << UDRE0)) == 0)
		;
	// while(!(UCSR0A & 0x20)) ;

	UDR0 = data;
}

void printfStr(char data, FILE * stream) {
//void putch(unsigned char data) {
	//�����غ� �� ������ ���
	while ((UCSR0A & (1 << UDRE0)) == 0)
		;
	// while(!(UCSR0A & 0x20)) ;

	UDR0 = data;
}

unsigned char getch() {
	unsigned char data;

	//�����͸� ���� ������ ���
	while ((UCSR0A & (1 << RXC0)) == 0)
		;

	//while (bit_is_set(UCSR0A,RXC0);
	//while (!(UCSR0A & 0x80);

	// Receiver register�� �������� �ϴ� �����͸� ����
	data = UDR0;

	return data;
}

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

void uart_init(unsigned long iBaudrate) {

	// UCSRnA �������͸� �ʱ�ȭ��Ų��.
	// 0��° ��Ʈ, �� MPCMn �� 0���� ��Ʈ (USARTn�� ��Ƽ ���μ��� ��Ÿ��� ����)
	UCSR0A = 0x00;

	// UCSRnB �������͸� �̿��Ͽ� �۽� �� ���� ��뼳���� �Ѵ�.
	// Rx, Tx enable
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// 3��°, 4��° ��Ʈ ��Ʈ ��, TXENn (USARTn����� �۽ź� ���� enable) RXENn (USARTn����� ���ź� ���� enable)
	//  2�� ��Ʈ UCSZ02 = 0���� ��Ʈ

	// UCRnC �������͸� �̿��Ͽ� ���(����/�񵿱�), �и�Ƽ���, ������Ʈ,
	// ���� ������ ��Ʈ���� �����Ѵ�.
	// �񵿱� ���, No Parity bit, 1 Stop bit, 8bits
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);
	/*
	 // UBRRnH(L) �������͸� �̿��� �ۼ��� ������Ʈ ����
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
	 */
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;
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

int main(void) {
	int temp;
	float voltage;

	unsigned char text[] =
	"\r\nWelcome! Serial communication world!!\r\n Good Luck\r\n";

	uart_init(9600UL);
	stdout = &PrnDevice;

	DDRB = 0xFF;

	PORTB = 0;

	InitADC();

	while (1) {
		PORTB = 0x00;
		temp = ReadADC(0);

		voltage = (temp / 1023.0) * 5.0;
		//printf("Ch[0] = %d\r\n", temp);

		printf("Ch[0] = %d, %3.2f\r\n", temp, voltage);
		_delay_ms(100);
		PORTB = 0xFF;
		_delay_ms(100);
	}
}

