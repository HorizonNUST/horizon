#pragma once
#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UILayout.hpp"

namespace engine
{
    class UILayout;

    /// @brief Main Screen
    class GameScreen
    {
    private:
        sf::RenderWindow m_window;
        UILayout* m_ui_layout = nullptr;

    public:
        GameScreen();
        ~GameScreen();

        /// @brief To Change `UILayout` to given layout
        /// @param layout `UILayout&` handle memory yourself
        void ChangeUILayout(UILayout& layout);

        /// @brief To Start the Game Loop
        void StartLoop();
    };
}