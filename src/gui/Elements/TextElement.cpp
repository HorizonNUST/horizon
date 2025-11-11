#include "TextElement.hpp"

engine::gui::elements::TextElement::TextElement(uint16_t id, const std::string &text, const sf::Vector2f &position)
    : m_position(position)
{
    setID(id);

    if (!m_font.openFromFile("assets/Inter/Inter.ttf"))
    {
        throw("Inter.ttf not found");
    }

    m_text = sf::Text(m_font);

    m_text->setString(text);
    m_text->setPosition(position);
}

inline void engine::gui::elements::TextElement::SetText(const std::string &newText)
{
    if (m_text)
        m_text->setString(newText);
}

void engine::gui::elements::TextElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    if (m_text)
        target.draw(*m_text, states);
}
