#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#define Period	1000
#define DutyRatio 5

int main(void) {
	int High = (DutyRatio/100.0)*Period;
	int Low = Period - High;

	DDRB |= (1 << PB5);

	while (1) {
		PORTB |= (1 << PB5);
		_delay_us(High);
		PORTB &= ~(1 << PB5);
		_delay_us(Low);
	};
}
