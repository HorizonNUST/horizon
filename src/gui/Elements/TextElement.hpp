#pragma once
#include "UIElement.hpp"
#include "BitmapTextRenderer.hpp"
#include "utils.hpp"

namespace engine::gui::elements
{
    class TextElement : public UIElement
    {
    public:
        TextElement(uint16_t id, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size = CONSTANTS::ZERO_VECTOR2F);

        /// @brief Set the text of the Element
        /// @param newText The New Text
        void SetText(const std::string &newText);

        /// @brief Set the color of the text
        /// @param color Text color
        void SetColor(const sf::Color &color);

        /// @brief Set character spacing
        /// @param spacing Spacing between characters
        void SetCharSpacing(float spacing);

        /// @brief Get the bounds of the text
        /// @return FloatRect containing the text bounds
        sf::FloatRect GetBounds() const;

    private:
        BitmapTextRenderer m_textRenderer;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}