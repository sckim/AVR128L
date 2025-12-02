/*=======================================================*/
// INT0(PD2), INT1(PD3)를 활성화
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

int Index = 0;

// 인터럽트 수행 함수는 아래와 같이
// SIGNAL(SIG_INTERRUPTn)으로 하여 n이 인터럽트 번호
//ISR(INT0_vect)
ISR(INT0_vect)
{
	PORTB ^= _BV(PB4);
}

ISR(INT1_vect) {
	PORTB ^= _BV(PB5);
}

int main(void) {
	DDRB |= (1<<PB4 | 1<<PB5);

	//DDRD &= ~(_BV(PD2) | _BV(PD3));
	PORTD |= (_BV(PD2) | _BV(PD3));

	EIMSK = 0b00000011;		//INT0 번 사용 설정
	//EIMSK = 0x01;
	EICRA = 0b00001010; 	//INT0 하강모서리에서 동작되도록 설정
	//EIMSK = 0x02;
	SREG = 0b10000000;
	//sei();
	//SREG = 0x80;
	while (1) {
	}
}
