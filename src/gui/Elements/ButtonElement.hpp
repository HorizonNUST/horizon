#pragma once
#include "UIElement.hpp"

namespace engine::gui::elements
{
    struct ButtonConfig
    {
        sf::Color fillColor = sf::Color::Black;
        float outlineThickness = 2.f;
        sf::Color outlineColor = sf::Color::White;
        sf::Color fontColor = sf::Color::White;
        unsigned int fontSize = 20;
        sf::Vector2f padding = {16.f, 8.f};
    };

    class ButtonElement : public UIElement
    {
    public:
        ButtonElement(const std::string &text, const sf::Vector2f &position, ButtonConfig config = {});

        inline void setText(const std::string &newText);

    private:
        sf::Font m_font;
        std::optional<sf::Text> m_text;
        sf::RectangleShape m_shape;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
