#ifndef Switch_h
#define Switch_h
#include "Arduino.h"
#include "wire.h"

class Switch
{
	public:
		Switch (int SwitchAddress);
	private:
		int _SwitchAddress;
};
#endif