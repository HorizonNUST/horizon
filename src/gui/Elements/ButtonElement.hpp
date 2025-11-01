#pragma once
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
        ButtonElement(const std::string &text, const sf::Vector2f &position, ButtonConfig config = {});

        inline void setText(const std::string &newText);

        void update(const GameScreenData &data) override;

    private:
        ButtonConfig m_config;

        sf::Font m_font;
        std::optional<sf::Text> m_text;
        sf::RectangleShape m_shape;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
