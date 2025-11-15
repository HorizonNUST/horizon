#include "Screen.hpp"

#include "GameScreenData.hpp"
#include "utils.hpp"

engine::GameScreen::GameScreen()
{
    m_window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Horizon", sf::Style::Titlebar | sf::Style::Close);
}

engine::GameScreen::~GameScreen()
{
}

void engine::GameScreen::ChangeUILayout(UILayout &layout)
{
    if (m_ui_layout)
        if (layout == *m_ui_layout)
        {
            DEBUG_PRINT("SAME LAYOUT");
            return;
        }

    m_data.isClicking = false;
    m_ui_layout = &layout;
}

void engine::GameScreen::StartLoop()
{
    while (m_window.isOpen())
    {
        // poll all events
        while (const std::optional<sf::Event> &event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
            else if (event->is<sf::Event::MouseButtonPressed>())
                m_data.isClicking = true;
            else if (event->is<sf::Event::MouseButtonReleased>())
                m_data.isClicking = false;
        }

        // get m_data after polling events
        m_data.mousePos = sf::Mouse::getPosition(m_window);

        m_window.clear();

        if (m_ui_layout)
        {
            m_ui_layout->update(m_data);
            m_ui_layout->drawLayout(m_window);
        }

        m_window.display();
    }
}
void engine::GameScreen::setBackgroundMusic(const std::string& path){
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50.f); // 0 - 100
    backgroundMusic.play();
    std::cout << "Background music started: " << path << "\n";
}
void engine::GameScreen::playAudioOneTime(std::string path){
    sound.setBuffer(soundBuffer);
    sound.setVolume(80.f); // 0 - 100
    sound.play();
    std::cout << "Playing sound once: " << path << "\n";
}