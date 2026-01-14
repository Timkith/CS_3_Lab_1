// #include <asrt.h>
// #include <LazySequence.h>
//
// template<class T>
// class Fib2Functor : public functor<T, T> {
//     T prev{};
//     T beforePrev{};
//
//     T operator()() {
//         T curr = prev + beforePrev;
//         beforePrev = prev;
//         prev = curr;
//         return curr;
//     }
// };
