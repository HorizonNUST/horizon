#pragma once
#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UILayout.hpp"

#include <SFML/Audio.hpp>

namespace engine
{
    class UILayout;

    /// @brief Main Screen
    class GameScreen
    {
    private:
        sf::RenderWindow m_window;
        UILayout *m_ui_layout = nullptr;
        GameScreenData m_data;

        // music/sound
        sf::Music backgroundMusic;   // for long background track
        sf::SoundBuffer soundBuffer; // for short sound
        sf::Sound sound;

        std::array<std::string, 8> collectedEvidence;
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

        void createMainMenuLayout();
        void createInvestigateLocationLayout();
        void createInterrogateSuspectLayout();
        void createViewEvidenceLayout();
        void createMakeAccusationLayout();

        void addEvidenceItem(const std::string &item);

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