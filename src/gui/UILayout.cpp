#include "UILayout.hpp"

engine::UILayout::UILayout()
    : elementA("test", {0.f, 0.f})
{
}

void engine::UILayout::DrawLayout(sf::RenderWindow &window)
{
    PRINT("Draw");
    window.draw(elementA);
}