# UI Layout

A layout in this application represents a complete screen or view with its associated UI elements and logic.

## Overview

Define Layouts in the constructor of `GameScreen` class

## Creating a New Layout

### 1. Define Layout in `screen.hpp`

Add your layout class declaration in [`src/gui/screen.hpp`](src/gui/screen.hpp):

```cpp
class GameScreen
{
private:

    .
    .
    .

    // Layouts
    UILayout* layoutName = nullptr;

    .
    .
    .
}
```

### 2. Implement Layout in `screen.cpp`

Implement your layout class in the constructor of `GameScreen` in [`src/gui/screen.cpp`](src/gui/screen.cpp):

```cpp
engine::GameScreen::GameScreen() ...
{
    .
    .
    .

    // Layouts
    layoutName = new UILayout(1); // 1 is the id, make sure this is unique for all layouts
    
    .
    .
    .
}
```

And in the destructor

```cpp
engine::GameScreen::~GameScreen()
{
    .
    .
    .

    delete layoutName;
}
```

### 3. Switching to a Layout

Switch to any layout using:

```cpp
ChangeUILayout(layoutName);
```

where `newLayout` is `UILayout&`
