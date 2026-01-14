#pragma once

#include <SmartPtr.h>

namespace swapper {
    template<typename T>
    void swap(T& obj1, T& obj2) noexcept {
        T buffer = smartptr::MoveRef(obj1);
        obj1 = smartptr::MoveRef(obj2);
        obj2 = smartptr::MoveRef(buffer);
    }
}




