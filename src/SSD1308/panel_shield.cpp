#include "panel_shield.h"

// Definition of private constants
const uint8_t PanelShield::EN;
const uint8_t PanelShield::RW;
const uint8_t PanelShield::RS;
const uint8_t PanelShield::D4;
const uint8_t PanelShield::D5;
const uint8_t PanelShield::D6;
const uint8_t PanelShield::D7;
const uint8_t PanelShield::BL;


// Implementation of public methods
PanelShield::PanelShield(uint8_t i2c_address)
  : SSD1308_I2C(i2c_address, EN, RW, RS, D4, D5, D6, D7, BL, NEGATIVE)
{
  // Definition for the SSD1308 lcd display driven by i2c.
  SSD1308_I2C::begin(20, 4);

  // I/O definitions for the physical user interface of the switch panel.
  I2CIO::begin(i2c_address + 1);
  I2CIO::pinMode(0, INPUT);
  I2CIO::pinMode(1, INPUT);
  I2CIO::pinMode(2, INPUT);
  I2CIO::pinMode(3, INPUT);
  I2CIO::pinMode(4, OUTPUT);
  I2CIO::pinMode(5, OUTPUT);
  I2CIO::pinMode(6, OUTPUT);
  I2CIO::pinMode(7, OUTPUT);
}


size_t PanelShield::printCustom(uint8_t value)
{
  return SSD1308_I2C::write(value);
}


int PanelShield::writeByte(uint8_t value)
{
  return I2CIO::write(value);
}
