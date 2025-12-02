// c로 작성된 코드가 C++에서 호출될때 문제가 없도록
extern "C" {
// add your #include statements here
#include "i2c.h"
}

#include <util/delay.h>
#include "PCF8574.h"

//생성자 정의
PCF8574::PCF8574(const uint8_t deviceAddress) {
	_address = deviceAddress;
	_dataIn = 0;
	_dataOut = 0xFF;
	_buttonMask = 0xFF;
	_error = PCF8574_OK;
}

// i2c 초기화 설정
void PCF8574::begin(void) {
	i2cInit();
	_delay_us(10);

}

uint8_t PCF8574::digitalReadAll(void) {
	i2cStart();
	i2cSend(_address + I2C_READ);
	_dataIn = i2cReadNoAck();
	i2cStop();

	return _dataIn;
}

uint8_t PCF8574::digitalRead(const uint8_t pin) {
	if (pin > 7) {
		_error = PCF8574_PIN_ERROR;
		return 0;
	}
	PCF8574::digitalReadAll();
	return (_dataIn & (1 << pin)) > 0;
}

void PCF8574::digitalWriteAll(const uint8_t value) {
	_dataOut = value;
	i2cStart();
	i2cSend(_address + I2C_WRITE);
	i2cSend(_dataOut);
	i2cStop();
	//_error = i2cStop();
}

void PCF8574::digitalWrite(const uint8_t pin, const uint8_t value) {
	if (pin > 7) {
		_error = PCF8574_PIN_ERROR;
		return;
	}
	if (value == 0) {
		_dataOut &= ~(1 << pin);
	} else {
		_dataOut |= (1 << pin);
	}
	digitalWriteAll(_dataOut);
}

void PCF8574::togglePin(const uint8_t pin) {
	if (pin > 7) {
		_error = PCF8574_PIN_ERROR;
		return;
	}
	toggle8(1 << pin);
}

void PCF8574::toggle8(const uint8_t mask) {
	_dataOut ^= mask;
	PCF8574::digitalWriteAll(_dataOut);
}

void PCF8574::shiftRight(const uint8_t n) {
	if (n == 0 || n > 7)
		return;
	_dataOut >>= n;
	PCF8574::digitalWriteAll(_dataOut);
}

void PCF8574::shiftLeft(const uint8_t n) {
	if (n == 0 || n > 7)
		return;
	_dataOut <<= n;
	PCF8574::digitalWriteAll(_dataOut);
}

int PCF8574::lastError() {
	int e = _error;
	_error = PCF8574_OK;
	return e;
}

void PCF8574::rotateRight(const uint8_t n) {
	uint8_t r = n & 7;
	_dataOut = (_dataOut >> r) | (_dataOut << (8 - r));
	PCF8574::digitalWriteAll(_dataOut);
}

void PCF8574::rotateLeft(const uint8_t n) {
	rotateRight(8 - (n & 7));
}

////added 0.1.07/08 Septillion
//uint8_t PCF8574::readButton8(const uint8_t mask) {
//	uint8_t temp = _dataOut;
//	PCF8574::digitalWriteAll(mask | _dataOut);
//	PCF8574::digitalReadAll();
//	PCF8574::digitalWriteAll(temp);
//	return _dataIn;
//}
//
////added 0.1.07 Septillion
//uint8_t PCF8574::readButton(const uint8_t pin) {
//	if (pin > 7) {
//		_error = PCF8574_PIN_ERROR;
//		return 0;
//	}
//	uint8_t temp = _dataOut;
//	PCF8574::digitalWrite(pin, 1);
//	uint8_t rtn = PCF8574::digitalRead(pin);
//	PCF8574::digitalWriteAll(temp);
//	return rtn;
//}
//
////added 0.1.08 Septillion
//void PCF8574::setButtonMask(uint8_t mask) {
//	_buttonMask = mask;
//}
