#pragma once

#include <exception>

namespace Exceptions
{
    struct LazySequenceIsInf : public std::exception
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Lazy Sequence is infinity";
        }
    };
}