#include <SFML/Graphics.hpp>

namespace engine::gui::elements
{
    class UIElement : public sf::Drawable
    {
    public:
        // Example: store a shape or sprite to draw
        sf::RectangleShape shape;

        UIElement()
        {
            shape.setSize({100.f, 50.f});
            shape.setFillColor(sf::Color::Blue);
            shape.setPosition({100.f, 100.f});
        }

    protected:
        // This is the only function sf::Drawable requires you to implement
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(shape, states);
        }
    };
}
