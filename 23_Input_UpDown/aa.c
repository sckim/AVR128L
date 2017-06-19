#include <avr/io.h>
#include <util/delay.h>
int main(void) {
	DDRF = 0XFF;  // F포트에 출력 설정
	chart SEG[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98,
			0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E }; // 0부터 F까지 설정 (표 첨부)
	int num = 0;  // 초기값 0으로 설정

	while (1) {             // while 구문 사용해 반복 설정
		PORTF = SEG[num++]; // 세그먼트 입력되는 코드 하나씩 순서대로 작동
		if (num == 16)          //  16번째 코드 작동시
			num = 0;              // 다시 0으로 초기화
		_delay_ms(500);  // 500ms 지연시간 설정
	}
}
