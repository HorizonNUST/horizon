#include "Screen.hpp"

#include "GameScreenData.hpp"
#include "utils.hpp"

engine::GameScreen::GameScreen()
    : sound(soundBuffer)
{
    m_window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Horizon", sf::Style::Titlebar | sf::Style::Close);

    // setBackgroundMusic("assets/Sound/background.mp3");

    // Layouts
    mainMenuLayout = new UILayout(0);
    investigateLocationLayout = new UILayout(1);
    interrogateSuspectLayout = new UILayout(2);
    viewEvidenceLayout = new UILayout(3);
    makeAccusationLayout = new UILayout(4);

    kitchenLayout = new UILayout(10);
    basementLayout = new UILayout(11);
    tvLoungeLayout = new UILayout(12);
    gardenLayout = new UILayout(13);

    createMainMenuLayout();
    createInvestigateLocationLayout();
    createInterrogateSuspectLayout();
    // evidence created on the fly
    createMakeAccusationLayout();

    ChangeUILayout(*mainMenuLayout);
}
engine::GameScreen::~GameScreen()
{
    delete mainMenuLayout;
    delete investigateLocationLayout;
    delete interrogateSuspectLayout;
    delete viewEvidenceLayout;
    delete makeAccusationLayout;

    delete kitchenLayout;
    delete basementLayout;
    delete tvLoungeLayout;
    delete gardenLayout;
}

void engine::GameScreen::createMainMenuLayout()
{
    // Main Menu
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    mainMenuLayout->AddButtonElement("Investigate Location", {startPos.x, startPos.y}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*investigateLocationLayout);
    });

    mainMenuLayout->AddButtonElement("Interrogate Suspect", {startPos.x, startPos.y + offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*interrogateSuspectLayout);
    });

    mainMenuLayout->AddButtonElement("View Evidence", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        viewEvidenceLayout->ClearLayout();
        createViewEvidenceLayout();
        ChangeUILayout(*viewEvidenceLayout);
    });

    mainMenuLayout->AddButtonElement("Make Accusation", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*makeAccusationLayout);
    });

    mainMenuLayout->AddButtonElement("Exit Game", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        m_window.close();
    });
}

void engine::GameScreen::createInvestigateLocationLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    uint16_t clueTextId = investigateLocationLayout->AddTextElement("-", {300.f, 150.f});
    investigateLocationLayout->getElementById(clueTextId)->SetHidden(true);

    investigateLocationLayout->AddButtonElement("Kitchen", {startPos.x, startPos.y}, [this, clueTextId]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a knife in the Kitchen!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->getElementById(clueTextId));
        elem->SetText("Found a bloody knife\nin the Kitchen!");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("Basement", {startPos.x, startPos.y + offsetY}, [this, clueTextId]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a mysterious footprint in the Basement!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->getElementById(clueTextId));
        elem->SetText("Found a mysterious footprint\nin the Basement!");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("TV Lounge", {startPos.x, startPos.y + 2 * offsetY}, [this, clueTextId]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a broken TV remote in the TV Lounge!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->getElementById(clueTextId));
        elem->SetText("Found a broken TV remote\nin the TV Lounge!");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("Garden", {startPos.x, startPos.y + 3 * offsetY}, [this, clueTextId]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a strange footprint in the Garden!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->getElementById(clueTextId));
        elem->SetText("Found a strange footprint\nin the Garden!");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });
}

void engine::GameScreen::createInterrogateSuspectLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    uint16_t responseTextId = interrogateSuspectLayout->AddTextElement("-", {300.f, 150.f});
    interrogateSuspectLayout->getElementById(responseTextId)->SetHidden(true);

    interrogateSuspectLayout->AddButtonElement("Mujtaba", {startPos.x, startPos.y}, [this, responseTextId]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Mujtaba was in the kitchen!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->getElementById(responseTextId));
        elem->SetText("Mujtaba: I was in the kitchen\nlooking for a snack.");
        elem->SetHidden(false);
    });

    interrogateSuspectLayout->AddButtonElement("Azhan", {startPos.x, startPos.y + offsetY}, [this, responseTextId]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Azhan was in the basement!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->getElementById(responseTextId));
        elem->SetText("Azhan: I was in the basement\nchecking the boiler.");
        elem->SetHidden(false);
    });

    interrogateSuspectLayout->AddButtonElement("Sheharyar", {startPos.x, startPos.y + 2 * offsetY}, [this, responseTextId]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Sheharyar was in the TV lounge!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->getElementById(responseTextId));
        elem->SetText("Sheharyar: I was in the TV\nlounge watching my favorite\nshow.");
        elem->SetHidden(false);
    });

    interrogateSuspectLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });
}

void engine::GameScreen::createViewEvidenceLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 30.f;
    constexpr sf::Vector2f lastButtonPos = {50.f, 4.f * 75.f + 150.f};

    int index = 0;

    for (const std::string &evidence : collectedEvidence)
    {
        if (evidence.empty())
            continue;

        viewEvidenceLayout->AddTextElement(evidence, {startPos.x, startPos.y + index * offsetY});
        index++;
    }

    viewEvidenceLayout->AddButtonElement("Back to Main Menu", lastButtonPos, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });
}

void engine::GameScreen::createMakeAccusationLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    makeAccusationLayout->AddButtonElement("Accuse Suspect A", {startPos.x, startPos.y}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        // Logic for accusing Suspect A
    });

    makeAccusationLayout->AddButtonElement("Accuse Suspect B", {startPos.x, startPos.y + offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        // Logic for accusing Suspect B
    });

    makeAccusationLayout->AddButtonElement("Accuse Suspect C", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        // Logic for accusing Suspect C
    });

    makeAccusationLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });
}

void engine::GameScreen::addEvidenceItem(const std::string &item)
{
    if (lastCollectedEvidenceIndex < collectedEvidence.size())
    {
        for (const auto &evidence : collectedEvidence)
        {
            if (evidence == item)
            {
                DEBUG_PRINT("Evidence already collected");
                return;
            }
        }
        collectedEvidence[lastCollectedEvidenceIndex] = item;
        lastCollectedEvidenceIndex++;
        DEBUG_PRINT("Evidence added: " + item);
    }
    else
    {
        DEBUG_PRINT("Evidence storage full, cannot add more evidence");
    }
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