#pragma once
#include "UIElement.hpp"

namespace engine::gui::elements
{
    class ImageElement : public UIElement
    {
    public:
        ImageElement(const std::string &imagePath, const sf::Vector2f &position);

        inline void setImage(const std::string &newPath);

    private:
        sf::Texture m_texture;
        std::optional<sf::Sprite> m_sprite;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
