#include <stdint.h>

#include "I2CIO.h"
#include "SSD1308_I2C.h"

#ifndef PANEL_SHIELD_H
#define PANEL_SHIELD_H

class PanelShield : public SSD1308_I2C, public I2CIO {
 public:
  PanelShield(uint8_t i2c_address);
  size_t printCustom(uint8_t value);
  int writeByte(uint8_t value);
 private:
  // static constants
  static const uint8_t EN = 0;
  static const uint8_t RW = 1;
  static const uint8_t RS = 2;
  static const uint8_t D4 = 4;
  static const uint8_t D5 = 5;
  static const uint8_t D6 = 6;
  static const uint8_t D7 = 7;
  static const uint8_t BL = 3;
};

#endif //PANEL_SHIELD_H
