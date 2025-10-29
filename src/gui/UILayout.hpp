#include <vector>
#include <functional>

#include "UIElement.hpp"
#include "utils.hpp"

namespace engine
{
    class UILayout
    {
    private:
        gui::elements::UIElement elementA;

    public:
        static utils::Event<std::string> elementAEvent;
    };
}