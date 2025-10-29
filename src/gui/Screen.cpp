#include "Screen.hpp"

Screen::Screen()
{
    m_window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Horizon", sf::Style::Titlebar | sf::Style::Close);
}

Screen::~Screen()
{
}

void Screen::StartLoop()
{
    while (m_window.isOpen())
    {
        while (const std::optional<sf::Event> &event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
        }

        m_window.clear();
        m_window.display();
    }
}
