#pragma once

#include <exception>

namespace Exceptions
{
    struct InvalidOperator : std::exception
    {
        [[nodiscard]] const char* what() const noexcept override
        {
            return "Invalid operator";
        }
    };
}
