// #pragma once
//
// #include <LinkedList.h>
// #include <SmartPtr.h>
// #include <AppendGenerator.h>
//
// namespace ordinality {
//     using namespace containers;
//     using namespace smartptr;
//
//     struct simple_ordinal {
//         size_t _power{};
//         size_t _coef{};
//         simple_ordinal() = default;
//         explicit simple_ordinal(const size_t coef) : _coef(coef){}
//         simple_ordinal(const size_t coef, const size_t power) : _coef(coef), _power(power){}
//     };
//
//     class ordinal {
//         LinkedList<simple_ordinal> _arr {};
//     public:
//         ordinal() : _arr(LinkedList<simple_ordinal>()) {}
//         explicit ordinal(size_t coef)
//         {
//             if (coef > 0) {
//                 append(_arr.GetGenerator(), simple_ordinal(coef));
//             }
//         }
//         explicit ordinal(simple_ordinal term) {
//             if(term._coef > 0) {
//                 append(_arr.GetGenerator(), term);
//             }
//         }
//         ordinal(const ordinal& other)= default;
//
//         ordinal(ordinal&& other)  noexcept : _arr(MoveRef(other._arr)){}
//
//         ordinal& operator=(const ordinal& other) {
//             auto genR = other._arr.GetGenerator();
//             auto genL = this->_arr.GetGenerator();
//             this->_arr.Clear();
//
//             for(; genR->HasNext(); genR->Next()) {
//                 append(MoveRef(genL), genR->GetCurrent());
//             }
//             return *this;
//         }
//
//         bool operator==(const ordinal& other) const {
//             auto genL = _arr.GetGenerator();
//             auto genR = other._arr.GetGenerator();
//
//             while (genL->HasNext() && genR->HasNext()) {
//
//                 const auto& a = genL->GetCurrent();
//                 const auto& b = genR->GetCurrent();
//
//                 if (a._power != b._power || a._coef != b._coef)
//                     return false;
//
//                 genL->Next();
//                 genR->Next();
//             }
//             if(genL->HasNext() || genR->HasNext()) {
//                 return false;
//             }
//             return true;
//         }
//
//
//         ordinal& operator+=(const ordinal& other) {
//             auto genL = _arr.GetGenerator();
//             auto genR = other._arr.GetGenerator();
//
//             LinkedList<simple_ordinal> result;
//             auto resGen = result.GetGenerator();
//
//             if (other._arr.GetLength() == 0)
//                 return *this;
//
//             if (_arr.GetLength() == 0) {
//                 for (; genR->HasNext(); genR->Next())
//                     append(MoveRef(resGen), genR->GetCurrent());
//                 _arr = MoveRef(result);
//                 return *this;
//             }
//
//             size_t max_power = 0;
//             if (genR->HasNext())
//                 max_power = genR->GetCurrent()._power;
//
//             for (; genL->HasNext(); genL->Next()) {
//                 const auto& t = genL->GetCurrent();
//                 if (t._power > max_power) {
//                     append(MoveRef(resGen),t);
//                 } else {
//                     break;
//                 }
//             }
//             if (genL->HasNext() && genR->HasNext() && genL->GetCurrent()._power ==
//                 genR->GetCurrent()._power) {
//                 append(MoveRef(resGen), simple_ordinal(genL->GetCurrent()._coef +
//                     genR->GetCurrent()._coef, genL->GetCurrent()._power));
//                 genL->Next();
//                 genR->Next();
//             }
//
//             for (;genR->HasNext(); genR->Next()) {
//                 append(MoveRef(resGen), genR->GetCurrent());
//             }
//
//             _arr = MoveRef(result);
//             return *this;
//         }
//
//         ordinal operator+(const ordinal& other) {
//             ordinal result(*this);
//             result += other;
//             return result;
//         }
//
//     };
// }