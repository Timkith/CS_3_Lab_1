#pragma once

#include <exception>

namespace Exceptions
{
    struct IndexOutOfRange : std::exception
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Index out of range";
        }
    };
}
