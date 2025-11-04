#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>

#include "__macros.hpp"

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

    inline void printLine(const std::string &fileName, const std::string &functionName, int lineNum, const std::string &message, const std::string &prefix = "")
    {
        using cf = printConfig;

        std::stringstream debugPrefix;
        if (cf::hasDebugPrefix())
        {
            debugPrefix << "["
                        << (cf::fileName ? fileName : "")
                        << (cf::printLineNum ? (" : " + std::to_string(lineNum)) : "")
                        << (cf::functionName ? (" @ " + functionName) : "")
                        << "] ";
        }

        std::cout << prefix << debugPrefix.str() << message << "\n";
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

#if DEBUG == 1
#define DEBUG_PRINT(message) utils::printLine(__FILE_NAME__, __func__, __LINE__, message, "* ")
#else
#define DEBUG_PRINT(message)
#endif