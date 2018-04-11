#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char BYTE;

int key_scan(void) {
	BYTE KEY;
	BYTE temp_LED;

	//read Port D
	KEY = PIND;
	//get only low 4 bits
	KEY &= 0x0f;

	temp_LED = 0;

	if (KEY != 0x0f)  //if a key is pressed
			{
		//     KEY = PIND;
		//     KEY &= 0x0f;
		//	  if(KEY != 0x0f)
		//	  {
		switch (KEY) {
		case 0x07:
			temp_LED = 1;
			break;
		case 0x0B:
			temp_LED = 2;
			break;
		case 0x0D:
			temp_LED = 3;
			break;
		default:
			temp_LED = 4;
		}
		//	  }
	}

	return temp_LED;
}

int main(void) {
	BYTE bKey;
	BYTE SEG[12] = { 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90,
			0X88, 0X8e };

	DDRA = 0xff;
	PORTA = 0xff;

	DDRF = 0xff;  // 7 segments
	PORTF = 0xff;

	// high 4bits: output
	// low 4bits: input
	DDRD = 0xf0;

	while (1) {
		PORTD = 0xb0; // only bit 6 low, 0b1011
		_delay_ms(20);
		bKey = key_scan();
		if (bKey == 1)
			PORTF = SEG[1];
		else if (bKey == 2)
			PORTF = SEG[4];
		else if (bKey == 3)
			PORTF = SEG[7];
		else if (bKey == 4)
			PORTF = SEG[10];  //A

		PORTD = 0xd0; // only bit 5 low, 0b1101
		_delay_ms(20);
		bKey = key_scan();
		if (bKey == 1)
			PORTF = SEG[2];
		else if (bKey == 2)
			PORTF = SEG[5];
		else if (bKey == 3)
			PORTF = SEG[8];
		else if (bKey == 4)
			PORTF = SEG[0];

		PORTD = 0xe0;  // only bit 4 low, 0b1110
		_delay_ms(20);
		bKey = key_scan();
		if (bKey == 1)
			PORTF = SEG[3];
		else if (bKey == 2)
			PORTF = SEG[6];
		else if (bKey == 3)
			PORTF = SEG[9];
		else if (bKey == 4)
			PORTF = SEG[11];
	}
}
