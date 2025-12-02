/*
* Check_databss.c
*
* Created: 2020-04-14 오후 10:26:28
* Author : Soochan Kim
*/

#include <avr/io.h>

void mdelay(int n)
{
	for(int i=0;i<n;i++)
		asm ("nop");
}

int main(void) {
	char* str="0123456789";
	int i = 0;
	
	DDRB = 0xF0;
	str[0] = 'A';
	while(1)	{
		i++;
		PORTB = 0xF0;
		mdelay(10);
		PORTB = 0x0F;
		mdelay(10);
	}
	return 1;
}
