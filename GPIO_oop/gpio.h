/*
 * gpio.h
 *
 *  Created on: 2019. 7. 2.
 *      Author: Soochan Kim
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdio.h>

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
void checkGPIO(void);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);


#endif /* GPIO_H_ */
