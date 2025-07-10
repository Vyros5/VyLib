#pragma once

#include <sstream>
#include <algorithm>
#include <iterator>

#include "VyLib/Types/StringTypes.h"

namespace Vy::StringUtils
{
    [[nodiscard]] String Join(const auto& values, cstring separator) 
    {
        if (values.empty()) 
        {
            return "";
        }

        using T          = std::decay_t<decltype(values)>;
        using value_type = T::value_type;

        std::ostringstream oss;
        std::copy(
            values.cbegin(), 
            values.cend() - 1,
            std::ostream_iterator<value_type>(oss, separator)
        );

        oss << *values.crbegin();
        return oss.str();
    }
}