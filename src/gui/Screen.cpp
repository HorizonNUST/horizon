#include "Screen.hpp"

#include "GameScreenData.hpp"
#include "utils.hpp"

engine::GameScreen::GameScreen()
    : sound(soundBuffer)
{
    m_window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Horizon", sf::Style::Titlebar | sf::Style::Close);

    setBackgroundMusic("assets/Sound/background.mp3");

    // Layouts
    mainmenu = new UILayout(0);
    room1 = new UILayout(1);
    room2 = new UILayout(2);
    room3 = new UILayout(3);
    accuseSuspect = new UILayout(4);

    //Main menu
    mainmenu->AddButtonElement("Room 1", {20.f, 20.f}, [this]() {
        ChangeUILayout(*room1);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    mainmenu->AddButtonElement("Room 2", {20.f, 80.f}, [this]() {
        ChangeUILayout(*room2);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    mainmenu->AddButtonElement("Room 3", {20.f, 140.f}, [this]() {
        ChangeUILayout(*room3);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    mainmenu->AddButtonElement("Accuse Suspect", {20.f, 200.f}, [this]() {
        ChangeUILayout(*accuseSuspect);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    // First Room
    auto r1_text = room1->AddTextElement("Clue: Broken Vase", {40.f, 200.f});
    room1->getElementById(r1_text)->SetHidden(true);

    room1->AddButtonElement("Toggle Clue Fingerprints on Broken Vase", {20.f, 120.f}, 
        [this, r1_text]() {
            auto* elem = room1->getElementById(r1_text);
            elem->SetHidden(!elem->IsHidden());
            playAudioOneTime("assets/Sound/button.mp3");
        });

    room1->AddButtonElement("Back", {20.f, 20.f}, [this]() {
        ChangeUILayout(*mainmenu);
        playAudioOneTime("assets/Sound/button.mp3");
    });
    
    //Second Room
    auto r2_text = room2->AddTextElement("Clue: Footprints", {40.f, 200.f});
    room2->getElementById(r2_text)->SetHidden(true);

    room2->AddButtonElement("Toggle Footprint", {20.f, 120.f},
        [this, r2_text]() {
            auto* elem = room2->getElementById(r2_text);
            elem->SetHidden(!elem->IsHidden());
            playAudioOneTime("assets/Sound/button.mp3");
        });

    room2->AddButtonElement("Back", {20.f, 20.f}, [this]() {
        ChangeUILayout(*mainmenu);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    //Third Room
    auto r3_text = room3->AddTextElement("Clue: Blood Stain", {40.f, 200.f});
    room3->getElementById(r3_text)->SetHidden(true);

    room3->AddButtonElement("Toggle Blood Stain on wall", {20.f, 120.f}, 
        [this, r3_text]() {
            auto* elem = room3->getElementById(r3_text);
            elem->SetHidden(!elem->IsHidden());
            playAudioOneTime("assets/Sound/button.mp3");
        });

    room3->AddButtonElement("Back", {20.f, 20.f}, [this]() {
        ChangeUILayout(*mainmenu);
        playAudioOneTime("assets/Sound/button.mp3");
    });

    //Accuse Suspect Layout
    auto resultText = accuseSuspect->AddTextElement("", {40.f, 260.f});
    accuseSuspect->getElementById(resultText)->SetHidden(false);

    auto accuse = [&, resultText](std::string name) {
        auto* resultElement = dynamic_cast<engine::gui::elements::TextElement*>(accuseSuspect->getElementById(resultText));
        if (resultElement) {
            if (name == correctSuspect)
                resultElement->SetText("Correct, Bravo! " + name + " is the culprit.");
            else
                resultElement->SetText("You are Wrongly accusing innocent " + name);
        }
    };

    accuseSuspect->AddButtonElement("Suspect A", {20.f, 20.f}, [=]() { accuse("Mujtaba"); });
    accuseSuspect->AddButtonElement("Suspect B", {20.f, 80.f}, [=]() { accuse("Azhan"); });
    accuseSuspect->AddButtonElement("Suspect C", {20.f, 140.f}, [=]() { accuse("Sheharyar"); });

    accuseSuspect->AddButtonElement("Back", {20.f, 360.f}, [this]() {
        ChangeUILayout(*mainmenu);
        playAudioOneTime("assets/Sound/button.mp3");
    });
    /*secondLayout->AddButtonElement("Third Layout", {0.f, 0.f}, [this]() { //
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

    thirdLayout->AddImageElement("assets/image.jpeg", {200.f, 100.f});*/

    ChangeUILayout(*mainmenu);
}

engine::GameScreen::~GameScreen()
{
    delete mainmenu;
    delete room1;
    delete room2;
    delete room3;
    delete accuseSuspect;
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