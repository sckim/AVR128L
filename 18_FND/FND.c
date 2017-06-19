/*=======================================================*/
//4장_예제4-3(e)
//
//시계만들기
//타이머1
//분주비 256
//초기값 3036(0X0BDC)
/*=======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>

#define FNDOutDDR DDRC
#define FNDOutPort PORTC

#define FNDGateDDR DDRB
#define FNDGatePort PORTB

unsigned char FND[10] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80,
		0X90 };
unsigned char GateSig[4] = { 0xE0, 0xD0, 0xB0, 0x70 };

int ShiftInx = 0;

int main(void) {
	FNDOutDDR = 0XFF;
	FNDGateDDR = 0xFF;
	FNDOutPort = FND[0];
	TIMSK = 0b00000101;  /// T1, T0

	// Normal, 1/1024 for 프리스케일
	TCCR0 = 0x07;
	TCNT0 = 0x00;  //초기값

	TCCR1A = 0x00; //normal
	TCCR1B = 0x04; //프리스케일 : 1024
	//TCNT1 = 0x10000-14400;
	TCNT1 = 0x10000-57600;  // prescale 256

	sei();
	while (1) {
	}
}
