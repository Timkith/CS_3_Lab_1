#pragma once

#include <string>
#include <utility>
#include <SmartPtr.h>

struct Person {
    using str = std::string;
    str _name{};
    str _dob{};
    str _phone{};
    str _work{};
public:
    explicit Person(str name) : _name(smartptr::MoveRef(name)){}
    
    Person(str name,str dob) :
    _name(smartptr::MoveRef(name)), _dob(smartptr::MoveRef(dob)){}
    
    Person(str name,str dob,str phone) :
    _name(smartptr::MoveRef(name)), _dob(smartptr::MoveRef(dob)),
    _phone(smartptr::MoveRef(phone)){}
    
    Person(str name,str dob,str phone,str work) :
    _name(smartptr::MoveRef(name)), _dob(smartptr::MoveRef(dob)),
    _phone(smartptr::MoveRef(phone)), _work(smartptr::MoveRef(work)){}

    str get_name() {
        return _name;
    }

    str get_dob() {
        return _dob;
    }

    str get_phone() {
        return _phone;
    }

    str get_work() {
        return _work;
    }
};