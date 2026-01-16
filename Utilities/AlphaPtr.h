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
    HashFunc _hash = HashFunc(hashutils::MurmurHash2);
    containers::DynamicArray<Person> _people;
    containers::HashMap<std::string, Person&, HashFunc> _heap;

public:
    AlphaPtr() : _heap(_hash) {}


};