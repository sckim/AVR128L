#include <avr/io.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

char getch(void) {
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

int putch (char data) {
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = data;
	return 0;
}

int main(void) {
	char recieved_byte;
	unsigned char text[] =
				"\r\nWelcome! Serial communication world!!\r\n Good Luck\r\n";
	unsigned char echo[] = "HKNU >> ";
	int i;

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;

	i=0;
	while (text[i] != '\0') {
		putch(text[i++]);
	}

	i=0;
	while (echo[i] != '\0') {
		putch(echo[i++]);
	}

	for (;;) {
		recieved_byte = getch();
		putch(recieved_byte);
	}
	return 0; // never reached
}
