#include "TextElement.hpp"

using namespace engine::gui::elements;

TextElement::TextElement(uint16_t id, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size)
{
    setID(id);

    m_textRenderer.setPosition(position);
    m_textRenderer.setText(text);
}

void TextElement::SetText(const std::string &newText)
{
    m_textRenderer.setText(newText);
}

void TextElement::SetColor(const sf::Color &color)
{
    m_textRenderer.setColor(color);
}

void TextElement::SetCharSpacing(float spacing)
{
    m_textRenderer.setCharSpacing(spacing);
}

sf::FloatRect TextElement::GetBounds() const
{
    return m_textRenderer.getGlobalBounds();
}

void TextElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    m_textRenderer.draw(target, states);
}