#include "ButtonElement.hpp"

engine::gui::elements::ButtonElement::ButtonElement(const std::string &text, const sf::Vector2f &position, ButtonConfig config)
{
    if (!m_font.openFromFile("assets/Inter/Inter.ttf"))
    {
        throw("Inter.ttf not found");
    }

    m_shape.setFillColor(config.fillColor);
    m_shape.setOutlineThickness(config.outlineThickness);
    m_shape.setOutlineColor(config.outlineColor);

    m_text = sf::Text(m_font);
    m_text->setString(text);
    m_text->setCharacterSize(config.fontSize);
    m_text->setFillColor(config.fontColor);

    sf::FloatRect textBounds = m_text->getLocalBounds();
    m_text->setOrigin(textBounds.position);
    m_text->setPosition({
        position.x + config.padding.x / 2,
        position.y + config.padding.y / 2,
    });

    m_shape.setPosition({
        position.x - config.padding.x / 2,
        position.y - config.padding.y / 2,
    });
    m_shape.setSize({textBounds.size.x + 2 * config.padding.x,
                     textBounds.size.y + 2 * config.padding.y});
}

inline void engine::gui::elements::ButtonElement::setText(const std::string &newText)
{
    if (m_text)
        m_text->setString(newText);
}

void engine::gui::elements::ButtonElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);

    if (m_text)
        target.draw(*m_text, states);
}
