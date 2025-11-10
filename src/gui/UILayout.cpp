#include "UILayout.hpp"

engine::UILayout::UILayout()
{
}

void engine::UILayout::AddTextElement(const std::string &text, const sf::Vector2f &position)
{
    m_elements.emplace_back(std::make_unique<engine::gui::elements::TextElement>(text, position));
}

void engine::UILayout::AddImageElement(const std::string &imagePath, const sf::Vector2f &position)
{
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ImageElement>(imagePath, position));
}

void engine::UILayout::AddButtonElement(const std::string &text, const sf::Vector2f &position, std::function<void()> callback, engine::gui::elements::ButtonConfig config)
{
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ButtonElement>(text, position, std::move(callback), config));
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