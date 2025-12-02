/*
 * mani.cpp
 *
 *  Created on: 2019. 6. 28.
 *      Author: Soochan Kim
 */

#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

//int main(void) {
//
//	// initialize the LCD
//	lcd.begin();
//
//	// Turn on the blacklight and print a message.
//	lcd.backlight();
//
//	lcd.printstr("HKNU");
//
//	return 0;
//}

int main(void)
{
	lcd.begin();

	bool blinking = true;
	lcd.cursor();

	while (1) {
		if (blinking) {
			lcd.clear();
			lcd.printstr("No cursor blink");
			lcd.noBlink();
			blinking = false;
		} else {
			lcd.clear();
			lcd.printstr("Cursor blink");
			lcd.blink();
			blinking = true;
		}
		_delay_ms(1000);
	}
}
