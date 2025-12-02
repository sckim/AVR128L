/*
* Library를 이용한 시리얼 통신
*
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
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

int main(void) {
	char recieved_byte;
	char text[] =
	"\r\nWelcome! Serial communication world!!\r\n Good Luck\r\n";
	char echo[] = "HKNU >> ";

	//stdout과 stdin에 사용자가 정의한 함수로 설정
	//아래 2줄은 main 함수 밖에 작성하면 오류가 발생하므로 주의
	stdout = &std_output;
	stdin = &std_input;

	uart_init(UART_BAUD_SELECT(19200, 16000000L));
	sei();

	printf("%s", text);

	//	uart_puts(echo);
	printf("%s", echo);

	for (;;) {
		scanf("%c", &recieved_byte);
		_delay_ms(50);
		//uart_putc(re;k;kcieved_byte);
		if( recieved_byte==0x0D)
			printf("\r\n%s", echo);
		else if (recieved_byte!=0)
			printf("%c", recieved_byte);

	}
	return 0; // never reached
}