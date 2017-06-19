#include <avr/io.h>
#include <util/delay.h>

#define sbit(x,y)      (x|=(1<<y))  	// y번째 비트 1
#define cbit(x,y)      (x&=~(1<<y)) 	// y번째 비트 0

#define RS_SET         sbit(PORTC,0) 	//C포트 0번째 1    0001
#define RS_CLEAR       cbit(PORTC,0) 	// C 포트 0번째 0
#define RW_SET         sbit(PORTC,1) 	// C포트 1번째 1   0010
#define RW_CLEAR       cbit(PORTC,1)
#define E_SET          sbit(PORTC,2) 	// C 포트 2번째 1  0100
#define E_CLEAR        cbit(PORTC,2)
#define LIGHT_SET      sbit(PORTC,3) 	//  C 포트 3번째 1 1000
#define LIGHT_CLEAR    cbit(PORTC,3)
#define BUSY     	   bit_is_set(PINB,7)   	// B포트  7 번째 1인지 검사

unsigned char display_data1[] = "Welcome";
unsigned char display_data2[] = "N403";
void lcd_busy() {
	DDRB = 0x00;
	do {
		E_CLEAR;
		_delay_ms(20);
		RS_CLEAR;
		RW_SET;
		E_SET;
		_delay_ms(20);
	} while (BUSY);
	E_CLEAR;
	DDRB = 0xFF;
}
void lcd_enable() {
	E_SET;
	_delay_ms(20);
	E_CLEAR;
}
void lcd_func_set() {
	RW_CLEAR;
	RS_CLEAR;
	PORTB = 0x38;
	lcd_enable();
}
void lcd_command(unsigned char lcd_data) {
	lcd_busy();
	RW_CLEAR;
	RS_CLEAR;
	PORTB = lcd_data;
	lcd_enable();
}
void lcd_init() // lcd 초기화
{
	E_CLEAR;
	_delay_ms(20);
	lcd_func_set();
	_delay_ms(20);
	lcd_func_set();
	_delay_ms(20);
	lcd_func_set();
	_delay_ms(20);
	lcd_command(0x3C);
	lcd_command(0x08);
	lcd_command(0x01);
	lcd_command(0x06);
}
void lcd_write_char(unsigned char lcd_data) {
	lcd_busy();
	RW_CLEAR;
	RS_SET;
	PORTB = lcd_data;
	lcd_enable();
	RS_CLEAR;
}
void lcd_display() {
	unsigned char i;
	LIGHT_SET;
	lcd_command(0x0C);
	lcd_command(0x02);
	for (i = 0; i < 16; i++) {
		lcd_write_char(display_data1[i]);
	}
	lcd_command(0xc0);
	for (i = 0; i < 16; i++) {
		lcd_write_char(display_data2[i]);
	}
}
int main() {
	DDRB = 0xff;
	DDRC = 0xff;
	PORTC = 0x00;
	lcd_init();
	lcd_display();
	while (1) {
	};

}
