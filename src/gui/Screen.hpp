#pragma once
#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UILayout.hpp"

namespace engine
{
    class GameScreen
    {
    private:
        sf::RenderWindow m_window;
        UILayout m_ui_layout;

    public:
        GameScreen();
        ~GameScreen();

        void StartLoop();
    };
}