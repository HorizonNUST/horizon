#include <functional>
#include <vector>

namespace utils
{
    template <typename... Args>
    class Event
    {
        std::vector<std::function<void(Args...)>> listeners;

    public:
        void subscribe(std::function<void(Args)> func)
        {
            listeners.push_back(func);
        }

        void trigger(Args... args)
        {
            for (auto &f : listeners)
                f(args...);
        }
    };

}