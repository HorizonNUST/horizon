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
    GameScreenData data;

    while (m_window.isOpen())
    {
        // poll all events
        while (const std::optional<sf::Event> &event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
            else if (event->is<sf::Event::MouseButtonPressed>())
                data.isClicking = true;
            else if (event->is<sf::Event::MouseButtonReleased>())
                data.isClicking = false;
        }
        
        // get data after polling events
        data.mousePos = sf::Mouse::getPosition(m_window);

        m_window.clear();

        m_ui_layout.Update(data);
        m_ui_layout.DrawLayout(m_window);

        m_window.display();
    }
}
