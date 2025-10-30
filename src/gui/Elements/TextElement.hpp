#pragma once
#include "UIElement.hpp"

namespace engine::gui::elements
{
    class TextElement : public UIElement
    {
    public:
        TextElement(const std::string &text, const sf::Vector2f &position);

        inline void setText(const std::string &newText);

    private:
        sf::Font m_font;
        std::optional<sf::Text> m_text;
        sf::Vector2f m_position;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
