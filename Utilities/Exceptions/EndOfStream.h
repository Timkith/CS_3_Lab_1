#pragma once

#include <exception>

namespace Exception {
    class EndOfStreamException: public std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override {
            return "Stream was closed";
        }
    };
}

