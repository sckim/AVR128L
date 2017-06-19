/*
#include <avr/io.h>
#include <util/delay.h>

#define SetBit(x,y)		(x |= (1<<y))
#define ClearBit(x,y)	(x &= ~(1<<y))

#define CheckBit(x,y)	(x & (1<<y))

#define RS_SET		SetBit(PORTC,0)
#define RS_CLEAR	ClearBit(PORTC,0)
#define RW_SET		SetBit(PORTC,1)
#define RW_CLEAR	ClearBit(PORTC,1)
#define E_SET		SetBit(PORTC,2)
#define E_CLEAR		ClearBit(PORTC,2)

#define LED_TurnOn 	SetBit(PORTC,3)
#define LED_TurnOff	ClearBit(PORTC,3)

#define BUSY		CheckBit(PINB,7)

unsigned char display_data1[ ]="    HANKYONG   ";
unsigned char display_data2[ ]="   UNIVERSITY  ";

//
void lcd_enable(void)
{
	E_SET;
	_delay_ms(10);
	E_CLEAR;
}

void lcd_busy(void)
{
//	DDRB |= (1<<7);
//	SetBit(PINB,7);
	E_CLEAR;
	
	RS_CLEAR;
	RW_SET;

	DDRB &= ~(1<<7);
	do {
		lcd_enable();
	} while(BUSY);

	DDRB |= (1<<7);
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

void lcd_command(unsigned char lcd_data)
{
	RW_CLEAR;
	RS_CLEAR;

	PORTB = lcd_data;

	lcd_enable();
}

// Display on	
// RS  R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// === === === === === === === === === ===
// 0   0   0   0   0   0   1   D   C   B
// D: Display
// C: Cursor
// B: blink

void lcd_OnOff(unsigned char on)
{
	if( on ) {
		lcd_command(0x0C);
	}
	else {
		lcd_command(0x08);
	}
}

void lcd_Clear(void)
{
	lcd_command(0x01);
}

void lcd_CursorHome(void)
{
	lcd_command(0x02);
}

void lcd_CursorMove2ndLine(void)
{
	lcd_command(0xc0);
}

void lcd_write_char(unsigned char lcd_data)
{
	//lcd_busy();
	//_delay_ms(10);
	RW_CLEAR;
	RS_SET;
	PORTB = lcd_data;
	lcd_enable();
	RS_CLEAR;
	RW_SET;
}

void lcd_display(void)
{
	unsigned char i;
	
	LED_TurnOn;
	lcd_CursorHome();	
	for(i=0; i<16; i++) {
		lcd_write_char(display_data1[i]);
		_delay_ms(500);
	}

	lcd_CursorMove2ndLine();	
	for(i=0; i<16; i++) {
		lcd_write_char(display_data2[i]);
		_delay_ms(500);
	}
	LED_TurnOn;
}

// 0: Display On
// 1: Cursor on
// 2: Cursor blink
void lcd_CursorOnOff(unsigned char on)
{
	switch( on ) {
		case 1: lcd_command(0x0E); break;
		case 2: lcd_command(0x0D); break;
		default: lcd_OnOff(1);
	}
}


void lcd_init(void)
{
	E_CLEAR;
	_delay_ms(20);
	//lcd_func_set();
	lcd_command(0x38);
	_delay_ms(5);
	//lcd_func_set();
	lcd_command(0x38);
	_delay_ms(1);
	//lcd_func_set();
	lcd_command(0x38);
	_delay_ms(1);

	// Set the display aline and character font
	lcd_command(0x38);
	// Display clear
	lcd_command(0x01); //lcd_Clear();
	lcd_CursorOnOff(1);
	
	// Entry Mode set
	// RS  R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// === === === === === === === === === ===
	// 0   0   0   0   0   0   0   1  I/D  S 
	// I/D : (1) increment (0) decrement
	// S : (1) shift (0) fixed
	lcd_command(0x06);
}

int main(void)
{
	DDRB = 0xff;
	DDRC = 0x0f;
	PORTC = 0x00;

	lcd_init();

	while(1) {
		lcd_display();
		_delay_ms(100);
		lcd_Clear();
	};
}
*/

#include <avr/io.h>
#include <util/delay.h>
#define sbit(x,y)      (x|=(1<<y))  // y번째 비트 1
#define cbit(x,y)      (x&=~(1<<y)) // y번째 비트 0
#define tbit(x,y)      (x&(1<<y))   // y 번째 1인지 검사
#define RS_SET         sbit(PORTC,0) //C포트 0번째 1    0001
#define RS_CLEAR       cbit(PORTC,0) // C 포트 0번째 0
#define RW_SET         sbit(PORTC,1) // C포트 1번째 1   0010
#define RW_CLEAR       cbit(PORTC,1)
#define E_SET          sbit(PORTC,2) // C 포트 2번째 1  0100
#define E_CLEAR        cbit(PORTC,2)
#define LIGHT_SET      sbit(PORTC,3) //  C 포트 3번째 1 1000
#define LIGHT_CLEAR    cbit(PORTC,3)
#define BUSY     tbit(PINB,7)   // B포트  7 번째 1인지 검사

unsigned char display_data1[] = "   HANKYONG   ";
unsigned char display_data2[] = "  UNIVERSITY  ";

void lcd_busy()
{
	DDRB=0x00;
	do{
		E_CLEAR;
		_delay_ms(20);
		RS_CLEAR;
		RW_SET;
		E_SET;
		_delay_ms(20);
	}while(BUSY);
	E_CLEAR;
	DDRB=0xFF; 
}
void lcd_enable()
{
	E_SET;
	_delay_ms(20);
	E_CLEAR;
}
void lcd_func_set()
{
	RW_CLEAR;
	RS_CLEAR;
	PORTB=0x38;
	lcd_enable();
}
void lcd_command(unsigned char lcd_data)
{
	lcd_busy();
	RW_CLEAR;
	RS_CLEAR;
	PORTB=lcd_data;
	lcd_enable();
}

void lcd_clear(void)
{
	lcd_command(0x01);
}

void lcd_init()// lcd 초기화 
{
	E_CLEAR;
	_delay_ms(20);
	lcd_func_set();
	_delay_ms(20);
	lcd_func_set();
	_delay_ms(20);
	lcd_func_set();
	_delay_ms(20);
	lcd_command(0x38);
	lcd_command(0x0c);
	lcd_command(0x01);
	lcd_command(0x06);
}
void lcd_write_char(unsigned char lcd_data)
{
	lcd_busy();
	RW_CLEAR;
	RS_SET;
	PORTB=lcd_data;
	lcd_enable();
	RS_CLEAR;
}
void lcd_display()
{
	unsigned char i;
	LIGHT_SET;
//	lcd_command(0x0C);
	lcd_command(0x02);
	for(i=0;i<16;i++)
	{
		lcd_write_char(display_data1[i]);
	}
	lcd_command(0xc0);
	for(i=0;i<16;i++)
	{
		lcd_write_char(display_data2[i]);
	}
}

#define Blink	0
#define CursorOn 1
#define CursorOff 2

void lcd_CursorMode(int Mode)
{
	switch(Mode){
		case Blink: lcd_command(0x0F); break; //Blink
		case CursorOn: lcd_command(0x0E); break; // On
		case CursorOff: lcd_command(0x0C); break;
		default:lcd_command(0x0E);
	}
}

void lcd_DisplayOff(void)
{
		lcd_command(0x08);
}

void lcd_DisplayOn(void)
{
		lcd_command(0x0C);
}

int main()
{
	DDRB = 0xff;
	DDRC = 0xff;
	PORTC = 0x00;
	lcd_init();
	lcd_CursorMode(Blink);
	while(1)
	{
		lcd_display();
		lcd_DisplayOff();
		 _delay_ms(100);
		lcd_DisplayOn();
		 _delay_ms(100);
		lcd_DisplayOff();
		 _delay_ms(100);
		lcd_DisplayOn();

	};

}
















