#pragma once
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

#include "__macros.hpp"

namespace utils
{
    inline int getRandomInt(int minInclusive, int maxInclusive)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(minInclusive, maxInclusive);
        return distrib(gen);
    }

    inline float getRandomFloat(float minInclusive, float maxInclusive)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distrib(minInclusive, maxInclusive);
        return distrib(gen);
    }

    inline bool getRandomBool()
    {
        return getRandomInt(0, 1);
    }

    inline float getRandom01()
    {
        return getRandomFloat(0, 1);
    }

    inline sf::Vector2f getRandomVector2f(float magnitude)
    {
        return {magnitude * getRandomFloat(0, 1), magnitude * getRandomFloat(0, 1)};
    }

    inline sf::Vector2i getRandomVector2i(float magnitude)
    {
        sf::Vector2f vec = getRandomVector2f(magnitude);
        return sf::Vector2i(
            static_cast<int>(vec.x),
            static_cast<int>(vec.y));
    }

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

namespace CONSTANTS
{
    /// @brief For Empty Functions etc.
    constexpr static inline void (*NULLFUNC)() = []() {};
}

#define PRINT(message) utils::printLine(__FILE_NAME__, __func__, __LINE__, message)

#if DEBUG == 1
#define DEBUG_PRINT(message) utils::printLine(__FILE_NAME__, __func__, __LINE__, message, "* ")
#else
#define DEBUG_PRINT(message)
#endif