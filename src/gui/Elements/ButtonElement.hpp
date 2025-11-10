#pragma once
#include <functional>

#include "utils.hpp"
#include "UIElement.hpp"
#include "GameScreenData.hpp"

namespace engine::gui::elements
{
    struct ButtonConfig
    {
        sf::Vector2f padding = {16.f, 8.f};

        sf::Color fillColor = sf::Color::Black;
        float outlineThickness = 2.f;
        sf::Color outlineColor = sf::Color::White;

        sf::Color fontColor = sf::Color::White;
        unsigned int fontSize = 20;
        sf::Text::Style fontStyle = sf::Text::Style::Regular;
        sf::Text::Style fontHoverStyle = sf::Text::Style::Underlined;
        sf::Text::Style fontClickStyle = sf::Text::Style::Italic;
    };

    class ButtonElement : public UIElement
    {
    public:
        ButtonElement(const std::string &text, const sf::Vector2f &position, std::function<void()> callback = CONSTANTS::NULLFUNC, ButtonConfig config = {});

        inline void SetText(const std::string &newText);

        void Update(const GameScreenData &data) override;

        void SetCallback(std::function<void()> callback);

    private:
        ButtonConfig m_config;

        sf::Font m_font;
        std::optional<sf::Text> m_text;
        sf::RectangleShape m_shape;

        bool m_pressedThisFrame = false;
        std::function<void()> m_callback;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
