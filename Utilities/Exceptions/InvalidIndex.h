#pragma once

#include <exception>

namespace Exceptions {
    class InvalidIndex: public std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override {
            return"Invalid index";
        }
    };
}
