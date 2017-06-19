/*
 * textLCD3.c
 *
 *  Created on: 2016. 4. 29.
 *      Author: Soochan Kim
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SetBit(x,y)		(x |= (1<<y))
#define ClearBit(x,y)	(x &= ~(1<<y))

#define CheckBit(x,y)	(x & (1<<y))

//LCD Reset
#define RS_SET		SetBit(PORTC,0)
#define RS_CLEAR	ClearBit(PORTC,0)
//LCD RW
#define RW_SET		SetBit(PORTC,1)
#define RW_CLEAR	ClearBit(PORTC,1)
//LCD Enable
#define E_SET		SetBit(PORTC,2)
#define E_CLEAR		ClearBit(PORTC,2)

#define BUSY		CheckBit(PINB,7)

#define LED_On 	SetBit(PORTC,3)
#define LED_Off	ClearBit(PORTC,3)

unsigned char display_data1[] = "   HANKYONG   ";
unsigned char display_data2[] = "  UNIVERSITY  ";

volatile int cur_x, cur_y;
volatile unsigned char cur_char;
volatile int updated = 0;

//
void LCD_enable(void) {
	E_SET;
	_delay_ms(1);
	E_CLEAR;
}

void LCD_busy() {
//	DDRB = 0x00;
	ClearBit(DDRB, 7);
	do {
		E_CLEAR;
		_delay_ms(20);
		RS_CLEAR;
		RW_SET;
		E_SET;
		//lcd_enable();
		_delay_ms(20);
	} while (BUSY);
	E_CLEAR;
	SetBit(DDRB, 7);
}

void LCD_command(unsigned char lcd_data) {
	LCD_busy();

	RW_CLEAR;
	RS_CLEAR;

	PORTB = lcd_data;

	LCD_enable();
}

void LCD_clear(void) {
	LCD_command(0x01);
}

void LCD_home(void) {
	LCD_command(0x02);
}

void LCD_1stLine(void) {
	LCD_command(0x80);
}

void LCD_2ndLine(void) {
	LCD_command(0xc0);
}

// Display on
// RS  R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// === === === === === === === === === ===
// 0   0   0   0   0   0   1   D   C   B
// D: Display
// C: Cursor
// B: blink
#define cBlink	0
#define cOn 1
#define cOff 2

void LCD_setCursor(int Mode) {
	switch (Mode) {
	case cBlink:
		LCD_command(0x0F);
		break; //Blink
	case cOn:
		LCD_command(0x0E);
		break; // On
	case cOff:
		LCD_command(0x0C);
		break;
	default:
		LCD_command(0x0E);
	}
}

void LCD_on(void) {
	LCD_command(0x08);
}

void LCD_off(void) {
	LCD_command(0x0C);
}

void LCD_moveCursor(int step) {
	// move right
	if (step >= 0) {
		if (step > 16)
			step = 16;
		for (int mv = 0; mv < step; mv++)
			LCD_command(0x14);
	} else {
		if (step < -16)
			step = -16;
		for (int mv = step; mv < 0; mv++)
			LCD_command(0x10);
	}
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

#define cLine1_5_7	0
#define cLine1_5_10	1
#define cLine2_5_7	2
#define cMaxLine 	2

void lcd_FunctionSet(int DataLen, int fntSize) {
	unsigned char data = 0x20;

	if (DataLen == 8)
		data |= _BV(4);

	switch (fntSize) {
	case cLine1_5_7:
		break;
	case cLine1_5_10:
		data |= 0x04;
		break;
	default:
		data |= 0x08;
	}

	LCD_command(data);
}

void LCD_moveCursorXY(int x, int y) {
	unsigned char data=0;

	switch (y) {
	case 1:
		data = 0x80 + x;
		break;
	case cMaxLine:
		data = 0xc0 + x;
		break;
	}
	LCD_command(data);
}

unsigned char LCD_getChar(int x, int y)
{
	unsigned char data;

	LCD_moveCursorXY(x,y);

	LCD_busy();
	DDRB = 0x00;

	RW_SET;
	RS_SET;
	E_SET;
	_delay_ms(1);
	data = PINB;

	LCD_enable();

	E_CLEAR;
	DDRB = 0xFF;
	
	return data;	
}

// Entry Mode set
// RS  R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// === === === === === === === === === ===
// 0   0   0   0   0   0   0   1  I/D  S
// I/D : (1) increment (0) decrement
// S : (1) shift (0) fixed
#define cRight 	  2
#define cLeft      0
#define cShift	  1
#define cFixed	  0

// Increment cursor
// lcd_EntryMode(cRight,cFixed);

void LCD_entryMode(int Direction, int Mode) {
	unsigned char data = 0x04;

	if (Direction == cRight)
		data |= _BV(1);

	if (Mode == cShift)
		data |= _BV(0);

	LCD_command(data);
}

void LCD_charWrite(unsigned char lcd_data) {
	LCD_busy();
	RW_CLEAR;
	RS_SET;
	PORTB = lcd_data;
	LCD_enable();
	RS_CLEAR;
}

void LCD_display() {
	unsigned char i;

	LED_On;
	LCD_1stLine();
	for (i = 0; i < 16; i++) {
		LCD_charWrite(display_data1[i]);
	}

	LCD_2ndLine();
	for (i = 0; i < 16; i++) {
		LCD_charWrite(display_data2[i]);
	}
	LED_Off;
}

void LCD_print(unsigned char str[]) {
	int i = 0;

	do {
		LCD_charWrite(str[i++]);
	} while (str[i] != '\0');

}

void LCD_printXY(int x, int y, unsigned char str[]) {
	int i = 0;

	LCD_moveCursorXY(x,y);
	do {
		LCD_charWrite(str[i++]);
	} while (str[i] != '\0');

}

void LCD_init(void) {
	E_CLEAR;
	_delay_ms(20);
	lcd_FunctionSet(8, 0);
	_delay_ms(5);
	lcd_FunctionSet(8, 0);
	_delay_ms(1);
	lcd_FunctionSet(8, 0);
	_delay_ms(1);

// Set the display 2 lines and character font
	lcd_FunctionSet(8, cLine2_5_7);
	LCD_entryMode(cRight, cFixed);
	LCD_clear();
	LCD_setCursor(cOff);
}

SIGNAL(SIG_INTERRUPT0)		//외부인터럽트 0실행 프로그램
{
	cli();
	updated = 1;

	cur_y--;

	if (cur_y <= 0)
		cur_y = cMaxLine;
	sei();
}

SIGNAL(SIG_INTERRUPT1)		//외부인터럽트 0실행 프로그램
{
	cli();
	updated = 1;

	cur_y++;
	if (cur_y > cMaxLine)
		cur_y = 1;
	sei();
}

SIGNAL(SIG_INTERRUPT2)		//외부인터럽트 0실행 프로그램
{
	cli();
	updated = 1;

	cur_x--;
	if (cur_x < 0) {
		cur_x = 15;
		if (cur_y == 1)
			cur_y = cMaxLine;
		else
			cur_y--;
	}
	sei();
}

SIGNAL(SIG_INTERRUPT3)		//외부인터럽트 0실행 프로그램
{
	cli();
	updated = 1;

	cur_x++;
	if (cur_x >= 16) {
		cur_x = 0;
		if (cur_y == cMaxLine)
			cur_y = 1;
		else
			cur_y++;
	}
	sei();
}

SIGNAL(SIG_INTERRUPT4)		//외부인터럽트 4실행 프로그램
{
	cli();

	cur_char = LCD_getChar(cur_x, cur_y);
	LCD_charWrite(cur_char);
	LCD_charWrite(cur_char+1);

	sei();
}

SIGNAL(SIG_INTERRUPT5)		//외부인터럽트 0실행 프로그램
{
	cli();

	LCD_moveCursorXY(cur_x, cur_y);

	if (cur_y == 1) {
		display_data1[cur_x] -= 1;
		LCD_charWrite(display_data1[cur_x]);
	} else {
		display_data2[cur_x] -= 1;
		LCD_charWrite(display_data2[cur_x]);

	}
	LCD_moveCursorXY(cur_x, cur_y);
	sei();
}

void interruptEnable(void) {
	// External Interrupt Mask Register
	EIMSK = 0x3F;		//2진수 (16진주:0x41)

	// External Interrupt Control Register
	EICRA = 0xFF;		//2진수 (16진수:0x02)
	EICRB = 0x0F;
	sei();
}

void port_init(void) {
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0x00;
	DDRE = 0x00;

	PORTB = 0x00;
	PORTC = 0x00;
}

int main() {
	port_init();
	interruptEnable();
	LCD_init();

	cur_x = 0;
	cur_y = 1;

	LCD_off();
	LCD_home();
	LCD_print(display_data1);
	LCD_2ndLine();
	LCD_print(display_data2);
	LCD_on();

	LCD_setCursor(cOn);

	while (1) {
		if (updated) {
			LCD_moveCursorXY(cur_x, cur_y);
			//lcd_getChar();
			updated = 0;
		}
		_delay_ms(10);
	};
}

