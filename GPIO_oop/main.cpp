/*
 * main.cpp
 *
 *  Created on: 2019. 7. 22.
 *      Author: Soochan Kim
 */
#define F_CPU 16000000UL

#include <util/delay.h>

extern "C" {
#include "pins.h"
#include "gpio.h"
}

int main(void) {
	pinMode(13, OUTPUT);

	while (1) {
		digitalWrite(13, HIGH);
		_delay_ms(1000);
		digitalWrite(13, LOW);
		_delay_ms(1000);
	}
	return 1;
}
