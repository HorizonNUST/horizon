#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>

#include "TextElement.hpp"
#include "utils.hpp"

namespace engine
{
    class UILayout
    {
    private:
        gui::elements::TextElement elementA;

    public:
        UILayout();
        
        static utils::Event<std::string> elementAEvent;

        void DrawLayout(sf::RenderWindow &window);
    };
}