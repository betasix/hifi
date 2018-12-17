/*
 * GenerichPortExpander.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: Simon
 */

#include "PortExpanderPCA9557.hpp"
#include <Wire.h>

PortExpanderPCA9557::PortExpanderPCA9557(uint8_t sda, uint8_t scl):
	m_sda(sda),
	m_scl(scl)
{
	// TODO Auto-generated constructor stub
}

PortExpanderPCA9557::~PortExpanderPCA9557()
{
	// TODO Auto-generated destructor stub
}

bool PortExpanderPCA9557::setup()
{
	// Setup the port expander
	Wire.begin(m_sda, m_scl);
	Wire.beginTransmission(i2cDefaultAddress);
	Wire.write(i2cConfRegister);
	Wire.write(i2cIOMask);
	Wire.endTransmission();
	return true;
}

bool PortExpanderPCA9557::send(uint8_t data)
{
	Wire.beginTransmission(i2cDefaultAddress);
	//Wire.write(i2cOutputPort);
	Wire.write(data);
	Wire.endTransmission();
	return true;
}

bool PortExpanderPCA9557::send(const unsigned char* data, uint8_t messageSizeInBytes)
{
	Wire.beginTransmission(i2cDefaultAddress);
	//Wire.write(i2cOutputPort);
	for (uint8_t dataIndex = 0; dataIndex < messageSizeInBytes; ++dataIndex)
	{
		Wire.write(data[dataIndex]);
	}
	Wire.endTransmission();
	return false;
}
