/*************************************
* Purpose: Understand GPIO registers
*
* DDRn
* PORTn
*************************************/

// delay 함수를 이용하기 위해서는 기준 시간이 필요하므로
// CPU의 메인 클럭에 대한 정보가 필요하다.
//
// # warning "F_CPU not defined for <util/delay.h>"
//
// 아래와 같은 warning을 없애기 위해서는 소스 크드에
// F_CPU를 선언해 주거나, 환경설정에서 선언해 준다.
//#define F_CPU	14745600

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	//PORTB의 모든 포터를 모두 출력으로 설정
	DDRB = 0xFF; 

	while(1)	{
		//PORTB의 상위 4비트에는 1을, 하위 4비트에는 0으로 설정
		PORTB = 0xF0; 
		//1초간 지연
		_delay_ms(1000); 

		PORTB = 0x0F;
		_delay_ms(1000);
	}
}
