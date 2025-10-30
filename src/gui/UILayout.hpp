#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "utils.hpp"

namespace engine
{
    class UILayout
    {
    private:
        gui::elements::UIElement elementA;

    public:
        static utils::Event<std::string> elementAEvent;

        void DrawLayout(sf::RenderWindow &window);
    };
}