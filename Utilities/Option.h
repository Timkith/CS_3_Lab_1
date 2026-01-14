#pragma once

#include <ExceptionsAll.h>
#include <type_traits>
#include <SmartPtr.h>
#include <Swap.h>

namespace optional {

    struct nullopt {
        constexpr explicit nullopt() = default;
        constexpr explicit nullopt(int) {}
    };
    template <typename T>
    class option {
        bool _has_value;
        T* _value{};
        std :: aligned_storage_t<sizeof(T), alignof(T)> _stg;
    public:
        // пустые конструкторы (с nullopt)
        option() : _has_value(false), _stg(), _value(reinterpret_cast<T*>(&_stg)) {}
        explicit option(nullopt) : _has_value(false), _stg(), _value(reinterpret_cast<T*>(&_stg)) {}

        //конструктор копирования
        option(const option& other) : _stg(), _has_value(other.has_value()), _value(reinterpret_cast<T*>(&_stg))
        {
            if (_has_value) new (_value) T(*other._value);
        }

        //move конструктор
        option(option && other)  noexcept :  _stg(), _has_value(other.has_value()),
        _value(reinterpret_cast<T*>(&_stg))
        {
            if (_has_value) new (_value) T(smartptr::MoveRef(*other._value));
        }

        //конструкторы с передаваемым значением
        explicit option(const T& value) : _stg(), _has_value(true), _value(reinterpret_cast<T*>(&_stg))
        {
            new(_value) T(value);
        }

        explicit option(const T&& value) : _stg(), _has_value(true), _value(reinterpret_cast<T*>(&_stg))
        {
            new(_value) T(smartptr::MoveRef(value));
        }
        ~option() {if (_has_value)  _value->~T();}

        option& operator=(nullopt)
        {
            if (_has_value) {
                _value->~T();
                _has_value = false;
            }
            return *this;
        }

        option& operator=(const option& other)
        {
            if (*this==other) {
                return *this;
            }
            if (other.has_value()){
                if (_has_value) {
                    *_value = *other._value;
                }
                else {
                    new (_value) T(*other._value);
                    _has_value = true;
                }
            } else if (_has_value){
                _value->~T();
                _has_value = false;
            }
            return *this;
        }

        option& operator=(option&& other) noexcept
        {
            if (other.has_value()){
                if (_has_value) {
                    *_value = smartptr::MoveRef(*other._value);
                }
                else {
                    new (_value) T(smartptr::MoveRef(*other._value));
                    _has_value = true;
                }
            } else if (_has_value){
                _value->~T();
                _has_value = false;
            }
            return *this;
        }

        void  swap (option& other) noexcept { //переписать для двух аргументов
            if (_has_value == other.has_value() && _has_value)
            {
                swapper::swap(*_value,*other._value);
            } else if (_has_value != other.has_value())
            {
                swapper::swap(_has_value, other._has_value);
                swapper::swap(*_value, *other._value);
            }

        }

        void reset() {
            if (_has_value) {
                _value->~T();
                _has_value = false;
            }
        }

        [[nodiscard]] bool has_value() const {return _has_value;}

        T get_value() {
            if(!_has_value) throw Exceptions::EmptyOption();
            return *_value;
        }

        friend bool operator==(const option& left, const option& right) //основной
        {
            return left.has_value() == right.has_value() && (!left.has_value() || *left._value == *right._value);
        }

        friend bool operator!=(const option& left, const option& right)
        {
            return !(left==right);
        }

        friend bool operator<(const option& left, const option& right)
        {
            if (!left.has_value() && right.has_value()) return true;
            if (!left.has_value() || !right.has_value()) return false;
            return *left._value < *right._value;
        }

        friend bool operator<=(const option& left, const option& right)
        {
            if (!left.has_value() && right.has_value()) return true;
            if (!left.has_value() && !right.has_value()) return true;
            if (left.has_value() && right.has_value())
                return *left._value <= *right._value;
            return false;
        }

        friend bool operator>(const option& left, const option& right)
        {
            if (left.has_value() && right.has_value())
                return *left._value > *right._value;
            return false;
        }

        friend bool operator>=(const option& left, const option& right)
        {
            if (!left.has_value() && !right.has_value()) return true;
            if (left.has_value() && right.has_value())
                return *left._value >= *right._value;
            return false;
        }

        constexpr T& operator*() {
            if (!_has_value) throw Exceptions::EmptyOption();
            return *_value;
        }

        constexpr const T&  operator*() const {
            if (!_has_value) throw Exceptions::EmptyOption();
            return *_value;
        }

        constexpr const T* operator->() const {
            if (!_has_value) throw Exceptions::EmptyOption();
            return _value;
        }

        constexpr T* operator->() {
            if (!_has_value) throw Exceptions::EmptyOption();
            return _value;
        }


        constexpr T& value() & {
            if(!has_value()) {
                throw Exceptions::EmptyOption();
            }
            return *_value;
        }

        constexpr const T& value() const & {
            if(!has_value()) {
                throw Exceptions::EmptyOption();
            }
            return *_value;
        }

        constexpr T&& value() && {
            if(!has_value()) {
                throw Exceptions::EmptyOption();
            }
            return smartptr::MoveRef(*_value);
        }
    };

    template<typename T, typename... Args>
    option<T> MakeOption(Args&&... args) {
        return option<T>(T(smartptr::MoveRef(args)...));
    }

    template<typename T>
    class option<T&> {
        T* _ptr = nullptr;
    public:
        option() = default;
        option(nullopt) : _ptr(nullptr) {}

        option(T& ref) : _ptr(&ref) {}

        bool has_value() const { return _ptr != nullptr; }

        T& value() {
            if (!_ptr) throw Exceptions::EmptyOption();
            return *_ptr;
        }

        const T& value() const {
            if (!_ptr) throw Exceptions::EmptyOption();
            return *_ptr;
        }

        T& operator*() { return value(); }
        const T& operator*() const { return value(); }

        T* operator->() { return &value(); }
        const T* operator->() const { return &value(); }
    };
}
