#include "i2c.h"
#include <util/delay.h>
#include <avr/sfr_defs.h>

void i2cInit(void) {
	TWBR = 32; /* set bit rate, see p. 242 */
	/* 8MHz / (16+2*TWBR*1) ~= 100kHz */
	TWCR |= (1 << TWEN); /* enable */

	//Use internal Pull up
	PORTC |= _BV(PC5);
	PORTC |= _BV(PC4);
}

/***************************************************************************************************
 void I2C_Start()
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate I2C Start Condition.
 Start Condition: SDA goes low when SCL is High.

 ____________
 SCL:          |            |
 ________|            |______
 _________
 SDA:      |         |
 ____|         |____________

 ***************************************************************************************************/
void i2cWaitForComplete(void) {
	loop_until_bit_is_set(TWCR, TWINT);
}

void i2cStart(void) {
	TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTA));
	i2cWaitForComplete();
}

/***************************************************************************************************
 void I2C_Stop()
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate I2C Stop Condition.
 Stop Condition: SDA goes High when SCL is High.

 ____________
 SCL:          |            |
               ________|            |______
        _________________
 SDA:                    |
                          __________|

 ***************************************************************************************************/
void i2cStop(void) {
//	TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTO));
//	_delay_us(100) ; //wait for a short time

	// send stop condition
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

	// wait for stop condition to be exectued on bus
	// TWINT is not set after a stop condition!
	while (TWCR & _BV(TWSTO)) {
		continue;
	}
}

//i2cRead
uint8_t i2cReadAck(void) {
	TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWEA));
	i2cWaitForComplete();
	return (TWDR);
}

uint8_t i2cReadNoAck(void) {
	TWCR = (_BV(TWINT) | _BV(TWEN));
	i2cWaitForComplete();
	return (TWDR);
}

void i2cSend(uint8_t data) {
	TWDR = data;
	TWCR = (_BV(TWINT) | _BV(TWEN)); /* init and enable */
	i2cWaitForComplete();
}
