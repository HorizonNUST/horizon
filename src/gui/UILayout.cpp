#include "UILayout.hpp"

void engine::UILayout::DrawLayout(sf::RenderWindow &window)
{
    PRINT("Draw");
    window.draw(elementA);
}