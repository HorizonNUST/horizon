#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "UILayout.hpp"
#include "utils.hpp"

namespace engine
{
    class UILayout;

    struct GameState
    {
        bool gameRunning = true;
    };

    /// @brief Main Screen
    class GameScreen
    {
    private:
        sf::RenderWindow m_window;
        UILayout *m_ui_layout = nullptr;
        GameScreenData m_data;
        GameState m_game_state;

        // music/sound
        sf::Music backgroundMusic;   // for long background track
        sf::SoundBuffer soundBuffer; // for short sound
        sf::Sound sound;

        std::array<std::string, 4> collectedEvidence;
        size_t lastCollectedEvidenceIndex = 0;

        // Main Menu
        UILayout *mainMenuLayout = nullptr;
        UILayout *investigateLocationLayout = nullptr;
        UILayout *interrogateSuspectLayout = nullptr;
        UILayout *viewEvidenceLayout = nullptr;
        UILayout *makeAccusationLayout = nullptr;

        // Investigate Location Layouts
        UILayout *kitchenLayout = nullptr;
        UILayout *basementLayout = nullptr;
        UILayout *tvLoungeLayout = nullptr;
        UILayout *gardenLayout = nullptr;

        // Interrogate Suspect Layouts
        UILayout *mujtabaLayout = nullptr;
        UILayout *azhanLayout = nullptr;
        UILayout *sheharyarLayout = nullptr;

        // Text Element IDs
        uint16_t clueInvestigateLayoutTextId;
        uint16_t responseInterrogateTextId;
        uint16_t accuseMakeAccusationTextId;
        uint16_t noEvidenceMainMenuTextId;

        // Back Buttons IDs
        uint16_t backInvestigateLocationButtonId;
        uint16_t backInterrogateSuspectButtonId;
        uint16_t backViewEvidenceButtonId;
        uint16_t backMakeAccusationButtonId;

        // Image ID
        uint16_t imageId;

        void createMainMenuLayout();
        void createInvestigateLocationLayout();
        void createInterrogateSuspectLayout();
        void createViewEvidenceLayout();
        void createMakeAccusationLayout();

        void addEvidenceItem(const std::string &item);

        std::string getRandomImagePath() const;

    public:
        GameScreen();
        ~GameScreen();

        /// @brief To Change `UILayout` to given layout
        /// @param layout `UILayout&` handle memory yourself
        void ChangeUILayout(UILayout &layout);

        /// @brief To Start the Game Loop
        void StartLoop();

        void setBackgroundMusic(const std::string &path);
        void playAudioOneTime(std::string path);
    };
}