#pragma once
#include <cstddef>
#include <type_traits>
#include <utility>

namespace smartptr
{

    template <class T>
    struct RemoveRef
    {
        using type = T;
    };
    template <class T>
    struct RemoveRef<T &>
    {
        using type = T;
    };
    template <class T>
    struct RemoveRef<T &&>
    {
        using type = T;
    };

    template <typename T>
    constexpr T&&
    PassForward(typename RemoveRef<T>::type &t) noexcept { return static_cast<T &&>(t); }

    template <typename T>
    constexpr typename std::remove_reference<T>::type &&
    MoveRef(T&& t) noexcept
    {
        return static_cast<typename RemoveRef<T>::type &&>(t);
    }

    template <class T>
    class UniquePtr
    {
        T *ptr_ = nullptr;

    public:
        UniquePtr() = default;
        UniquePtr(T *p) noexcept : ptr_(p) {}

        template <class U, class = std::enable_if_t<std::is_convertible_v<U *, T *>>>
        UniquePtr(UniquePtr<U> &&other) noexcept
            : ptr_(static_cast<T *>(other.release())) {}

        UniquePtr(const UniquePtr &) = delete;
        UniquePtr &operator=(const UniquePtr &) = delete;

        UniquePtr(UniquePtr &&other) noexcept : ptr_(other.ptr_)
        {
            other.ptr_ = nullptr;
        }
        UniquePtr &operator=(UniquePtr &&other) noexcept
        {
            if (this != &other)
            {
                reset();
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
            }

            return *this;
        }

        ~UniquePtr() { reset(); }

        T *get() const noexcept { return ptr_; }
        T &operator*() const { return *ptr_; }
        T *operator->() const { return ptr_; }
        explicit operator bool() const noexcept { return ptr_ != nullptr; }

        T *release() noexcept
        {
            T *p = ptr_;
            ptr_ = nullptr;
            return p;
        }

        void reset(T *p = nullptr) noexcept
        {
            if (ptr_ != p)
            {
                delete ptr_;
                ptr_ = p;
            }
        }
    };

    template <class T, class... Args>
    UniquePtr<T> MakeUnique(Args &&...args)
    {
        return UniquePtr<T>(new T(PassForward<Args>(args)...));
    }

    template <class Base, class Derived, class... Args>
    UniquePtr<Base> MakeUnique(std::in_place_type_t<Derived>, Args &&...args)
    {
        return UniquePtr<Base>(new Derived(PassForward<Args>(args)...));
    }

    template <class T>
    UniquePtr<T[]> MakeUnique(size_t size)
    {
        return UniquePtr<T[]>(new T[size]());
    }

} // namespace smartptr
