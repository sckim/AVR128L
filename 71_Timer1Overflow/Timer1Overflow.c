/*************************************
* Purpose: Timer1을 이용하여 1초마다 overflow
* interrupt에 의한 LED Shift
*
* TIMSK
* TCCR1B
* TCNT1
*************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

#define cOneSecond	14400

unsigned char LED_ARRAY[9] = { 0xff, 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf,
		0x7f };
unsigned char FND[10] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90 };

volatile unsigned int index = 0;

ISR (TIMER1_OVF_vect)	{
// SIGNAL은 AVR studio v.7에서는 컴파일 안 됨
// SIGNAL(SIG_OVERFLOW1) {
	PORTA = LED_ARRAY[index];
	PORTF = FND[index];
	
	index++;
	if (index == 9)
		index = 0;
	TCNT1 = 0xFFFF - cOneSecond + 1;
}

int main(void) {
	DDRA = 0xFF;
	DDRF = 0xFF;

	cli();
	// TOIE1: Timer Overflow Interrupt Enable (Timer 1);
	// If this bit is set and if global interrupts are enabled, the micro will jump to // the Timer Overflow 1 interrupt vector upon Timer 1 Overflow.
	TIMSK |= (1 << TOIE1);
	//TIMSK = 0x04;
	
	/* Clock Seclects bits
	CS12	CS11	CS10	Mode Description
	000: Stop Timer/Counter 1
	001: No Prescaler (Timer Clock = System Clock)
	010: divide clock by 8
	011: divide clock by 64
	100: divide clock by 256
	101: divide clock by 1024
	110: increment timer 1 on T1 Pin falling edge
	111: increment timer 1 on T1 Pin rising edge
	*/
	TCCR1B |= (1<<CS12);
	TCCR1B |= (1<<CS10);  // /1024

	TCNT1 = 0xFFFF - cOneSecond + 1;

	sei();
    //SREG |= 0b10000000;

	while (1) {
	};
}
