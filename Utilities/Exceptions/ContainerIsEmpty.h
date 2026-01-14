#pragma once

#include <exception>

namespace Exceptions
{
    struct ContainerIsEmpty : public std::exception
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Conatainer is empty";
        }
    };
}
