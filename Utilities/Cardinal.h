#pragma once

#include <Swap.h>
#include <ExceptionsAll.h>

namespace cardinality{

    struct W {
        constexpr explicit W(int){}
    };

    template<typename T>
    class cardinal {
        bool _is_inf;
        size_t _value{};
    public:
        explicit cardinal() : _is_inf(true) {}
        explicit cardinal(W) : _is_inf(true) {}
        //конструктор копирования
        cardinal(const cardinal& other) : _is_inf(other.is_inf()), _value(other._value) {}

        //конструкторы с передаваемым значением
        explicit cardinal(const size_t value) : _is_inf(false), _value(value) {}

        ~cardinal() = default;

        [[nodiscard]] bool is_inf() const {
            return _is_inf;
        }

        [[nodiscard]] size_t get_value() const {
            if(_is_inf) throw Exceptions::CardinalIsInf();
            return _value;
        }

        cardinal& operator=(const cardinal& other) {
            if (this == &other) return *this;
            if (other.is_inf()) {
                _is_inf = true;
            } else {
                _is_inf = false;
                _value = other._value;
            }
            return *this;
        }

        void swap(cardinal& other) noexcept {
            if (_is_inf && other.is_inf()) {}
            else if (!_is_inf && !other.is_inf()) {
                swapper::swap(_value,other._value);
            }else {
                swapper::swap(_is_inf, other._is_inf);
                swapper::swap(_value,other._value);
            }
        }

        friend bool operator==(const cardinal& left, const cardinal& right) {
            if (left._is_inf == right._is_inf) {
                if (left._is_inf) {
                    return true;
                }
                return left._value == right._value;
            }
            return false;
        }

        friend bool operator!=(const cardinal& left, const cardinal& right) {
            return !(left==right);
        }

        friend bool operator<(const cardinal& left, const cardinal& right) {
            if (left._is_inf) return false;
            if (!right._is_inf) return left._value < right._value;
            return true;
        }
        friend bool operator<=(const cardinal& left, const cardinal& right) {
            if (right._is_inf) return true;
            if (!left._is_inf) return left._value <= right._value;
            return false;
        }

        friend bool operator>(const cardinal& left, const cardinal& right) {
            if (right._is_inf) return false;
            if (!left._is_inf) return left._value > right._value;
            return true;
        }

        friend bool operator>=(const cardinal& left, const cardinal& right) {
            if (left._is_inf) return true;
            if (!right._is_inf) return left._value >= right._value;
            return false;
        }

        size_t operator*() const {
            if (!_is_inf) throw Exceptions::CardinalIsInf();
            return _value;
        }

        friend cardinal operator+(const cardinal& left,const cardinal& right) {
            if (left._is_inf || right._is_inf) {
                return cardinal();
            }
            return cardinal(left._value + right._value);
        }

        cardinal& operator+=(const cardinal& other) {
            if (!this->_is_inf) {
                if (other._is_inf) {
                    this->_is_inf = true;
                    return *this;
                }
                this->_value += other._value;
                return *this;
            }
            return *this;
        }

        friend cardinal operator*(const cardinal& left,const cardinal& right) {
            if (left._is_inf || right._is_inf) {
                return cardinal();
            }
            return cardinal(left._value * right._value);
        }

        cardinal& operator*=(const cardinal& other) {
            if (!this->_is_inf) {
                if (other._is_inf) {
                    this->_is_inf = true;
                    return *this;
                }
                this->_value *= other._value;
                return *this;
            }
            return *this;
        }

    };
} //namespace cardinal





