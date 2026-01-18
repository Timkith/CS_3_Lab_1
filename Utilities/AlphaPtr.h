#pragma once

#include <HashMap.h>
#include <DynamicArray.h>
#include <Person.h>
#include <HashUtils.h>

template<typename K = std::string>
class AlphaPtr {
    using str = std::string;
    using HashFunc = size_t(*)(const str&);
private:
    HashFunc _hash = hashutils::MurmurHash2<const str&>;
    containers::DynamicArray<Person> _people;
    containers::HashMap<std::string, Person&, HashFunc> _heap;

    void SyncHeap() {
        for (size_t i = 0; i < _people.GetLength(); ++i) {
            _heap[_people[i].get_name()] = _people[i];
        }
    }

public:
    AlphaPtr() : _heap(_hash) {}

    void Add(Person p) {
        str name = p.get_name();

        size_t pos = 0;
        while (pos < _people.GetLength() && _people[pos].get_name() < name) {
            pos++;
        }
        _people.InsertAt(p, pos);
        SyncHeap();
    }



};