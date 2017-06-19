#include <avr/io.h>
#include <avr/interrupt.h>

int Index = -1;
unsigned char SEG[10]= {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90};

// 인터럽트 수행 함수는 아래와 같이
// SIGNAL(SIG_INTERRUPTn)으로 하여 n이 인터럽트 번호
SIGNAL(SIG_INTERRUPT0)
{
   Index++;
   if (Index >= 10) Index = 0;

   PORTF = SEG[Index];    
   
} //인터럽트 실행문

SIGNAL(SIG_INTERRUPT1)
{
   Index--;
   if (Index < 0) Index = 9;
   
   PORTF = SEG[Index];    
} //인터럽트 실행문

int main(void)
{
    DDRF  = 0XFF;
    PORTF = 0xFF;
  
    EIMSK = 0b00000011;      //INT0 번, INT1번 사용 설정
    //EIMSK = 0x01;
    EICRA = 0b00001010;       //INT0 하강모서리에서 동작되도록 설정(0번,1번 인터럽트)
    //EICRA = 0x02;
    SREG = 0b10000000;
    //SREG = 0x80;


    while(1) //프로그램이 끝나지않게 하기위한  무한반복문
    { 
    }
}
