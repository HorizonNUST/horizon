#include "Screen.hpp"

#include "GameScreenData.hpp"
#include "utils.hpp"

engine::GameScreen::GameScreen()
    : sound(soundBuffer)
{
    m_window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Horizon", sf::Style::Titlebar | sf::Style::Close);

    firstLayout = new UILayout(1);
    secondLayout = new UILayout(2);
    thirdLayout = new UILayout(3);

    firstLayout->AddButtonElement("Second Layout", {0.f, 0.f}, [this]() { //
        ChangeUILayout(*secondLayout);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    secondLayout->AddButtonElement("Third Layout", {0.f, 0.f}, [this]() { //
        ChangeUILayout(*thirdLayout);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    auto layoutBElemID = secondLayout->AddTextElement("TEST", {0.f, 120.f});
    secondLayout->getElementById(layoutBElemID)->SetHidden(true);
    secondLayout->AddButtonElement("Show Test", {0.f, 60.f}, [this, layoutBElemID]() { //
        secondLayout->getElementById(layoutBElemID)->SetHidden(!secondLayout->getElementById(layoutBElemID)->IsHidden());
        playAudioOneTime("assets/Sound/button.mp3");
    });

    thirdLayout->AddButtonElement("First Layout", {0.f, 0.f}, [this]() { //
        ChangeUILayout(*firstLayout);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    ChangeUILayout(*firstLayout);

    setBackgroundMusic("assets/Sound/background.mp3");
}

engine::GameScreen::~GameScreen()
{
    delete firstLayout;
    delete secondLayout;
    delete thirdLayout;
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
void engine::GameScreen::setBackgroundMusic(const std::string &path)
{
    // Load the sound buffer from file
    if (!backgroundMusic.openFromFile("assets/Sound/background.mp3"))
    {
        std::cerr << "Failed to load sound buffer from file: assets/Sound/button.mp3\n";
    }
    backgroundMusic.setLooping(true);
    backgroundMusic.setVolume(50.f); // 0 - 100
    backgroundMusic.play();
    std::cout << "Background music started: " << path << "\n";
}
void engine::GameScreen::playAudioOneTime(std::string path)
{
    // Load the sound buffer from file
    if (!soundBuffer.loadFromFile("assets/Sound/button.mp3"))
    {
        std::cerr << "Failed to load sound buffer from file: assets/Sound/button.mp3\n";
    }
    sound.setBuffer(soundBuffer);
    sound.setVolume(80.f); // 0 - 100
    sound.play();
    std::cout << "Playing sound once: " << path << "\n";
}