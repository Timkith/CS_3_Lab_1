#pragma once

#include <SmartPtr.h>
#include <Swap.h>


namespace types {
    template<typename T1, typename T2>
    struct pair {
        T1 first {};
        T2 second {};
        pair() = default;
        pair(T1 obj1, T2 obj2) : first(obj1), second(obj2){}

        pair& operator=(const pair& other) {
            this->first = other.first;
            this->second = other.second;

            return *this;
        }

        friend bool operator==(const pair& left, const pair& right) {
            if (left.first != right.first || left.second != right.second)
                return false;
            return true;
        }

        friend bool operator!=(const pair& left, const pair& right) {
            return !(left==right);
        }

        friend bool operator<(const pair& left, const pair& right) {
            if (left.first == right.first) {
                return left.second < right.second;
            }
            return left.first < right.first;
        }

        friend bool operator<=(const pair& left, const pair& right) {
            return left==right || left < right;
        }

        friend bool operator>(const pair& left, const pair& right) {
            if (left.first == right.first) {
                return left.second > right.second;
            }
            return left.first > right.first;
        }

        friend bool operator>=(const pair& left, const pair& right) {
            return left==right || left > right;
        }

    };


    template <typename T1, typename T2>
    pair<T1, T2> MakePair(T1&& fst, T2&& snd) {
        return pair<T1,T2>(smartptr::PassForward<T1>(fst), smartptr::PassForward<T2>(snd));
    }


    template<unsigned I, typename... T> struct TupleElement;


    template <unsigned I, typename Head, typename... Tail>
    struct TupleElement<I, Head, Tail...> : TupleElement<I - 1, Tail...> {};

    template <typename Head, typename... Tail>
    struct TupleElement<0,Head,Tail...> {
        using type = Head;
    };

    template<unsigned U, typename... T>
    using TupleElementT= typename TupleElement<U, T...>::type;

    template<unsigned U>
    struct pair_get;
    template<>
    struct pair_get<0> {

        template<typename T1,typename T2>
        static T1& Get(pair<T1,T2>& obj){return obj.first;}

        template<typename T1,typename T2>
        static const T1& Get(const pair<T1,T2>& obj) {return obj.first;}

        template<typename T1,typename T2>
        static T1&& Get(pair<T1,T2>&& obj){return smartptr::PassForward<T1>(obj.first);}

        template<typename T1,typename T2>
        static T1&& Get(const pair<T1,T2>&& obj){return smartptr::PassForward<T1>(obj.first);}
    };

    template<>
    struct pair_get<1> {

        template<typename T1,typename T2>
        static T2& Get(pair<T1,T2>& obj){return obj.second;}

        template<typename T1,typename T2>
        static const T2& Get(const pair<T1,T2>& obj){return obj.second;}

        template<typename T1,typename T2>
        static T2&& Get(pair<T1,T2>&& obj){return smartptr::PassForward<T2>(obj.second);}

        template<typename T1,typename T2>
        static T2&& Get(const pair<T1,T2>&& obj){return smartptr::PassForward<T2>(obj.second);}
    };

    template<size_t I, typename T1, typename T2>
    constexpr TupleElementT<I, T1, T2>& Get(pair<T1,T2>& obj) noexcept {return pair_get<I>::Get(obj);}

    template<size_t I, typename T1, typename T2>
    constexpr const TupleElementT<I, T1, T2>& Get(const pair<T1,T2>& obj) noexcept {return pair_get<I>::Get(obj);}

    template<size_t I, typename T1, typename T2>
    constexpr TupleElementT<I, T1, T2>&& Get(pair<T1,T2>&& obj) noexcept
    {return pair_get<I>::Get(smartptr::MoveRef(obj));}

    template<size_t I, typename T1, typename T2>
    constexpr TupleElementT<I, T1, T2>&& Get(const pair<T1,T2>&& obj) noexcept
    {return pair_get<I>::Get(smartptr::MoveRef(obj));}
}
