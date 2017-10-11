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

#define USART_BAUDRATE 9600
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
	/*
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
	 */
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;
}

static FILE PrnDevice = FDEV_SETUP_STREAM(printfStr, NULL, _FDEV_SETUP_WRITE);

int main() {
	unsigned char text[] =
			"\r\nWelcome! Serial communication world!!\r\n Good Luck\r\n";
	unsigned char echo[] = "HKNU >> ";
	unsigned char i = 0;

	DDRB = 0xff;
	DDRC = 0x00;

	uart_init(9600UL);
	stdout = &PrnDevice;

	while (text[i] != '\0') {
		putch(text[i++]);
		_delay_ms(40);
	}
	i = 0;
	while (echo[i] != '\0')
		putch(echo[i++]);

	printf("%s", text);
	printf("%s", echo);

	i = 0;
	while (1) {
		printf("i:%3d  %.3f\r\n", i++, i + 1.1);
		//sprintf(text, "i:%3d  %.3f", i, i + 1.1);
		_delay_ms(1000);
		if (i > 10)
			i = 0;
	};

	return 0;
}
