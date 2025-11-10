#pragma once
#include <array>
#include <functional>

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "TextElement.hpp"
#include "ImageElement.hpp"
#include "ButtonElement.hpp"
#include "utils.hpp"

#include "Screen.hpp"
#include "GameScreenData.hpp"

namespace engine
{
    class GameScreen;

    /// @brief To generate a Layout containing `UIElements`
    class UILayout
    {
    private:
        std::vector<std::unique_ptr<engine::gui::elements::UIElement>> m_elements;

    public:
        UILayout();

        void AddTextElement(const std::string &text, const sf::Vector2f &position);
        void AddImageElement(const std::string &imagePath, const sf::Vector2f &position);
        void AddButtonElement(const std::string &text, const sf::Vector2f &position, std::function<void()> callback = CONSTANTS::NULLFUNC, engine::gui::elements::ButtonConfig config = {});

    private:
        friend class GameScreen;

        void update(const GameScreenData &data);
        void drawLayout(sf::RenderWindow &window);
    };
}
