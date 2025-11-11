#include "Screen.hpp"
#include "UILayout.hpp"

int main()
{
    using namespace engine;

    GameScreen screen;

    UILayout mainMenu;
    UILayout livingRoom;
    UILayout diningRoom;
    UILayout kitchen;
    UILayout suspectMenu;
    UILayout interrogation;
    UILayout accusation;

    // --- MAIN MENU ---
    mainMenu.AddTextElement("Main Menu", {50.f, 30.f});
    mainMenu.AddTextElement("Choose a Location:", {50.f, 80.f});

    mainMenu.AddButtonElement("Living Room", {50.f, 130.f}, [&]() { screen.ChangeUILayout(livingRoom); });
    mainMenu.AddButtonElement("Dining Room", {50.f, 180.f}, [&]() { screen.ChangeUILayout(diningRoom); });
    mainMenu.AddButtonElement("Kitchen", {50.f, 230.f}, [&]() { screen.ChangeUILayout(kitchen); });

    mainMenu.AddTextElement("Suspect Options:", {50.f, 300.f});
    mainMenu.AddButtonElement("Select Suspect", {50.f, 350.f}, [&]() { screen.ChangeUILayout(suspectMenu); });

    // --- SUSPECT MENU ---
    suspectMenu.AddTextElement("Suspect Menu", {50.f, 30.f});
    suspectMenu.AddButtonElement("Interrogate", {50.f, 100.f}, [&]() { screen.ChangeUILayout(interrogation); });
    suspectMenu.AddButtonElement("Accuse", {50.f, 150.f}, [&]() { screen.ChangeUILayout(accusation); });
    suspectMenu.AddButtonElement("Back", {50.f, 200.f}, [&]() { screen.ChangeUILayout(mainMenu); });

    // --- LIVING ROOM ---
    livingRoom.AddTextElement("Living Room", {50.f, 30.f});
    livingRoom.AddTextElement("Items to Investigate:", {50.f, 100.f});

    uint16_t brokenVaseId = livingRoom.AddTextElement("A shattered vase lies on the floor. It looks recently broken.", {300.f, 150.f});
    livingRoom.getElementById(brokenVaseId)->SetHidden(true);
    livingRoom.AddButtonElement("Broken Vase", {50.f, 150.f}, [&]() {
        livingRoom.getElementById(brokenVaseId)->SetHidden(false);
    });

    uint16_t photoFrameId = livingRoom.AddTextElement("A family photo with one face scratched out.", {300.f, 200.f});
    livingRoom.getElementById(photoFrameId)->SetHidden(true);
    livingRoom.AddButtonElement("Photo Frame", {50.f, 200.f}, [&]() {
        livingRoom.getElementById(photoFrameId)->SetHidden(false);
    });

    livingRoom.AddButtonElement("Back", {50.f, 400.f}, [&]() { screen.ChangeUILayout(mainMenu); });

    // --- DINING ROOM ---
    diningRoom.AddTextElement("Dining Room", {50.f, 30.f});
    diningRoom.AddTextElement("Items to Investigate:", {50.f, 100.f});

    uint16_t wineGlassId = diningRoom.AddTextElement("A single glass with red stains — perhaps wine, perhaps not.", {300.f, 150.f});
    diningRoom.getElementById(wineGlassId)->SetHidden(true);
    diningRoom.AddButtonElement("Wine Glass", {50.f, 150.f}, [&]() {
        diningRoom.getElementById(wineGlassId)->SetHidden(false);
    });

    uint16_t tableclothId = diningRoom.AddTextElement("The tablecloth has a hidden blood spot under a plate.", {300.f, 200.f});
    diningRoom.getElementById(tableclothId)->SetHidden(true);
    diningRoom.AddButtonElement("Tablecloth", {50.f, 200.f}, [&]() {
        diningRoom.getElementById(tableclothId)->SetHidden(false);
    });

    diningRoom.AddButtonElement("Back", {50.f, 400.f}, [&]() { screen.ChangeUILayout(mainMenu); });

    // --- KITCHEN ---
    kitchen.AddTextElement("Kitchen", {50.f, 30.f});
    kitchen.AddTextElement("Items to Investigate:", {50.f, 100.f});

    uint16_t knifeId = kitchen.AddTextElement("A sharp kitchen knife missing from the set. Found near the sink.", {300.f, 150.f});
    kitchen.getElementById(knifeId)->SetHidden(true);
    kitchen.AddButtonElement("Knife", {50.f, 150.f}, [&]() {
        kitchen.getElementById(knifeId)->SetHidden(false);
    });

    uint16_t noteId = kitchen.AddTextElement("A note that reads 'Meet me after dinner - J.'", {300.f, 200.f});
    kitchen.getElementById(noteId)->SetHidden(true);
    kitchen.AddButtonElement("Note", {50.f, 200.f}, [&]() {
        kitchen.getElementById(noteId)->SetHidden(false);
    });

    kitchen.AddButtonElement("Back", {50.f, 400.f}, [&]() { screen.ChangeUILayout(mainMenu); });

    // --- INTERROGATION ---
    interrogation.AddTextElement("Interrogation Room", {50.f, 30.f});

    uint16_t q1Id = interrogation.AddTextElement("Suspect: I was in the kitchen cleaning up after dinner.", {300.f, 100.f});
    interrogation.getElementById(q1Id)->SetHidden(true);
    interrogation.AddButtonElement("Ask about last night", {50.f, 100.f}, [&]() {
        interrogation.getElementById(q1Id)->SetHidden(false);
    });

    uint16_t q2Id = interrogation.AddTextElement("Suspect: We had a fight, but I didn’t do anything!", {300.f, 150.f});
    interrogation.getElementById(q2Id)->SetHidden(true);
    interrogation.AddButtonElement("Ask about the victim", {50.f, 150.f}, [&]() {
        interrogation.getElementById(q2Id)->SetHidden(false);
    });

    interrogation.AddButtonElement("Back", {50.f, 400.f}, [&]() { screen.ChangeUILayout(suspectMenu); });

    // --- ACCUSATION ---
    accusation.AddTextElement("Accuse Suspect", {50.f, 30.f});

    uint16_t confessionId = accusation.AddTextElement("You accuse the suspect... They break down and confess.", {300.f, 100.f});
    accusation.getElementById(confessionId)->SetHidden(true);
    accusation.AddButtonElement("Confirm Accusation", {50.f, 100.f}, [&]() {
        accusation.getElementById(confessionId)->SetHidden(false);
    });

    accusation.AddButtonElement("Back", {50.f, 200.f}, [&]() { screen.ChangeUILayout(suspectMenu); });

    // --- Start Game ---
    screen.ChangeUILayout(mainMenu);
    screen.StartLoop();

    return 0;
}
