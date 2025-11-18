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

    mujtabaLayout = new UILayout(20);
    azhanLayout = new UILayout(21);
    sheharyarLayout = new UILayout(22);

    createMainMenuLayout();
    createInvestigateLocationLayout();
    createInterrogateSuspectLayout();
    // evidenceLayout created on the fly
    // createViewEvidenceLayout()
    createMakeAccusationLayout();

    createMainMenuLayout();
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

    delete mujtabaLayout;
    delete azhanLayout;
    delete sheharyarLayout;
}

void engine::GameScreen::createMainMenuLayout()
{
    // Main Menu
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    mainMenuLayout->AddTextElement("Choose what to do", {50.f, 75.f});

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
        ChangeUILayout(*viewEvidenceLayout);
        createViewEvidenceLayout();
    });

    noEvidenceMainMenuTextId = mainMenuLayout->AddTextElement("No evidence collected yet.", {350.f, 7.5f + startPos.y + 3 * offsetY});
    mainMenuLayout->getElementById(noEvidenceMainMenuTextId)->SetHidden(true);

    mainMenuLayout->AddButtonElement("Make Accusation", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        if (collectedEvidence[0].empty())
        {
            // No evidence collected yet
            mainMenuLayout->getElementById(noEvidenceMainMenuTextId)->SetHidden(false);
            return;
        }

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

    investigateLocationLayout->AddTextElement("Where do you want to investigate?", {50.f, 75.f});

    clueInvestigateLayoutTextId = investigateLocationLayout->AddTextElement("-", {300.f, 150.f});
    investigateLocationLayout->getElementById(clueInvestigateLayoutTextId)->SetHidden(true);

    // BACK BUTTON

    backInvestigateLocationButtonId = investigateLocationLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });

    investigateLocationLayout->AddButtonElement("Kitchen", {startPos.x, startPos.y}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a knife in the Kitchen!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->getElementById(clueInvestigateLayoutTextId));
        elem->SetText("Found a torn crumpled page from victim\'s journal under the sink. A half-smoked cigarette in trash beside a note with victim\'s name. A half-finished cocktail on shelf — something victim never drank — suggests someone else prepared it.");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("Basement", {startPos.x, startPos.y + offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a mysterious footprint in the Basement!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->getElementById(clueInvestigateLayoutTextId));
        elem->SetText("Muddy shoeprints lead from furnace to broken window. Bloodstained rag lies on the workbench besides the victim\'s tools. Charred paper scraps are caught in the grate, as if someone tried burning evidence.");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("TV Lounge", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a broken TV remote in the TV Lounge!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->getElementById(clueInvestigateLayoutTextId));
        elem->SetText("Victim\'s gold watch is half-hidden under a spilled ashtray. A cracked lamp on the sideboard holds traces of soil on the shards. Muddy tracks run across the rug toward the backdoor, showing someone ran in a hurry. Their is a no landline phone and farmhouse is outsdie the city");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("Garden", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a strange footprint in the Garden!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->getElementById(clueInvestigateLayoutTextId));
        elem->SetText("Garden gate latch is snapped off, and a rosebush has a broken branch. Bloody fingerprints are on shed door. A single muddy bootprint is seen before disappearing.");
        elem->SetHidden(false);
    });
}

void engine::GameScreen::createInterrogateSuspectLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    interrogateSuspectLayout->AddTextElement("Who do you want to interrogate?", {50.f, 75.f});

    responseInterrogateTextId = interrogateSuspectLayout->AddTextElement("-", {300.f, 150.f});
    interrogateSuspectLayout->getElementById(responseInterrogateTextId)->SetHidden(true);

    // BACK BUTTON
    backInterrogateSuspectButtonId = interrogateSuspectLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });

    interrogateSuspectLayout->AddButtonElement("Jackson", {startPos.x, startPos.y}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Jackson was in the basement");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->getElementById(responseInterrogateTextId));
        elem->SetText("Detective: Where were you and what were you doing when the murder happened? \n\nJackson: I was in the basement, I was there around 8:15 PM when the lights flickered, I was fixing the lantern. I didn\'t hear anything upstairs — then I came up and discovered the body.");
        elem->SetHidden(false);
    });

    interrogateSuspectLayout->AddButtonElement("Hagrid", {startPos.x, startPos.y + offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Hagrid was in the TV lounge!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->getElementById(responseInterrogateTextId));
        elem->SetText("Detective: What about you and what were you doing when the murder happened? \n\nHagrid: I... I was in the TV lounge, rehearsing a speech. Actually, I answered a phone call to my editor at about 8:05 PM, so I didn\'t hear the gunshot. I must have dozed off soon after");
        elem->SetHidden(false);
    });

    interrogateSuspectLayout->AddButtonElement("Julian", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Julian was in the garden!");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->getElementById(responseInterrogateTextId));
        elem->SetText("Detective: What about you, sir? \n\nJulian: I was outside in the garden, planting some new bulbs. I kept the back gate open by mistake. I came in around 8:30 PM when I heard the window close, but by then everything was chaos.");
        elem->SetHidden(false);
    });
}

void engine::GameScreen::createViewEvidenceLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 30.f;
    constexpr sf::Vector2f lastButtonPos = {50.f, 4.f * 75.f + 150.f};

    viewEvidenceLayout->AddTextElement("Collected Evidence:", {50.f, 75.f});

    // BACK BUTTON
    backViewEvidenceButtonId = viewEvidenceLayout->AddButtonElement("Back to Main Menu", lastButtonPos, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });

    int index = 0;

    for (const std::string &evidence : collectedEvidence)
    {
        if (evidence.empty())
            continue;

        viewEvidenceLayout->AddTextElement(evidence, {startPos.x, startPos.y + index * offsetY});
        index++;
    }
}

void engine::GameScreen::createMakeAccusationLayout()
{
    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    accuseMakeAccusationTextId = makeAccusationLayout->AddTextElement("-", {300.f, 150.f});
    makeAccusationLayout->getElementById(accuseMakeAccusationTextId)->SetHidden(true);

    makeAccusationLayout->AddTextElement("Who do you want to accuse?", {50.f, 75.f});

    backMakeAccusationButtonId = makeAccusationLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });

    auto accuseSuspect = [this](const std::string &suspectName, const std::string &resultText)
    {
        if (m_game_state.gameRunning == false)
            return;

        playAudioOneTime("assets/Sound/button.mp3");

        auto elem = dynamic_cast<gui::elements::TextElement *>(makeAccusationLayout->getElementById(accuseMakeAccusationTextId));
        elem->SetText("You accused " + suspectName + "!\n" + resultText);
        elem->SetHidden(false);

        // disable all buttons
        investigateLocationLayout->DisableAllButtons();
        interrogateSuspectLayout->DisableAllButtons();
        // viewEvidenceLayout->DisableAllButtons(); // cannot disable as it is created on the fly
        makeAccusationLayout->DisableAllButtons();

        // enable back buttons
        auto investigateButton = dynamic_cast<gui::elements::ButtonElement *>(investigateLocationLayout->getElementById(backInvestigateLocationButtonId));
        investigateButton->SetDisabled(false);
        auto interrogateButton = dynamic_cast<gui::elements::ButtonElement *>(interrogateSuspectLayout->getElementById(backInterrogateSuspectButtonId));
        interrogateButton->SetDisabled(false);
        // skip viewEvidenceLayout as it is created on the fly
        auto makeAccusationButton = dynamic_cast<gui::elements::ButtonElement *>(makeAccusationLayout->getElementById(backMakeAccusationButtonId));
        makeAccusationButton->SetDisabled(false);

        m_game_state.gameRunning = false;
    };

    makeAccusationLayout->AddButtonElement("Mujtaba", {startPos.x, startPos.y}, [this, accuseSuspect]() { //
        accuseSuspect("Mujtaba", "The real culprit was Azhan.");
    });

    makeAccusationLayout->AddButtonElement("Azhan", {startPos.x, startPos.y + offsetY}, [this, accuseSuspect]() { //
        accuseSuspect("Azhan", "Congratulations! You found the real culprit!");
    });

    makeAccusationLayout->AddButtonElement("Sheharyar", {startPos.x, startPos.y + 2 * offsetY}, [this, accuseSuspect]() { //
        accuseSuspect("Sheharyar", "The real culprit was Azhan.");
    });
}

void engine::GameScreen::addEvidenceItem(const std::string &item)
{
    if (lastCollectedEvidenceIndex >= collectedEvidence.size())
    {
        DEBUG_PRINT("Evidence storage full, overwriting oldest evidence.");
    }

    for (const auto &evidence : collectedEvidence)
    {
        if (evidence == item)
        {
            DEBUG_PRINT("Evidence already collected");
            return;
        }
    }
    // overwrite in a circular manner
    collectedEvidence[lastCollectedEvidenceIndex % collectedEvidence.size()] = item;
    lastCollectedEvidenceIndex++;
    DEBUG_PRINT("Evidence added: " + item);
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
    if (!backgroundMusic.openFromFile(path))
    {
        throw std::runtime_error("Failed to load background music from file: " + path);
    }
    backgroundMusic.setLooping(true);
    backgroundMusic.setVolume(50.f); // 0 - 100
    backgroundMusic.play();
    DEBUG_PRINT("Background music started: " + path);
}
void engine::GameScreen::playAudioOneTime(std::string path)
{
    // Load the sound buffer from file
    if (!soundBuffer.loadFromFile("assets/Sound/button.mp3"))
    {
        throw std::runtime_error("Failed to load sound buffer from file: " + path);
    }
    sound.setBuffer(soundBuffer);
    sound.setVolume(80.f); // 0 - 100
    sound.play();
    DEBUG_PRINT("Played sound: " + path);
}