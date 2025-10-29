#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"

namespace engine
{
    class GameScreen
    {
    private:
        std::vector<gui::elements::UIElement> m_ui_elements;
        sf::RenderWindow m_window;

    public:
        GameScreen();
        ~GameScreen();

        void StartLoop();
    };
}