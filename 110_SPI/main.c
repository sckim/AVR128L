/*
 * MCP410x digital potentiometer
 * SPI communication
 */
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"

#define SLAVE_SELECT    SPI_SS_PORT &= ~(1 << SPI_SS)
#define SLAVE_DESELECT  SPI_SS_PORT |= (1 << SPI_SS)

void initSPI(void) {
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

void SPI_writeByte(uint8_t byte) {
	SLAVE_SELECT;
	SPI_MasterTransmit(0);
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

int main(void) {
	initSPI();

	while (1) {
		for (int i = 0; i < 255; i++) {
			SPI_writeByte(i);
			_delay_ms(1);
		}
	}
	return 1;
}
