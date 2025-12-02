///*************************************
// * Purpose: Timer0을 이용한 OC0A(PD6)에 PWM 생성
// *
// *
// *************************************/
#define F_CPU	16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer0.h"

#define DutyRatio	20
#define DutyValue (DutyRatio / 100.0 * 256)

int main(void)
{
	// OCPD6 is now an output
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);	

	OCR0A = DutyValue;
	OCR0B = 2*DutyValue;
	// set PWM for 50% duty cycle

	Timer0Mode(FPWM);		 // Compare capture mode
	Timer0Prescaler(1024);	 // 16MHz/256 => 1 step = 16us
	Timer0OutputMode(NonInvert);
	
	TCCR0A |= (1 << COM0B1);
	TCCR0A &= ~(1 << COM0B0);

	while (1);
	{
		// we have a working Fast PWM
	}
}