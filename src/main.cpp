#include "Screen.hpp"
#include "UILayout.hpp"

using namespace engine;

UILayout setupLayoutA(GameScreen &screen, UILayout &layoutB);
UILayout setupLayoutB(GameScreen &screen, UILayout &layoutA);

int main()
{
    GameScreen screen;

    UILayout layoutA(1);
    UILayout layoutB(2);

    layoutA = setupLayoutA(screen, layoutB);
    layoutB = setupLayoutB(screen, layoutA);

    layoutA.AddButtonElement("Layout B", {0.f, 0.f}, [&screen, &layoutB]() { //
        screen.ChangeUILayout(layoutB);
    });

    auto layoutBElemID = layoutB.AddTextElement("TEST", {0.f, 120.f});
    layoutB.getElementById(layoutBElemID)->SetHidden(true);
    layoutB.AddButtonElement("Show Element", {0.f, 60.f}, [&layoutB, &layoutBElemID]() { //
        layoutB.getElementById(layoutBElemID)->SetHidden(false);
    });

    layoutB.AddButtonElement("Layout A", {0.f, 0.f}, [&screen, &layoutA]() { //
        screen.ChangeUILayout(layoutA);
    });

    screen.ChangeUILayout(layoutA);
    screen.StartLoop();

    return 0;
}

UILayout setupLayoutA(GameScreen &screen, UILayout &layoutB)
{
    UILayout layoutA(1);

    layoutA.AddButtonElement("Layout B", {0.f, 0.f}, [&screen, &layoutB]() { //
        screen.ChangeUILayout(layoutB);
    });

    return layoutA;
}

UILayout setupLayoutB(GameScreen &screen, UILayout &layoutA)
{
    UILayout layoutB(2);

    auto layoutBElemID = layoutB.AddTextElement("TEST", {0.f, 120.f});
    layoutB.getElementById(layoutBElemID)->SetHidden(true);
    layoutB.AddButtonElement("Show Element", {0.f, 60.f}, [&layoutB, &layoutBElemID]() { //
        layoutB.getElementById(layoutBElemID)->SetHidden(false);
    });

    layoutB.AddButtonElement("Layout A", {0.f, 0.f}, [&screen, &layoutA]() { //
        screen.ChangeUILayout(layoutA);
    });

    return layoutB;
}
