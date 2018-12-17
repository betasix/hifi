#include <stdint.h>

class IPortExpander
{
public:
	IPortExpander() {};
	virtual ~IPortExpander(){};
	virtual bool setup() = 0;
	virtual bool send(const unsigned char* data, uint8_t messageSizeInBytes) = 0;
};
