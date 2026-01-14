#pragma once

#include <exception>

namespace Exceptions {
    class InvalidNewSize: public std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override {
            return "Invalid new size";
        }
    };
}
