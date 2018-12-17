#ifndef _UI_VALUE_
#define _UI_VALUE_
#include <string>

template <class T>
class UI_valuePair
{
    public:
        UI_valuePair(T returnType, std::string displayString);
        T getValue();
        std::string& getDisplayString();

    private:
        T m_returnType;
        std::string m_displayString;
};

template <class T>
UI_valuePair<T>::UI_valuePair(T returnType, std::string displayString):
    m_returnType(returnType),
    m_displayString(displayString)
{

}

template<class T>
T UI_valuePair<T>::getValue()
{
    return m_returnType;
}

template<class T>
std::string& UI_valuePair<T>::getDisplayString()
{
    return m_displayString;
}
#endif
