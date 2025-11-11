#include "UILayout.hpp"

engine::UILayout::UILayout()
{
}

uint16_t engine::UILayout::AddTextElement(const std::string &text, const sf::Vector2f &position)
{
    lastID++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::TextElement>(lastID, text, position));
    return lastID;
}

uint16_t engine::UILayout::AddImageElement(const std::string &imagePath, const sf::Vector2f &position)
{
    lastID++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ImageElement>(lastID, imagePath, position));
    return lastID;
}

uint16_t engine::UILayout::AddButtonElement(const std::string &text, const sf::Vector2f &position, std::function<void()> callback, engine::gui::elements::ButtonConfig config)
{
    lastID++;
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ButtonElement>(lastID, text, position, std::move(callback), config));
    return lastID;
}

engine::gui::elements::UIElement *engine::UILayout::getElementById(uint16_t id)
{
    for (const auto &element : m_elements)
    {
        if (element->GetID() == id)
        {
            return element.get();
        }
    }

    return nullptr;
}

void engine::UILayout::update(const GameScreenData &data)
{
    for (const auto &element : m_elements)
    {
        element->Update(data);
    }
}

void engine::UILayout::drawLayout(sf::RenderWindow &window)
{
    for (auto &element : m_elements)
    {
        window.draw(*element);
    }
}