#include <SFML/Graphics.hpp>

namespace engine::gui::elements
{
    class UIElement : public sf::Drawable
    {
    public:
        UIElement() = default;
        virtual ~UIElement() = default; // always good practice in base classes

    protected:
        /// @brief Draw method to implement for `sf::Drawable`
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    };
}
