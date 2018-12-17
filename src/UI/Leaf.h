#ifndef _LEAF_H_
#define _LEAF_H_
#include "IUIElement.h"
#include "IEncoderControlled.h"
#include <functional>
#include <vector>
#include <UI/UI_valuePair.h>
#include <string>

template <class T>
class Leaf : public IUIElement
{
private:
  T m_value;
  std::function<void(T)> m_callback;
  std::vector< UI_valuePair<T>* > m_valueList;
  std::string m_title;
  size_t m_selectedValue = 0;

public:
  Leaf(std::string title, std::function<void(T)> callback, std::vector< UI_valuePair<T>* > valueList);
  virtual ~Leaf();

  // Override IUIElement interface
  virtual std::string render();
  virtual void callback();

  // Navigation
  virtual void increaseValue();
  virtual void decreaseValue();
};

template <class T>
Leaf<T>::Leaf(std::string title, std::function<void(T)> callback, std::vector< UI_valuePair<T>* > valueList) :
                                                                    m_callback(callback),
                                                                    m_title(title),
                                                                    m_valueList(valueList)
{
}

template <class T>
Leaf<T>::~Leaf()
{
}

template <class T>
void Leaf<T>::callback()
{
  m_callback(m_value);
}

template <class T>
std::string Leaf<T>::render()
{
  return m_title + m_valueList[m_selectedValue]->getDisplayString();
}

template <class T>
void Leaf<T>::increaseValue()
{
  if (m_selectedValue < m_valueList.size() - 1)
  {
    ++m_selectedValue;
    m_value = m_valueList[m_selectedValue]->getValue();
  }
}

template <class T>
void Leaf<T>::decreaseValue()
{
  if (m_selectedValue > 0)
  {
    --m_selectedValue;
    m_value = m_valueList[m_selectedValue]->getValue();
  }
}

#endif