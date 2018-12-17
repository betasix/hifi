#include "Page.h"
#include <string>

Page::Page(std::string title) : m_uiElementSelected(0), m_title(title)
{
}

Page::~Page()
{
    for (const auto *element : m_uiElements)
    {
        delete element;
    }
}

void Page::nextUIElement()
{
    if (m_uiElements.size() > 0)
    {
        if (m_selectedUIElementIndex != m_uiElements.size() - 1)
        {
            ++m_selectedUIElementIndex;
        }
        else
        {
            m_selectedUIElementIndex = 0;
        }
    }
}

void Page::previousUIElement()
{
    if (m_uiElements.size() > 0)
    {
        if (m_selectedUIElementIndex != 0)
        {
            --m_selectedUIElementIndex;
        }
        else
        {
            m_selectedUIElementIndex = m_uiElements.size() - 1;
        }
    }
}

void Page::addUIElement(IUIElement *uiElement)
{
    m_uiElements.push_back(uiElement);
}


void Page::on_encoder_pushed()
{
    if (m_uiElementSelected == true)
    {
        m_uiElementSelected = false;
    }    
    else
    {
        m_uiElementSelected = true;
    }
}

void Page::on_encoder_long_press()
{
    
}

void Page::on_encoder_next()
{
    if (m_uiElementSelected == false)
    {
        nextUIElement();
    }
    else 
    {
         if (m_uiElements.empty() == false)
         {
            m_uiElements[m_selectedUIElementIndex]->increaseValue();
            m_uiElements[m_selectedUIElementIndex]->callback();
         }
    }
}
    

void Page::on_encoder_previous()
{
     if (m_uiElementSelected == false)
    {
        previousUIElement();
    }
    else 
    {
         if (m_uiElements.empty() == false)
         {
            m_uiElements[m_selectedUIElementIndex]->decreaseValue();
            m_uiElements[m_selectedUIElementIndex]->callback();
         }
    }
}

std::string Page::render()
{
    return m_title + ": " + m_uiElements[m_selectedUIElementIndex]->render();
}