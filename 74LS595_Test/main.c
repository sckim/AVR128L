/*
* 74LS595_Test.c
*
* Created: 2019-10-24 오후 5:16:52
* Author : Soochan Kim
*/

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SH_CP	PB0
#define DS		PB1
#define ST_CP	PB2

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

void init595(void)
{
	// set DDRB direction as output
	sbi(DDRB, SH_CP);
	sbi(DDRB, DS);
	sbi(DDRB, ST_CP);
	
	cbi(PORTB, SH_CP);
	cbi(PORTB, DS);
	cbi(PORTB, ST_CP);
}

void Latch595(void)
{
	sbi(PORTB, ST_CP);
	_delay_loop_1(1);
	cbi(PORTB, ST_CP);
	_delay_loop_1(1);
}

void Clk595(void)
{
	sbi(PORTB, SH_CP);
	cbi(PORTB, SH_CP);
}

void Write595(unsigned char data)
{
	for(int i=0; i<8; i++) {
		if (data & 0x80) {
			sbi(PORTB, DS);
			} else {
			cbi(PORTB, DS);
		}
		Clk595();
		data <<= 1;
	}
	Latch595();
}

int main(void)
{
	init595();
	
	while(1){
		/* Replace with your application code */
		Write595(0xFF);
		_delay_ms(1000);
		Write595(0xF0);
		_delay_ms(1000);
		Write595(0x0F);
		_delay_ms(1000);
	}
}

