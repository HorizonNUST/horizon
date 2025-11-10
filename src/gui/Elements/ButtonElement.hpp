#pragma once
#include <functional>

#include "utils.hpp"
#include "UIElement.hpp"
#include "GameScreenData.hpp"

namespace engine::gui::elements
{
    /// @brief Used to set the style for the button
    struct ButtonConfig
    {
        /// @brief Padding around the Text
        sf::Vector2f padding = {16.f, 8.f};

        /// @brief Color of the button backgorund
        sf::Color fillColor = sf::Color::Black;
        float outlineThickness = 2.f;
        sf::Color outlineColor = sf::Color::White;

        sf::Color fontColor = sf::Color::White;
        unsigned int fontSize = 20;
        /// @brief input `sf::Text::Style::`
        sf::Text::Style fontStyle = sf::Text::Style::Regular;
        /// @brief input `sf::Text::Style::`
        sf::Text::Style fontHoverStyle = sf::Text::Style::Underlined;
        /// @brief input `sf::Text::Style::`
        sf::Text::Style fontClickStyle = sf::Text::Style::Italic;
    };

    class ButtonElement : public UIElement
    {
    public:
        ButtonElement(const std::string &text, const sf::Vector2f &position, std::function<void()> callback = CONSTANTS::NULLFUNC, ButtonConfig config = {});

        /// @brief Set the Text Inside Button
        /// @param newText The New Text String
        inline void SetText(const std::string &newText);

        void Update(const GameScreenData &data) override;

        /// @brief Add callback for when button is clicked
        /// @param callback the callback of type `std::function<void()>` i.e a lambda that takes nothing as parameters
        void SetCallback(std::function<void()> callback);

    private:
        ButtonConfig m_config;

        sf::Font m_font;
        std::optional<sf::Text> m_text;
        sf::RectangleShape m_shape;

        bool m_pressedThisFrame = false;
        std::function<void()> m_callback;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
