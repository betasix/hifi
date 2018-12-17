#include "Arduino.h"
#include "Switch.h"
#include "Wire.h"

Switch::Switch(int SwitchAddress)
{
	_SwitchAddress = SwitchAddress;
	uint8_t sw_inputs;
	Wire.begin();
}