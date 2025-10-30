#include "UILayout.hpp"

engine::UILayout::UILayout()
{
    m_elements.emplace_back(std::make_unique<engine::gui::elements::TextElement>("Title", sf::Vector2f{50.f, 30.f}));
    m_elements.emplace_back(std::make_unique<engine::gui::elements::TextElement>("Subtitle", sf::Vector2f{50.f, 80.f}));
    m_elements.emplace_back(std::make_unique<engine::gui::elements::ImageElement>("assets/image.jpeg", sf::Vector2f{400.f, 50.f}));
    m_elements.emplace_back(std::make_unique<engine::gui::elements::TextElement>("Press Enter to Start", sf::Vector2f{250.f, 500.f}));
}

void engine::UILayout::DrawLayout(sf::RenderWindow &window)
{
    for (auto &element : m_elements)
    {
        window.draw(*element);
    }
}