#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char BYTE;
#define KEYPAD D  //KEYPAD IS ATTACHED ON PORTA

//*******************************
#define KEYPAD_PORT 	PORT(KEYPAD)
#define KEYPAD_DDR   	DDR(KEYPAD)
#define KEYPAD_PIN   	PIN(KEYPAD)
//*******************************


#define RowColDirection DDRD //Data Direction Configuration for keypad 
#define COL PORTD //Lower four bits of PORTC are used as ROWs
#define ROW PIND //Higher four bits of PORTC are used as COLs - See more at: http://exploreembedded.com/wiki/AVR_C_Library#Keypad

void delay(unsigned long i)
{
   while(--i);
}


void KEYPAD_WaitForKeyRelease() 	
{ 
	unsigned char key; 
	
	do { 
		PORTD = 0x0f; // Pull the ROW lines to low and Column high low. 
		key=COL & 0x0f; // Read the Columns, to check the key press 	
	}while(key!=0x0f); // Wait till the Key is released, // If no Key is pressed, Column lines will remain high (0x0f) 
} 

void KEYPAD_WaitForKeyPress()
{
	unsigned char key;
	
	do { 
		do { 
			ROW=0x0f;	// Pull the ROW lines to low and Column lines high. 
			key=COL & 0x0F; // Read the Columns, to check the key press 
		} while(key==0x0f); // Wait till the Key is pressed, // if a Key is pressed the corresponding Column line go low   
		
		_delay_ms(10);	// Wait for some time(debounce Time);   
		ROW=0x0f;	// After debounce time, perform the above operation 
		key=COL & 0x0F;	// to ensure the Key press.   
	}while(key==0x0f);
} 

unsigned char KEYPAD_ScanKey()
{
	unsigned char ScanKey = 0xe0,i, key;

 	for(i=0;i<0x04;i++) // Scan All the 4-Rows for key press
 	{ 
	 ROW=ScanKey + 0x0F;// Select 1-Row at a time for Scanning the Key 
	 key=COL &0x0F;  // Read the Column, for key press ? 
	 if(key!= 0x0F) // If the KEY press is detected for the selected 
		break; // ROW then stop Scanning, ? 
	 
	 ScanKey=(ScanKey<<1)+ 0x10; // Rotate the ScanKey to SCAN the remaining Rows
 	} 
 	key = key + (ScanKey &0xf0); // Return the row and COL status to decode the key 
 
  	return(key);
 }

unsigned char KEYPAD_GetKey()
{ 
	unsigned char key;
	
	KEYPAD_WaitForKeyRelease(); // Wait for the previous key release 
	_delay_ms(100);
	//KEYPAD_WaitForKeyPress(); // Wait for the new key press 
	key = KEYPAD_ScanKey(); // Scan for the key pressed. 
	
	switch(key) // Decode the key 
	{ 
		case 0xe7: key='0'; break;
		case 0xeb: key='1'; break;
		case 0xed: key='2'; break;
		case 0xee: key='3'; break; 
		case 0xd7: key='4'; break; 
		case 0xdb: key='5'; break; 
		case 0xdd: key='6'; break; 
		case 0xde: key='7'; break; 
		case 0xb7: key='8'; break; 
		case 0xbb: key='9'; break; 
		case 0xbd: key='A'; break; 
		case 0xbe: key='B'; break; 
		case 0x77: key='C'; break; 
		case 0x7b: key='D'; break; 
		case 0x7d: key='E'; break; 
		case 0x7e: key='F'; break; 
		default: key='z'; 
		
	} 
	return(key); // Return the key 
}

int main(void)
{
	BYTE	Index=0;

	BYTE	LED[8] = {0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00};
	BYTE	SEG[10]= {0XC0, 0XF9,0XA4,0XB0,0X99,0X92,0X82, 0XD8,0X80,0X90};


	DDRA = 0xff;
	PORTA = 0xff;

	// high 4bits: output
	// low 4bits: input
	DDRD = 0xf0;
	
	// 7Seg
	DDRF = 0xFF;
	

	while(1)
	{
		//KEYPAD_WaitForKeyRelease(); // Wait for the previous key release 
		//_delay_ms(100);
		//KEYPAD_WaitForKeyPress(); // Wait for the new key press 
		Index = KEYPAD_GetKey();
		PORTA = LED[Index];
		PORTF = ~SEG[Index+1];
		_delay_ms(100);
	}
}
