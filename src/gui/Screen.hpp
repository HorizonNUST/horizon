#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"

class Screen
{
private:
    std::vector<UIElement> m_ui_elements;
    sf::RenderWindow m_window;

public:
    Screen();
    ~Screen();

    void StartLoop();
};
