/*************************************
* Purpose: Understand GPIO registers
*
* DDRn
* PORTn
*************************************/

// delay �Լ��� �̿��ϱ� ���ؼ��� ���� �ð��� �ʿ��ϹǷ�
// CPU�� ���� Ŭ���� ���� ������ �ʿ��ϴ�.
//
// # warning "F_CPU not defined for <util/delay.h>"
//
// �Ʒ��� ���� warning�� ���ֱ� ���ؼ��� �ҽ� ũ�忡
// F_CPU�� ������ �ְų�, ȯ�漳������ ������ �ش�.
//#define F_CPU	14745600

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	//PORTB�� ��� ���͸� ��� ������� ����
	DDRB = 0xFF; 

	while(1)	{
		//PORTB�� ���� 4��Ʈ���� 1��, ���� 4��Ʈ���� 0���� ����
		PORTB = 0xF0; 
		//1�ʰ� ����
		_delay_ms(1000); 

		PORTB = 0x0F;
		_delay_ms(1000);
	}
}
