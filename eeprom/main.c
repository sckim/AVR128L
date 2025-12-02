/*
* Library를 이용한 시리얼 통신
*
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "uart.h"

void uart_printf(char data, FILE * stream)
{
	uart_putc(data);
}

unsigned char uart_scanf(FILE * stream)
{
	return uart_getc();
}

//새로운 standard io를 지정한다.
static FILE std_output = FDEV_SETUP_STREAM(uart_printf, NULL, _FDEV_SETUP_WRITE);
static FILE std_input = FDEV_SETUP_STREAM(NULL, uart_scanf, _FDEV_SETUP_READ);

volatile uint16_t eepromaddress;
unsigned int start = 0;
uint8_t	ch = 0;

void EEPROM_write(void) {
	unsigned int addr = 0;

	for (addr = start; addr < start+0x20; addr++) {
		//eeprom_write_byte((uint8_t*) addr, ch);
		eeprom_update_byte((uint8_t*) addr, ch);
		printf("W: %d @ %d\r\n", ch+=2, addr);
	}
}
void EEPROM_read(void) {
	unsigned char rw8;
	unsigned int addr = 0;

	for (addr = start; addr < start+30; addr++) {
		rw8 = eeprom_read_byte((uint8_t*) addr);
		printf("R %d @ %d\r\n", rw8, addr);
	}
}

int main(void) {
	uint8_t add;
	uint8_t value;

	//stdout과 stdin에 사용자가 정의한 함수로 설정
	//아래 2줄은 main 함수 밖에 작성하면 오류가 발생하므로 주의
	stdout = &std_output;
	stdin = &std_input;

	uart_init(UART_BAUD_SELECT(9600, 16000000L));
	sei();

	//	PORTB ^= _BV(5);
	printf("%s\r", "Previous EEprom data");
	EEPROM_read();
	_delay_ms(5000);

	printf("%s\r", "New EEprom data");
	EEPROM_write();
	_delay_ms(5000);
	
	printf("%s\r", "Check EEprom data");
	EEPROM_read();

	_delay_ms(1000);
	return 0; // never reached
}