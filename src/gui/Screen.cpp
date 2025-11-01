#include "Screen.hpp"

#include "GameScreenData.hpp"

engine::GameScreen::GameScreen()
{
    m_window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Horizon", sf::Style::Titlebar | sf::Style::Close);
}

engine::GameScreen::~GameScreen()
{
}

void engine::GameScreen::StartLoop()
{
    while (m_window.isOpen())
    {
        while (const std::optional<sf::Event> &event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
        }

        m_window.clear();

        // Update
        GameScreenData data;
        data.mousePos = sf::Mouse::getPosition();
        
        m_ui_layout.Update(data);

        // Draw
        m_ui_layout.DrawLayout(m_window);

        m_window.display();
    }
}
