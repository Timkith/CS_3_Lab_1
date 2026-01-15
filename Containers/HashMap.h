#pragma once

#include <Pair.h>
#include <LinkedList.h>
#include <DynamicArray.h>
#include <functional>
#include <Option.h>
#include <ExceptionsAll.h>
#include <IGenerator.h>

namespace containers {
    using types::Get;

    template<typename K, typename V, class Hash = std::hash<K> >
    class HashMap : public Generamble<types::pair<K, V> > {
        using pair_t = types::pair<K, V>;
        using bucket_t = containers::LinkedList<pair_t>;
        using array_t = containers::DynamicArray<bucket_t>;

        size_t _capacity = 10;
        array_t _arr;
        Hash _hash{};

        class HashMapGenerator : public IGenerator<pair_t> {
            GeneratorT<bucket_t> _garse;
            GeneratorT<pair_t> _glist;

            void MoveToNextValid() {
                while (!_glist->HasNext() && _garse->HasNext()) {
                    _garse->Next();
                    if (_garse->HasNext()) {
                        _glist = smartptr::MoveRef(_garse->GetCurrent().GetGenerator());
                    }
                }
            }

        public:
            explicit HashMapGenerator(HashMap &map) : _garse(smartptr::MoveRef(map._arr.GetGenerator())),
                                                      _glist(smartptr::MoveRef(map._arr[0].GetGenerator())) {
                if (!_glist->HasNext()) {
                    MoveToNextValid();
                }
            }

            IGenerator<pair_t> &Next() override {
                if (!HasNext()) throw Exceptions::IndexOutOfRange();

                _glist->Next();

                if (!_glist->HasNext()) {
                    MoveToNextValid();
                }
                return *this;
            }

            const pair_t &GetCurrent() const override {
                return _glist->GetCurrent();
            }

            [[nodiscard]] bool HasNext() const override {
                return _garse->HasNext() || _glist->HasNext();
            }
        };

        using Generator = HashMap<K, V, Hash>::HashMapGenerator;


        optional::option<V &> search(bucket_t &_list, const K &k) {
            for (auto it = _list.GetGenerator(); it->HasNext(); it->Next()) {
                const auto &p = it->GetCurrent();
                if (types::Get<0>(p) == k) {
                    auto &non_const_p = const_cast<pair_t &>(p);
                    return optional::option<V &>(types::Get<1>(non_const_p));
                }
            }
            return optional::option<V &>(optional::nullopt{});
        }

    public:
        HashMap() : _arr(array_t(_capacity)) {
            for (size_t i = 0; i < _capacity; ++i)
                _arr.Append(bucket_t{});
        }

        ~HashMap() override = default;


        V &at(const K &k) {
            size_t idx = _hash(k) % _capacity;
            auto &_list = _arr[idx];
            auto found = search(_list, k);
            if (!found.has_value()) throw Exceptions::EmptyOption();
            return found.value();
        }

        V &operator[](const K &k) {
            size_t idx = _hash(k) % _capacity;
            auto &_list = _arr[idx];

            auto found = search(_list, k);
            if (found.has_value()) return found.value();

            auto &added = _list.Append(pair_t(k, V{}));
            return types::Get<1>(added);
        }

        void Add(pair_t p) {
            size_t idx = _hash(types::Get<0>(p)) % _capacity;
            _arr[idx].Append(p);
        }

        bool HasValue(const V &value) {
            for (auto it = GetGenerator(); it->HasNext(); it->Next()) {
                if (auto &p = it->GetCurrent(); types::Get<1>(p) == value) return true;
            }
            return false;
        }

        void Remove(const K &k) {
            size_t idx = _hash(k) % _capacity;
            auto &_list = _arr[idx];

            size_t _list_idx = 0;
            for (auto it = _list.GetGenerator(); it->HasNext(); it->Next()) {
                auto &p = it->GetCurrent();
                if (Get<0>(p) == k) {
                    _list.RemoveAt(_list_idx);
                    return;
                }
                _list_idx++;
            }
            throw Exceptions::IndexOutOfRange();
        }

        GeneratorT<pair_t> GetGenerator() override {
            return smartptr::MakeUnique<Generator>(*this);
        }
    };
}
