/*
 * main.c
 *
 *  Created on: 2017. 10. 27.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

unsigned char text[] =
		"\r\nWelcome!\r\n";

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define NOT_ON_TIMER 0
#define TIMER0A 1
#define TIMER0B 2
#define TIMER1A 3
#define TIMER1B 4
#define TIMER1C 5
#define TIMER2  6
#define TIMER2A 7
#define TIMER2B 8

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

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = 14; // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ADC_init() {
	// For Aref=AVcc;
	ADMUX = (1 << REFS0);
	//Rrescalar div factor =128
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ReadADC(uint8_t ch) {
	//clear mux channel
	ADMUX &= 0xF8;
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

void analogWriteB(int pin, int val) {
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.
	sbi(DDRB, pin);
	if (val == 0) {
		cbi(PORTB, pin);
	} else if (val == 255) {
		sbi(PORTB, pin);
	} else {
		switch (pin) {
		case 1:
			// connect pwm to pin on timer 1, channel A
			sbi(TCCR1A, COM1A1);
			OCR1A = val; // set pwm duty
			break;
		case 2:
			// connect pwm to pin on timer 1, channel B
			sbi(TCCR1A, COM1B1);
			OCR1B = val; // set pwm duty
			break;
		case 3:
			// connect pwm to pin on timer 2, channel A
			sbi(TCCR2A, COM2A1);
			OCR2A = val; // set pwm duty
			break;
		case NOT_ON_TIMER:
		default:
			if (val < 128) {
				cbi(PORTB, pin);
			} else {
				sbi(PORTB, pin);
			}
		}
	}
}

void PWM_init() {
	//sei();

	// Timer 0
	// FastPWM
	sbi(TCCR0A, WGM01);
	sbi(TCCR0A, WGM00);

	// set timer 0 prescale factor to 64
	sbi(TCCR0B, CS01);
	sbi(TCCR0B, CS00);

	// enable timer 0 overflow interrupt
	sbi(TIMSK0, TOIE0);

	// timers 1 and 2 are used for phase-correct hardware pwm
	// this is better for motors as it ensures an even waveform
	// note, however, that fast pwm mode can achieve a frequency of up
	// 8 MHz (with a 16 MHz clock) at 50% duty cycle
	TCCR1B = 0;

	// set timer 1 prescale factor to 64
	sbi(TCCR1B, CS11);
	sbi(TCCR1B, CS10);
	// put timer 1 in 8-bit phase correct pwm mode
	sbi(TCCR1A, WGM10);

	// set timer 2 prescale factor to 64
	sbi(TCCR2B, CS22);

	// configure timer 2 for phase correct pwm (8-bit)
	sbi(TCCR2A, WGM20);
}

// the loop function runs over and over again forever
void loop(void) {

	sbi(PORTB, 5);
	_delay_ms(100);              // wait for a second
	cbi(PORTB, 5);    // turn the LED off by making the voltage LOW
	_delay_ms(100);

	sensorValue = ReadADC(0);
	outputValue = (int) map(sensorValue, 0, 1023, 0, 255);

	printf("Ch[%d] = %d, Output %d\r\n", 0, sensorValue, outputValue);

	// change the analog out value:
	analogWriteB(1, outputValue);
	analogWriteB(2, outputValue);
	analogWriteB(3, 255-outputValue);
}

void Display_menu(void)
{
	int i=0;

	while (text[i] != '\0') {
		putch(text[i++]);
		_delay_ms(40);
	}
}

void setup(void) {
	uart_init(9600UL);
	stdout = &PrnDevice;

	PWM_init();
	ADC_init();

	// initialize digital pin 13 as an output.
	sbi(PORTB, 5);

}

int main(void) {
	setup();
	Display_menu();

	for (;;) {
		loop();
	}

	return 0;
}
