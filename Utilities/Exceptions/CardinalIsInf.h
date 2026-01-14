#pragma once

#include <exception>

namespace Exceptions
{
    struct CardinalIsInf : public std::exception
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Cardinal is infinity";
        }
    };
}