#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace utils
{
    struct printConfig
    {
        static constexpr bool printLineNum = true;
        static constexpr bool functionName = true;
        static constexpr bool fileName = true;

        static inline constexpr bool hasDebugPrefix()
        {
            return printLineNum || functionName || fileName;
        }
    };

    inline void printLine(const std::string &fileName, const std::string &functionName, int lineNum, const std::string &message)
    {
        using cf = printConfig;

        std::stringstream debugPrefix;
        if (cf::hasDebugPrefix())
        {
            debugPrefix << "["
                        << (cf::fileName ? fileName : "")
                        << (cf::functionName ? (" @ " + functionName) : "")
                        << (cf::printLineNum ? (" : " + std::to_string(lineNum)) : "")
                        << "] ";
        }

        std::cout << debugPrefix.str() << message << "\n";
    }

    template <typename... Args>
    class Event
    {
        std::vector<std::function<void(Args...)>> listeners;

    public:
        void subscribe(std::function<void(Args...)> func)
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

#define PRINT(message) utils::printLine(__FILE_NAME__, __func__, __LINE__, message)