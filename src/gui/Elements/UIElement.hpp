#pragma once
#include <SFML/Graphics.hpp>

#include "GameScreenData.hpp"

namespace engine::gui::elements
{
    class UIElement : public sf::Drawable
    {
    public:
        UIElement() = default;
        virtual ~UIElement() = default; // always good practice in base classes

        /// @brief Used to pass in screen data to elements
        virtual void Update(const GameScreenData &data) {};

    protected:
        /// @brief Draw method to implement for `sf::Drawable`
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    };
}
