#include "Screen.hpp"

#include "GameScreenData.hpp"
#include "utils.hpp"

engine::GameScreen::GameScreen()
    : sound(soundBuffer)
{
    m_window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Horizon", sf::Style::Titlebar | sf::Style::Close);

    setBackgroundMusic("assets/Sound/background.mp3");

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
}

void engine::GameScreen::createMainMenuLayout()
{
    // random background image
    mainMenuLayout->AddImageElement(getRandomImagePath(), {0.f, 0.f});

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
        viewEvidenceLayout->ClearLayout(); // clear previous evidence entries
        createViewEvidenceLayout();
        ChangeUILayout(*viewEvidenceLayout);
    });

    noEvidenceMainMenuTextId = mainMenuLayout->AddTextElement("No evidence collected yet.", {350.f, 7.5f + startPos.y + 3 * offsetY});
    mainMenuLayout->GetElementById(noEvidenceMainMenuTextId)->SetHidden(true);

    mainMenuLayout->AddButtonElement("Make Accusation", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        if (collectedEvidence[0].empty())
        {
            // No evidence collected yet
            mainMenuLayout->GetElementById(noEvidenceMainMenuTextId)->SetHidden(false);
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
    investigateLocationLayout->AddImageElement(getRandomImagePath(), {0.f, 0.f});

    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    investigateLocationLayout->AddTextElement("Where do you want to investigate?", {50.f, 75.f});

    clueInvestigateLayoutTextId = investigateLocationLayout->AddTextElement("-", {300.f, 150.f});
    investigateLocationLayout->GetElementById(clueInvestigateLayoutTextId)->SetHidden(true);

    // BACK BUTTON

    backInvestigateLocationButtonId = investigateLocationLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });

    investigateLocationLayout->AddButtonElement("Kitchen", {startPos.x, startPos.y}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found a torn crumpled page in the Kitchen.");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->GetElementById(clueInvestigateLayoutTextId));
        elem->SetText("Found a torn crumpled page\n"
                      "from victim\'s journal under\n"
                      "the sink.\n"
                      "A half-smoked cigarette in\n"
                      "trash beside a note with\n"
                      "victim\'s name.\n"
                      "A half-finished cocktail\n"
                      "on shelf, something victim\n"
                      "never drank, suggests someone\n"
                      "else prepared it.");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("Basement", {startPos.x, startPos.y + offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found mysterious footprints in the Basement.");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->GetElementById(clueInvestigateLayoutTextId));
        elem->SetText("Muddy shoeprints lead from\n"
                      "furnace to broken window.\n"
                      "Bloodstained rag lies on the\n"
                      "workbench besides the\n"
                      "victim\'s tools.\n"
                      "Charred paper scraps are\n"
                      "caught in the grate, as if\n"
                      "someone tried burning evidence");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("TV Lounge", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found that there is no contact to outside world from the TV Lounge.");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->GetElementById(clueInvestigateLayoutTextId));
        elem->SetText("Victim\'s gold watch is\n"
                      "half-hidden under a spilled\n"
                      "ashtray. A cracked lamp on\n"
                      "the sideboard holds traces\n"
                      "of soil on the shards.\n"
                      "Muddy tracks run across the\n"
                      "rug toward the backdoor,\n"
                      "showing someone ran in a hurry.\n"
                      "There is no landline phone\n"
                      "and farmhouse is outside the\n"
                      "city");
        elem->SetHidden(false);
    });

    investigateLocationLayout->AddButtonElement("Garden", {startPos.x, startPos.y + 3 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Found and muddy bootprint in the Garden.");

        auto elem = dynamic_cast<gui::elements::TextElement *>(investigateLocationLayout->GetElementById(clueInvestigateLayoutTextId));
        elem->SetText("Garden gate latch is snapped\n"
                      "off, and a rosebush has a\n"
                      "broken branch.\n"
                      "Bloody fingerprints are\n"
                      "on shed door.\n"
                      "A single muddy bootprint\n"
                      "is seen before disappearing");
        elem->SetHidden(false);
    });
}

void engine::GameScreen::createInterrogateSuspectLayout()
{
    interrogateSuspectLayout->AddImageElement(getRandomImagePath(), {0.f, 0.f});

    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    interrogateSuspectLayout->AddTextElement("Who do you want to interrogate?", {50.f, 75.f});

    responseInterrogateTextId = interrogateSuspectLayout->AddTextElement("-", {250.f, 150.f});
    interrogateSuspectLayout->GetElementById(responseInterrogateTextId)->SetHidden(true);

    // BACK BUTTON
    backInterrogateSuspectButtonId = interrogateSuspectLayout->AddButtonElement("Back to Main Menu", {startPos.x, startPos.y + 4 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");
        ChangeUILayout(*mainMenuLayout);
    });

    interrogateSuspectLayout->AddButtonElement("Jackson", {startPos.x, startPos.y}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Jackson was in the basement.");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->GetElementById(responseInterrogateTextId));
        elem->SetText("Detective: Where were you and\n"
                      "what were you doing when the\n"
                      "murder happened?\n"
                      "\n"
                      "Jackson: I was in the basement,\n"
                      "I was there around 8:15 PM when\n"
                      "the lights flickered, I was fixing\n"
                      "the lantern. I didn\'t hear anything\n"
                      "upstairs — then I came up and\n"
                      "discovered the body.");
        elem->SetHidden(false);
    });

    interrogateSuspectLayout->AddButtonElement("Hagrid", {startPos.x, startPos.y + offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Hagrid was in the TV lounge.");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->GetElementById(responseInterrogateTextId));
        elem->SetText("Detective: Where were you and\n"
                      "what were you doing when the\n"
                      "murder happened?\n"
                      "\n"
                      "Hagrid: I... I was in the TV\n"
                      "lounge, rehearsing a speech.\n"
                      "Actually, I answered a phone\n"
                      "call to my editor at about\n"
                      "8:05 PM, so I didn\'t hear the\n"
                      "gunshot. I must have dozed off\n"
                      "soon after");
        elem->SetHidden(false);
    });

    interrogateSuspectLayout->AddButtonElement("Julian", {startPos.x, startPos.y + 2 * offsetY}, [this]() { //
        playAudioOneTime("assets/Sound/button.mp3");

        addEvidenceItem("Julian was outside the garden.");

        auto elem = dynamic_cast<gui::elements::TextElement *>(interrogateSuspectLayout->GetElementById(responseInterrogateTextId));
        elem->SetText("Detective: Where were you and\n"
                      "what were you doing when the\n"
                      "murder happened?\n"
                      "\n"
                      "Julian: I was outside in the\n"
                      "garden, planting some new bulbs.\n"
                      "I kept the back gate open by\n"
                      "mistake.\n"
                      "I came in around 8:30 PM when I\n"
                      "heard the window close, but by\n"
                      "then everything was chaos.");
        elem->SetHidden(false);
    });
}

void engine::GameScreen::createViewEvidenceLayout()
{
    viewEvidenceLayout->AddImageElement(getRandomImagePath(), {0.f, 0.f});

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
    makeAccusationLayout->AddImageElement(getRandomImagePath(), {0.f, 0.f});

    constexpr sf::Vector2f startPos = {50.f, 150.f};
    constexpr float offsetY = 75.f;

    accuseMakeAccusationTextId = makeAccusationLayout->AddTextElement("-", {300.f, 150.f});
    makeAccusationLayout->GetElementById(accuseMakeAccusationTextId)->SetHidden(true);

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

        auto elem = dynamic_cast<gui::elements::TextElement *>(makeAccusationLayout->GetElementById(accuseMakeAccusationTextId));
        elem->SetText("You accused " + suspectName + "!\n" + resultText);
        elem->SetHidden(false);

        // disable all buttons
        investigateLocationLayout->DisableAllButtons();
        interrogateSuspectLayout->DisableAllButtons();
        // viewEvidenceLayout->DisableAllButtons(); // cannot disable as it is created on the fly
        makeAccusationLayout->DisableAllButtons();

        // enable back buttons
        auto investigateButton = dynamic_cast<gui::elements::ButtonElement *>(investigateLocationLayout->GetElementById(backInvestigateLocationButtonId));
        investigateButton->SetDisabled(false);
        auto interrogateButton = dynamic_cast<gui::elements::ButtonElement *>(interrogateSuspectLayout->GetElementById(backInterrogateSuspectButtonId));
        interrogateButton->SetDisabled(false);
        // skip viewEvidenceLayout as it is created on the fly
        auto makeAccusationButton = dynamic_cast<gui::elements::ButtonElement *>(makeAccusationLayout->GetElementById(backMakeAccusationButtonId));
        makeAccusationButton->SetDisabled(false);

        m_game_state.gameRunning = false;
    };

    makeAccusationLayout->AddButtonElement("Jackson", {startPos.x, startPos.y}, [this, accuseSuspect]() { //
        accuseSuspect("Jackson", "Wrong accusation! The real culprit was Hagrid.");
    });

    makeAccusationLayout->AddButtonElement("Hagrid", {startPos.x, startPos.y + offsetY}, [this, accuseSuspect]() { //
        accuseSuspect("Hagrid", "Hagrid Confessed! You solved the case!");
    });

    makeAccusationLayout->AddButtonElement("Julian", {startPos.x, startPos.y + 2 * offsetY}, [this, accuseSuspect]() { //
        accuseSuspect("Julian", "Wrong accusation! The real culprit was Hagrid.");
    });
}

void engine::GameScreen::addEvidenceItem(const std::string &item)
{
    if (lastCollectedEvidenceIndex >= collectedEvidence.size())
    {
        DEBUG_PRINT("Evidence array full, overwriting oldest evidence.");
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

std::string engine::GameScreen::getRandomImagePath() const
{
    int randomValue = utils::getRandomInt(1, 4);
    switch (randomValue)
    {
    case 1:
        return "assets/bgs/basement.png";
    case 2:
        return "assets/bgs/garden.png";
    case 3:
        return "assets/bgs/kitchen.png";
    case 4:
        return "assets/bgs/tv-lounge.png";
    default:
        return "assets/bgs/basement.png";
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