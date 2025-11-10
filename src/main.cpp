#include "Screen.hpp"
#include "UILayout.hpp"

int main()
{
    engine::GameScreen screen;

    engine::UILayout layoutA;
    engine::UILayout layoutB;

    screen.ChangeUILayout(layoutA);

    layoutA.AddTextElement("Layout A", sf::Vector2f{50.f, 30.f});
    layoutA.AddTextElement("Sub A", sf::Vector2f{50.f, 80.f});
    layoutA.AddImageElement("assets/image.jpeg", sf::Vector2f{400.f, 50.f});
    layoutA.AddButtonElement("Press Enter to Start", sf::Vector2f{250.f, 500.f}, [&]() { //
        screen.ChangeUILayout(layoutB);                                                 //
    });                                                                                  //

    layoutB.AddTextElement("Layout B", sf::Vector2f{50.f, 30.f});
    layoutB.AddTextElement("Sub B", sf::Vector2f{50.f, 80.f});
    layoutB.AddImageElement("assets/image.jpeg", sf::Vector2f{400.f, 50.f});
    layoutB.AddButtonElement("Press Enter to Start", sf::Vector2f{250.f, 500.f}, [&]() { //
        screen.ChangeUILayout(layoutA);                                                 //
    });                                                                                  //

    screen.StartLoop();

    return 0;
}
