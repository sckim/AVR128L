// this code sets up counter1 A output at 25% and B output at 75%
// using ICR1 as top (16bit), Fast PWM.

#include <avr/io.h>

int main(void) {
	DDRB |= (1 << DDB1) | (1 << DDB2);
	// PB1 and PB2 is now an output

	ICR1 = 0xFFFF;
	// set TOP to 16bit

	OCR1A = 0x3FFF;
	// set PWM for 25% duty cycle @ 16bit
	OCR1B = 0x3FFF;
	// set PWM for 75% duty cycle @ 16bit

	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	// set none-inverting mode

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	// set Fast PWM mode using ICR1 as TOP

	TCCR1B |= (1 << CS10);
	// START the timer with no prescaler

	while (1)
	;
	{
		// we have a working Fast PWM
	}
}
