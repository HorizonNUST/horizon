#include "TextElement.hpp"
#include <stdexcept>

using namespace engine::gui::elements;

TextElement::TextElement(uint16_t id, const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size)
    : m_position(position)
{
    setID(id);

    // Load the bitmap font image
    if (!m_texture.loadFromFile("assets/bitmap_font.png"))
    {
        throw std::runtime_error("assets/bitmap_font.png not found");
    }

    // CRITICAL: Disable texture smoothing to prevent interpolation artifacts
    m_texture.setSmooth(false);

    // Initialize vertex array as triangles (SFML 3.0 removed Quads)
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

    // Build initial vertex array from provided text
    SetText(text);
}

void TextElement::SetText(const std::string &newText)
{
    m_textString = newText;
    m_vertices.clear();

    if (m_textString.empty())
        return;

    const unsigned int texW = m_texture.getSize().x;
    const unsigned int texH = m_texture.getSize().y;

    // Each glyph is 8x8
    const unsigned int gw = 8;
    const unsigned int gh = 8;

    // Number of glyphs per row in the source sheet
    const unsigned int cols = texW / gw;

    float cursorX = m_position.x;
    float cursorY = m_position.y;

    for (char ch : m_textString)
    {
        if (ch == '\n')
        {
            cursorX = m_position.x;
            cursorY += gh;
            continue;
        }

        unsigned char uc = static_cast<unsigned char>(ch);

        // Skip non-printable characters
        if (uc < 32 || uc > 127)
        {
            cursorX += gw;
            continue;
        }

        // Calculate atlas index (characters start at ASCII 32)
        unsigned int index = uc - 32;

        // Calculate texture coordinates
        float u = static_cast<float>((index % cols) * gw);
        float v = static_cast<float>((index / cols) * gh);

        // Create 6 vertices for 2 triangles (forming a quad)
        // Triangle 1: top-left, top-right, bottom-left
        // Triangle 2: top-right, bottom-right, bottom-left
        
        sf::Vertex vertices[6];
        
        // Triangle 1
        vertices[0].position = sf::Vector2f(cursorX, cursorY);              // Top-left
        vertices[1].position = sf::Vector2f(cursorX + gw, cursorY);         // Top-right
        vertices[2].position = sf::Vector2f(cursorX, cursorY + gh);         // Bottom-left
        
        vertices[0].texCoords = sf::Vector2f(u, v);
        vertices[1].texCoords = sf::Vector2f(u + gw, v);
        vertices[2].texCoords = sf::Vector2f(u, v + gh);
        
        // Triangle 2
        vertices[3].position = sf::Vector2f(cursorX + gw, cursorY);         // Top-right
        vertices[4].position = sf::Vector2f(cursorX + gw, cursorY + gh);    // Bottom-right
        vertices[5].position = sf::Vector2f(cursorX, cursorY + gh);         // Bottom-left
        
        vertices[3].texCoords = sf::Vector2f(u + gw, v);
        vertices[4].texCoords = sf::Vector2f(u + gw, v + gh);
        vertices[5].texCoords = sf::Vector2f(u, v + gh);

        // Set color to white (ensure no color modulation)
        for (int i = 0; i < 6; ++i)
        {
            vertices[i].color = sf::Color::White;
            m_vertices.append(vertices[i]);
        }

        cursorX += gw + m_charSpacing;
    }
}

void TextElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IsHidden())
        return;

    if (m_vertices.getVertexCount() == 0)
        return;

    // Set texture for the vertex array and draw
    states.texture = &m_texture;
    
    // Ensure no additional transformations affect texture sampling
    states.transform = sf::Transform::Identity;
    
    target.draw(m_vertices, states);
}
