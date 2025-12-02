/*
 * MCP410x digital potentiometer
 * SPI communication
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "pinDefines.h"

//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

//#define SPI_SS        PB2
#define SLAVE_SELECT    SPI_SS_PORT &= ~(1 << SPI_SS)
#define SLAVE_DESELECT  SPI_SS_PORT |= (1 << SPI_SS)

void SPI_init(void) {
	SPI_SS_DDR |= (1 << SPI_SS); /* set SS output */
	SPI_SS_PORT |= (1 << SPI_SS); /* start off not selected (high) */

	SPI_MOSI_DDR |= (1 << SPI_MOSI); /* output on MOSI */
	SPI_MISO_PORT |= (1 << SPI_MISO); /* pullup on MISO */
	SPI_SCK_DDR |= (1 << SPI_SCK); /* output on SCK */

	SPCR |= (1 << SPR1); /* div 16, safer for breadboards */
	SPCR |= (1 << MSTR); /* clockmaster */
	SPCR |= (1 << SPE); /* enable */
}

void SPI_MasterTransmit(char cData) {
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while (!(SPSR & (1 << SPIF)))
		;
}

void SPI_write(int addr, uint8_t byte) {
	SLAVE_SELECT;
	SPI_MasterTransmit(addr);
	SPI_MasterTransmit(byte);
	SLAVE_DESELECT;
}

char SPI_SlaveReceive(void) {
	/* Wait for reception complete */
	while (!(SPSR & (1 << SPIF)))
		;
	/* Return Data Register */
	return SPDR;
}

void MAX7219_clearDisplay(void)
{
	for(int i=1; i<=8; i++)
		SPI_write(i, 0);
}

void MAX7219_shutdown(uint8_t flag)
{
	if(flag)
		SPI_write(OP_SHUTDOWN, 0);
	else
		SPI_write(OP_SHUTDOWN, 1);
}

void MAX7219_init(void)
{
	SPI_init();

	SPI_write(OP_DISPLAYTEST, 0);
	SPI_write(OP_SCANLIMIT, 7);
	SPI_write(OP_DECODEMODE,0);
	MAX7219_clearDisplay();
	MAX7219_shutdown(1);
}

void MAX7219_intensity(uint8_t intensity)
{
    if(intensity>=0 && intensity<16)
        SPI_write(OP_INTENSITY, 8);
}

void MAX7219_setRow(int row, uint8_t value) {
	if(row>=0 && row<8)
		SPI_write(row+1, value);
}

int main(void) {
	uint8_t	pattern;

	MAX7219_init();

	MAX7219_shutdown(0);
	MAX7219_intensity(8);
	MAX7219_clearDisplay();

	while (1) {
		pattern = 0x01;
		for(int i=0; i<8; i++){
			MAX7219_setRow(i, pattern);
			pattern = (pattern<<1) | 1;
			_delay_ms(100);
		}
		MAX7219_clearDisplay();
	}
	return 1;
}
