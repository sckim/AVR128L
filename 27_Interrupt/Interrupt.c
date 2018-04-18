/*=======================================================*/
// 외부 인터럽트를 이용한 7 segment 값 변경
// INT0 (PD0)를 활성화
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned int Index = 0;
unsigned char SEG[10]= {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90};

// 인터럽트 수행 함수는 아래와 같이
// SIGNAL(SIG_INTERRUPTn)으로 하여 n이 인터럽트 번호
SIGNAL(SIG_INTERRUPT0)
{
	PORTF = SEG[Index++];    
	if (Index == 10) Index = 0;
}

int main(void)
{
    DDRF  = 0XFF;
    PORTF = 0xFF;
  
    EIMSK = 0b00000001;		//INT0 번 사용 설정
    //EIMSK = 0x01;
    EICRA = 0b00000010; 	//INT0 하강모서리에서 동작되도록 설정
    //EIMSK = 0x02;
    SREG = 0b10000000;
    //SREG = 0x80;

    while(1)
    { 
    }
}
