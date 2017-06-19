/*=======================================================*/
//4장_예제4-2(c)
//
//0.5초 마다 led 시프트----------
// overflow interrupt 이용
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND[10] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90 };

int Cnt = 0;
SIGNAL(SIG_OVERFLOW1)
{
   PORTF = FND[Cnt++];
   if(Cnt > 9) Cnt = 0;
   TCNT1 = 65535-57600;
}
int main(void)
{
   DDRF = 0xFF;
   PORTF = 0xff;

   TIMSK = 0x04;			// timer1 overflow interrupt
   TCCR1B = 0x04;   		// 256 분주
   TCNT1 = 65535-57600;   	// 
   //OCR1A = 0xE100;
   sei();
   while (1)
   {
   }
}
