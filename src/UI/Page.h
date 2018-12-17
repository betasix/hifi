#include <vector>
#include "IUIElement.h"
#include "IEncoderControlled.h"
#include <functional>
#include <string>

class Page : public IUIElement, public IEncoderControlled
{
private:
    std::vector< IUIElement* > m_uiElements;
    std::string m_title; // Page title displayed first in render
    size_t m_selectedUIElementIndex;
    bool m_uiElementSelected;

public:
    virtual void on_encoder_pushed();
    virtual void on_encoder_long_press();
    virtual void on_encoder_next();
    virtual void on_encoder_previous();
    virtual std::string render();
    
    Page(std::string title);
    ~Page();

    void nextUIElement();
    void previousUIElement();
    void selectUIElement();
    void addUIElement(IUIElement* uiElement);
};