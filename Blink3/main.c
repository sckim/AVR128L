/*
 * Blink3.c
 *
 * Created: 2019-11-07 오후 3:16:38
 * Author : Soochan Kim
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h

int main(void)
{
	DDRD = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		PORTD = 0;
		_delay_ms(10);
		for(int i=0; i<8; i++)	{
			PORTD |= _BV(i);
			_delay_ms(10);
		}
    }
}

