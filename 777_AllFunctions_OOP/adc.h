/*
 * adc.h
 *
 *  Created on: 2019. 7. 5.
 *      Author: Soochan Kim
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adc_init(void);
uint16_t adc_read(uint8_t ch);

#endif /* ADC_H_ */
