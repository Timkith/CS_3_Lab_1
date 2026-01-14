#pragma once

#include <exception>

namespace Exceptions
{
    struct EmptyOption : public std::exception
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Option is empty";
        }
    };
}
