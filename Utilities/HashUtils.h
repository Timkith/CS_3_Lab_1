#pragma once
#include <string_view>
#include <cstdint>
#include <cstring>
#include "SmartPtr.h"

namespace hashutils {

    template <typename T>
    size_t MurmurHash2(T&& input) noexcept {
        std::string_view key = smartptr::PassForward<T>(input);

        auto len = static_cast<uint32_t>(key.size());
        uint32_t h = len;
        const uint32_t m = 0x5bd1e995;
        const auto* data = reinterpret_cast<const unsigned char*>(key.data());


        for (; len >= 4; data += 4, len -= 4) {
            uint32_t k;
            std::memcpy(&k, data, 4);

            k *= m;
            k ^= k >> 24;
            k *= m;

            h *= m;
            h ^= k;
        }

        if (len > 0) {
            if (len == 3) h ^= data[2] << 16;
            if (len >= 2) h ^= data[1] << 8;
            h ^= data[0];
            h *= m;
        }

        h ^= h >> 13;
        h *= m;
        h ^= h >> 15;

        return h;
    }

}
