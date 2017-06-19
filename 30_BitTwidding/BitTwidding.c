#include <avr/io.h>

#define setBit(byte, bit) 		(byte |= _BV(bit))
#define clearBit(byte, bit)		(byte &= ~_BV(bit)) 
#define toggleBit(byte, bit) 	(byte ^= _BV(bit))

void delay(unsigned int ti)
{
	while(--ti);
}

int main(void)
{
	volatile unsigned char uA;

	DDRA = 0xff;

	uA = 0x03;

	uA = 0x03<<1;

	uA = 0x03<<2;

//	sbit(uA, 1);

	uA |= (1<<2);

	uA |= (1<<6);

	uA &= ~(1<<6);

	uA ^= (1<<2);

	uA ^= (1<<2);

	uA ^= _BV(2);

	setBit(uA, 6);

	while(1){
		bit_is_set(PORTA, 1);
		delay(10000);
		bit_is_clear(PORTA, 1);
		delay(10000);
	}

	return 0;
}
