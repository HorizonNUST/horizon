# Adding UI Elements to Layouts

This guide explains how to add UI elements (buttons, text boxes, panels, etc.) to your layouts.

## Basic Element Addition

### Create and Configure Element

You can add elements to a `UILayout` after declaring it

```cpp
layoutName = new UILayout(1);

layoutName->AddTextElement("Text", {0.f, 0.f}); // explained later
```

## Common UI Elements

### Text

```cpp
layoutName->AddTextElement(text, position);
```

here `text` is `std::string` and `position` is `sf::Vector2f`, you can give position like `{0.f, 0.f}`.

Example:

```cpp
layoutName->AddTextElement("some text", {0.f, 0.f});
```

> Note that `{0.f, 0.f}` is top left corner, and `{800.f, 600.f}` is bottom right corner. Position is taken from top right corner

### Button

```cpp
layoutName->AddButtonElement(buttonText, position, lambdaForFunctionCallback);
```

here `text` is `std::string`, `position` is `sf::Vector2f`, you can give position like `{0.f, 0.f}`, and the `lambdaForFunctionCallback` is a lambda that returns nothing.

Example:

```cpp
layoutName->AddButtonElement("Sample Button", {50.f, 50.f}, [this]() { // pass in this to access class variables
    playAudioOneTime("assets/Sound/button.mp3");
    ChangeUILayout(*newLayout);
});
```

Example to toggle `TextElement`:

```cpp
uint16_t dummyTextElementId = secondLayout->AddTextElement("TEST", {0.f, 120.f}); // the function returns an `uint16_t` id associated with the element
layoutName->AddButtonElement("Sample Button", {50.f, 50.f}, [this, dummyTextElementId]() { // pass in `this` to access class variables
    playAudioOneTime("assets/Sound/button.mp3");
    engine::gui::elements::UIElement* element = layoutName->getElementById(dummyTextElementId);
    element->SetHidden(!element->IsHidden());
});
```

### Image

```cpp
layoutName->AddImageElement(imagePath, position);
```

here `imagePath` is `std::string` for the location of the image, add images in `assets` folder, `position` is `sf::Vector2f`, you can give position like `{0.f, 0.f}`.
