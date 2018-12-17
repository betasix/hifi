/*
 * GenerichPortExpander.h
 *
 *  Created on: Mar 21, 2017
 *      Author: Simon
 */

#ifndef LIBRARIES_SSD1308_PORTEXPANDER_PORTEXPANDERPCA9557_H_
#define LIBRARIES_SSD1308_PORTEXPANDER_PORTEXPANDERPCA9557_H_

#include "IPortExpander.h"
#include <stdint.h>

class PortExpanderPCA9557 : public IPortExpander
{
public:
	PortExpanderPCA9557(uint8_t sda = 5, uint8_t scl = 4);
	virtual ~PortExpanderPCA9557();
	bool setup() override;
	bool send(const unsigned char* data, uint8_t messageSizeInBytes) override;
	bool send(uint8_t data);

private:
	static constexpr uint8_t i2cDefaultAddress = 0x38;
	static constexpr uint8_t i2cIOMask = 0x00;
	static constexpr uint8_t i2cConfRegister = 0x03;
	static constexpr uint8_t i2cOutputPort = 0x01;
	static constexpr uint8_t i2cInputPort = 0x02; // TODO: find the right port
	uint8_t m_sda;
	uint8_t m_scl;
};

#endif /* LIBRARIES_SSD1308_PORTEXPANDER_PORTEXPANDERPCA9557_H_ */
