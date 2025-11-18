#pragma once
#include "UIElement.hpp"

#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace engine::gui::elements
{
    class TextElement : public UIElement
    {
    public:
        TextElement(uint16_t id, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size = CONSTANTS::ZERO_VECTOR2F);

        /// @brief Set the text of the Element
        /// @param newText The New Text
        void SetText(const std::string &newText);

    private:
        // bitmap font texture (sprite sheet)
        sf::Texture m_texture;

        // vertex array storing quads for all characters
        sf::VertexArray m_vertices;

        // glyph size in pixels (width, height)
        unsigned int m_glyphWidth{8};
        unsigned int m_glyphHeight{8};

        // horizontal advance (spacing) between characters (in pixels)
        float m_charSpacing{0.0f};

        // top-left position where text is drawn
        sf::Vector2f m_position;

        // cached text string
        std::string m_textString;

        // utility: rebuild texture from image -> binary alpha (background -> transparent)
        void buildTextureMask(const sf::Image &srcImage, sf::Image &outImage, unsigned int tolerance = 24u) const;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
