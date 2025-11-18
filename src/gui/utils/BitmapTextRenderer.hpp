#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace engine::gui
{
    /// @brief Renders text using a bitmap font atlas
    class BitmapTextRenderer
    {
    public:
        BitmapTextRenderer();

        /// @brief Initialize with position and optional spacing
        /// @param position Starting position for text
        /// @param charSpacing Spacing between characters (default 0)
        void setPosition(const sf::Vector2f &position);
        void setCharSpacing(float spacing);

        /// @brief Set the text to render
        /// @param text The text string
        void setText(const std::string &text);

        /// @brief Set the color of the text
        /// @param color Text color
        void setColor(const sf::Color &color);

        /// @brief Get the bounds of the rendered text
        /// @return FloatRect containing the text bounds
        sf::FloatRect getLocalBounds() const;

        /// @brief Get the global bounds (position + size)
        /// @return FloatRect containing the global bounds
        sf::FloatRect getGlobalBounds() const;

        /// @brief Draw the text
        /// @param target Render target
        /// @param states Render states
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        /// @brief Get static font texture (shared across all instances)
        static const sf::Texture& getTexture();

    private:
        static sf::Texture s_texture;
        static bool s_textureLoaded;

        sf::VertexArray m_vertices;
        sf::Vector2f m_position;
        std::string m_textString;
        sf::Color m_color;
        float m_charSpacing;

        unsigned int m_glyphWidth;
        unsigned int m_glyphHeight;

        /// @brief Rebuild vertex array from current text
        void rebuildVertices();

        /// @brief Load the bitmap font texture (called once)
        static void loadTexture();
    };
}
