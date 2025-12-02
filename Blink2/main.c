/*
 * Blink.c
 *
 * Created: 2019-11-21 오후 5:31:51
 * Author : Soochan Kim
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRB = _BV(PD5);
    while (1) 
    {
		PORTB |= _BV(PB5);
		_delay_ms(1000);
		PORTB &= ~_BV(PB5);
		_delay_ms(1000);
    }
}

