/*
 * timer1.h
 *
 *  Created on: 2019. 11. 15.
 *      Author: Soochan Kim
 */

#ifndef TIMER1_H_
#define TIMER1_H_


#include <avr/io.h>
#include <util/delay.h>

#define Normal 	0
#define PPWM8	1
#define PPWM9	2
#define PPWM10	3
#define CTC		4
#define FPWM8	5
#define FPWM9	6
#define FPWM10	7
#define FPWM_ICR1	14
#define FPWM_OCR1A	15

#define Normal 		0
#define Toggle		1
#define NonInvert	2
#define Invert		3

void Timer1Mode(unsigned char mode);
void Timer1OutputA(unsigned char mode);
void Timer1OutputB(unsigned char mode);
void Timer1Prescaler(unsigned int scale);

#endif /* TIMER1_H_ */
