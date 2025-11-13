#include "Screen.hpp"
#include "UILayout.hpp"

using namespace engine;

int main()
{
    GameScreen screen;

    UILayout layoutA(1);
    UILayout layoutB(2);
    UILayout layoutC(3);

    layoutA.AddButtonElement("Layout B", {0.f, 0.f}, [&screen, &layoutB]() { //
        screen.ChangeUILayout(layoutB);
    });

    layoutB.AddButtonElement("Layout A", {0.f, 0.f}, [&screen, &layoutA]() { //
        screen.ChangeUILayout(layoutA);
    });

    screen.ChangeUILayout(layoutA);
    screen.StartLoop();

    return 0;
}
