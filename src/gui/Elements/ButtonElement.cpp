#include "ButtonElement.hpp"
#include "utils.hpp"

engine::gui::elements::ButtonElement::ButtonElement(uint16_t id, const std::string &text, const sf::Vector2f &position, std::function<void()> callback, ButtonConfig config)
    : m_callback(callback), m_config(config)
{
    setID(id);

    m_shape.setFillColor(config.fillColor);
    m_shape.setOutlineThickness(config.outlineThickness);
    m_shape.setOutlineColor(config.outlineColor);

    // Setup text renderer
    m_textRenderer.setText(text);
    m_textRenderer.setColor(config.fontColor);
    m_textRenderer.setCharSpacing(config.charSpacing);

    // Get text bounds for button sizing
    sf::FloatRect textBounds = m_textRenderer.getLocalBounds();

    // Position the shape
    m_shape.setPosition({position.x + config.outlineThickness,
                         position.y + config.outlineThickness});

    m_shape.setSize({textBounds.size.x + 2.f * config.padding.x,
                     textBounds.size.y + 2.f * config.padding.y});

    // Center text within button
    sf::Vector2f textPosition = {
        m_shape.getPosition().x + config.padding.x,
        m_shape.getPosition().y + config.padding.y};

    m_textRenderer.setPosition(textPosition);
}

void engine::gui::elements::ButtonElement::SetText(const std::string &newText)
{
    m_textRenderer.setText(newText);

    // Recalculate button size
    sf::FloatRect textBounds = m_textRenderer.getLocalBounds();
    sf::Vector2f currentPos = m_shape.getPosition();

    m_shape.setSize({textBounds.size.x + 2.f * m_config.padding.x,
                     textBounds.size.y + 2.f * m_config.padding.y});

    // Reposition text
    sf::Vector2f textPosition = {
        currentPos.x + m_config.padding.x,
        currentPos.y + m_config.padding.y};

    m_textRenderer.setPosition(textPosition);
}

void engine::gui::elements::ButtonElement::Update(const GameScreenData &data)
{
    // aliases
    const int &mousePosX = data.mousePos.x;
    const int &mousePosY = data.mousePos.y;

    const float &topSidePos = m_shape.getPosition().y;
    const float &bottomSidePos = topSidePos + m_shape.getSize().y;
    const float &leftSizePos = m_shape.getPosition().x;
    const float &rightSidePos = leftSizePos + m_shape.getSize().x;

    if ((mousePosX >= leftSizePos && mousePosX < rightSidePos) &&
        (mousePosY >= topSidePos && mousePosY < bottomSidePos))
    {
        if (data.isClicking)
        {
            // click logic
            if (!m_pressedThisFrame)
            {
                DEBUG_PRINT("CLICK");
                m_callback();
                m_textRenderer.setColor(m_config.fontClickColor);
                m_pressedThisFrame = true;
            }
        }
        else
        {
            // hover logic
            m_textRenderer.setColor(m_config.fontHoverColor);
            m_pressedThisFrame = false;
        }
    }
    else
    {
        m_textRenderer.setColor(m_config.fontColor);
        m_pressedThisFrame = false;
    }
}

void engine::gui::elements::ButtonElement::SetCallback(std::function<void()> callback)
{
    m_callback = callback;
}

void engine::gui::elements::ButtonElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    target.draw(m_shape, states);
    m_textRenderer.draw(target, states);
}