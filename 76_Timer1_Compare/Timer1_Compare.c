/*=======================================================*/
//4장_예제4-2(c)
//
//0.5초 마다 led 시프트----------
// compare match interrupt 이용
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND[10] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90 };

int Cnt = 0;

SIGNAL(TIMER1_COMPA_vect)
{
   PORTF = FND[Cnt++];
   if(Cnt > 9) Cnt = 0;
}

int main(void)
{
   DDRF = 0xFF;
   PORTF = 0xff;

 TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  TIMSK |= (1 << OCIE1A); // compare


    // 1 Hz (14745600/((14399+1)*1024))
  OCR1A = 14399;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  

   sei();
   while (1)
   {
   }
}
