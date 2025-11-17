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

        //music/sound
        sf::Music backgroundMusic;   // for long background track
        sf::SoundBuffer soundBuffer; // for short sound
        sf::Sound sound;

        // Layouts
        UILayout* mainmenu = nullptr;
        UILayout* room1 = nullptr;
        UILayout* room2 = nullptr;
        UILayout* room3 = nullptr;
        UILayout* accuseSuspect = nullptr;

        std::string correctSuspect = "Suspect A";

    public:
        GameScreen();
        ~GameScreen();

        /// @brief To Change `UILayout` to given layout
        /// @param layout `UILayout&` handle memory yourself
        void ChangeUILayout(UILayout &layout);

        /// @brief To Start the Game Loop
        void StartLoop();

        void setBackgroundMusic(const std::string& path);
        void playAudioOneTime(std::string path);
    };
}