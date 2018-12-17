#ifndef _IUIELEMENT_H_
#define _IUIELEMENT_H_

#include <string>

class IUIElement 
{
public:
    virtual std::string render() = 0;
    virtual ~IUIElement(){};
    virtual void callback(){};
    virtual void increaseValue(){};
    virtual void decreaseValue(){};
};

#endif