#pragma once
#include <array>
#include <functional>

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "TextElement.hpp"
#include "ImageElement.hpp"
#include "ButtonElement.hpp"
#include "utils.hpp"

namespace engine
{
    class UILayout
    {
    private:
        std::vector<std::unique_ptr<engine::gui::elements::UIElement>> m_elements;

    public:
        UILayout();

        void DrawLayout(sf::RenderWindow &window);
    };
}