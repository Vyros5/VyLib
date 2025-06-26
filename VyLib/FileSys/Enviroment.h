#pragma once


#include "VyLib/Types.h"
#include "VyLib/Defines.h"
#include "VyLib/Containers.h"

namespace VyLib
{
    template <typename T, typename... Ts>
    concept OneOf = requires() 
    {
        { (std::is_same_v<T, Ts> || ...) };
    };

    template <typename T = String>
    requires OneOf<T, String, u64, i64, f64, f32>
    VYINLINE Optional<T> GetEnv(const String& env)
    {
        if (const auto val = std::getenv(env.c_str()); val)
        {
            try
            {
                if constexpr (std::is_same_v<T, String>)
                {
                    return String{ val };
                }
                else if constexpr (std::is_same_v<T, u64>)
                {
                    return std::stoul(val);
                }
                else if constexpr (std::is_same_v<T, i64>)
                {
                    return std::stol(val);
                }
                else if constexpr (std::is_same_v<T, f64>)
                {
                    return std::stod(val);
                }
                else if constexpr (std::is_same_v<T, u32>)
                {
                    return std::stof(val);
                }
            }
            catch([[maybe_unused]] const std::logic_error&)
            {
                return {};
            }
        }

        return {};
    }
}