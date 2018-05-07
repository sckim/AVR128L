#include <avr/io.h>
#include <util/delay.h>
#include "mydef.h"

// LCD control information
#define LCD_RS	BIT0
#define LCD_RW	BIT1
#define LCD_En	BIT2

#define LCD_Busy BIT7

#define LCDControlDir	DDRC
#define LCDDataDir		DDRB

#define LCDControl		PORTC	//LCD control line
#define	LCDData			PORTB	//LCD data line

#define RS_SET         	SetBit(LCDControl,LCD_RS) 	//C포트 0번째 1    0001
#define RS_CLEAR       	ClearBit(LCDControl,LCD_RS) 	// C 포트 0번째 0
#define RW_SET         	SetBit(LCDControl,LCD_RW) 	// C포트 1번째 1   0010
#define RW_CLEAR       	ClearBit(LCDControl,LCD_RW)
#define E_SET          	SetBit(LCDControl,LCD_En) 	// C 포트 2번째 1  0100
#define E_CLEAR        	ClearBit(LCDControl,LCD_En)
//#define LIGHT_SET      	SetBit(LCDControl,3) 	//  C 포트 3번째 1 1000
//#define LIGHT_CLEAR    	ClearBit(LCDControl,3)
#define BUSY     	   	CheckBit(LCDData,LCD_Busy)   	// B포트  7 번째 1인지 검사

unsigned char display_data1[16] = "Welcome";
unsigned char display_data2[16] = "N403";

void lcd_busy() {
	LCDData = 0x00;
	do {
		E_CLEAR;
		_delay_ms(20);
		RS_CLEAR;
		RW_SET;
		E_SET;
		_delay_ms(20);
	} while (BUSY);
	E_CLEAR;
	LCDData = 0xFF;
}
void lcd_enable() {
	E_SET;
	_delay_ms(20);
	E_CLEAR;
}
void lcd_func_set() {
	RW_CLEAR;
	RS_CLEAR;
	LCDData = 0x38;
	lcd_enable();
}

// Function Set
// RS  R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// === === === === === === === === === ===
//  0   0   0   0   1   DL  N   F   *   * 
//
// DL : (1) 8bits, (0) 4bits
//
// N: Sets number of display lines
// F: Sets character font
//   display Character  Duty                             
// N F  lines    Font    Factor Remarks                    
// === ======= ========= ====== =======                    
// 0 0    1    5x 7 dots  1/8    -                         
// 0 1    1    5x10 dots  1/11   -                         
// 1 *    2    5x 7 dots  1/16  Cannot display 2 lines with 5x10 dot character font  
void lcd_command(unsigned char lcd_data) {
	lcd_busy();
	RW_CLEAR;
	RS_CLEAR;
	LCDData = lcd_data;
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
	LCDData = lcd_data;
	lcd_enable();
	RS_CLEAR;
}
void lcd_display() {
	unsigned char i;
	//LIGHT_SET;
	lcd_command(0x0E);	//디스플레이를 켜고, 커서를 꺼짐
	lcd_command(0x80);	//홈 리턴
	lcd_command(0x0c);
	for (i = 0; i < 16; i++) {
		lcd_write_char(display_data1[i]);
	}
	lcd_command(0xc0);	// 두번째 라인 시작점으로 커서 이동
	for (i = 0; i < 16; i++) {
		lcd_write_char(display_data2[i]);
	}
}
int main() {
	LCDControlDir = 0xff;	// LCD Data port를 출력으로 설정
	LCDDataDir = 0xff;	// LCD 제어라인

	LCDControl = 0x00;

	lcd_init();
	lcd_display();
	while (1) {
	};

}
