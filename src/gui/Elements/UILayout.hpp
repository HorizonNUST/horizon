#include <vector>
#include <functional>

#include "UIElement.hpp"
#include "utils.hpp"

class UILayout
{
private:
    UIElement elementA;

public:
    static Event<std::string> elementAEvent;
};