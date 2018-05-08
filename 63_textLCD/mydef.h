/*
 * mydef.h
 *
 *  Created on: 2017. 6. 7.
 *      Author: Soochan Kim
 */

#ifndef MYDEF_H_
#define MYDEF_H_

// Type define
#define BYTE	unsigned char
#define WORD	unsigned int
#define	LONG	unsigned long
#define L_LONG	unsigned long long

//Bit Masks
#define BIT0    0x01 //bit positions for setting/clearing bits
#define BIT1    0x02
#define BIT2    0x04
#define BIT3    0x08
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40
#define BIT7    0x80

#define SetBit(x,y)      	( x |= (y) )  	// y번째 비트 1
#define ClearBit(x,y)      	( x &= (~y) ) 	// y번째 비트 0
#define CheckBit(x,y) 		( x & (y) )   //True if bit y of byte x=1.

#endif /* MYDEF_H_ */
