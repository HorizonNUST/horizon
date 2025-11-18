#include "BitmapTextRenderer.hpp"
#include <stdexcept>

namespace engine::gui
{
    // Static member initialization
    sf::Texture BitmapTextRenderer::s_texture;
    bool BitmapTextRenderer::s_textureLoaded = false;

    BitmapTextRenderer::BitmapTextRenderer()
        : m_position(0.f, 0.f), m_color(sf::Color::White), m_charSpacing(0.f), m_glyphWidth(8), m_glyphHeight(8)
    {
        loadTexture();
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    }

    void BitmapTextRenderer::loadTexture()
    {
        if (s_textureLoaded)
            return;

        if (!s_texture.loadFromFile("assets/bitmap_font.png"))
        {
            throw std::runtime_error("assets/bitmap_font.png not found");
        }

        s_texture.setSmooth(false);
        s_textureLoaded = true;
    }

    const sf::Texture &BitmapTextRenderer::getTexture()
    {
        loadTexture();
        return s_texture;
    }

    void BitmapTextRenderer::setPosition(const sf::Vector2f &position)
    {
        m_position = position;
        rebuildVertices();
    }

    void BitmapTextRenderer::setCharSpacing(float spacing)
    {
        m_charSpacing = spacing;
        rebuildVertices();
    }

    void BitmapTextRenderer::setText(const std::string &text)
    {
        m_textString = text;
        rebuildVertices();
    }

    void BitmapTextRenderer::setColor(const sf::Color &color)
    {
        m_color = color;

        // Update existing vertices' colors
        for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
        {
            m_vertices[i].color = m_color;
        }
    }

    void BitmapTextRenderer::rebuildVertices()
    {
        m_vertices.clear();

        if (m_textString.empty())
            return;

        const unsigned int texW = s_texture.getSize().x;
        const unsigned int cols = texW / m_glyphWidth;

        float cursorX = m_position.x;
        float cursorY = m_position.y;

        for (char ch : m_textString)
        {
            if (ch == '\n')
            {
                cursorX = m_position.x;
                cursorY += m_glyphHeight;
                continue;
            }

            unsigned char uc = static_cast<unsigned char>(ch);

            // Skip non-printable characters
            if (uc < 32 || uc > 127)
            {
                cursorX += m_glyphWidth + m_charSpacing;
                continue;
            }

            // Calculate atlas index (characters start at ASCII 32)
            unsigned int index = uc - 32;

            // Calculate texture coordinates
            float u = static_cast<float>((index % cols) * m_glyphWidth);
            float v = static_cast<float>((index / cols) * m_glyphHeight);

            // Create 6 vertices for 2 triangles (forming a quad)
            sf::Vertex vertices[6];

            // Triangle 1
            vertices[0].position = sf::Vector2f(cursorX, cursorY);
            vertices[1].position = sf::Vector2f(cursorX + m_glyphWidth, cursorY);
            vertices[2].position = sf::Vector2f(cursorX, cursorY + m_glyphHeight);

            vertices[0].texCoords = sf::Vector2f(u, v);
            vertices[1].texCoords = sf::Vector2f(u + m_glyphWidth, v);
            vertices[2].texCoords = sf::Vector2f(u, v + m_glyphHeight);

            // Triangle 2
            vertices[3].position = sf::Vector2f(cursorX + m_glyphWidth, cursorY);
            vertices[4].position = sf::Vector2f(cursorX + m_glyphWidth, cursorY + m_glyphHeight);
            vertices[5].position = sf::Vector2f(cursorX, cursorY + m_glyphHeight);

            vertices[3].texCoords = sf::Vector2f(u + m_glyphWidth, v);
            vertices[4].texCoords = sf::Vector2f(u + m_glyphWidth, v + m_glyphHeight);
            vertices[5].texCoords = sf::Vector2f(u, v + m_glyphHeight);

            // Set color
            for (int i = 0; i < 6; ++i)
            {
                vertices[i].color = m_color;
                m_vertices.append(vertices[i]);
            }

            cursorX += m_glyphWidth + m_charSpacing;
        }
    }

    sf::FloatRect BitmapTextRenderer::getLocalBounds() const
    {
        if (m_textString.empty())
            return sf::FloatRect({0, 0}, {0, 0});

        // Count visible characters (excluding newlines)
        size_t visibleChars = 0;
        size_t lines = 1;
        size_t maxCharsInLine = 0;
        size_t currentLineChars = 0;

        for (char ch : m_textString)
        {
            if (ch == '\n')
            {
                lines++;
                maxCharsInLine = std::max(maxCharsInLine, currentLineChars);
                currentLineChars = 0;
            }
            else if (ch >= 32 && ch <= 127)
            {
                visibleChars++;
                currentLineChars++;
            }
        }
        maxCharsInLine = std::max(maxCharsInLine, currentLineChars);

        float width = maxCharsInLine * (m_glyphWidth + m_charSpacing);
        if (maxCharsInLine > 0 && m_charSpacing > 0)
            width -= m_charSpacing; // Remove trailing spacing

        float height = lines * m_glyphHeight;

        return sf::FloatRect({0, 0}, {width, height});
    }

    sf::FloatRect BitmapTextRenderer::getGlobalBounds() const
    {
        sf::FloatRect localBounds = getLocalBounds();
        return sf::FloatRect({m_position.x + localBounds.position.x,
                              m_position.y + localBounds.position.y},
                             {localBounds.size.x,
                              localBounds.size.y});
    }

    void BitmapTextRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if (m_vertices.getVertexCount() == 0)
            return;

        states.texture = &s_texture;
        target.draw(m_vertices, states);
    }
}
