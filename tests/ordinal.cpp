// #include <asrt.h>
// #include "Ordinal.h"
//
// using namespace ordinality;
//
// TEST(Ordinal, finiteAddition) {
//     ordinal a(3);
//     ordinal b(5);
//     ordinal c = a + b;
//
//     ASSERT_TRUE(c == ordinal(8));
// }
//
// TEST(Ordinnal, mainRule) {
//     ordinal one(1);
//     ordinal omega(simple_ordinal(1, 1));
//
//     ASSERT_TRUE(one + omega == omega);
//     ASSERT_FALSE(omega + one == omega);
// }
//
// TEST(Ordinal, complexSum) {
//     ordinal a; //w^3 + 2w^2 + 3
//     a += ordinal(simple_ordinal(1, 3));
//     a += ordinal(simple_ordinal(2, 2));
//     a += ordinal(3);
//
//     ordinal b;   //w^2 + 5
//     b += ordinal(simple_ordinal(1, 2));
//     b += ordinal(5);
//
//     ordinal c = a + b;
//
//     ordinal expected;
//     expected += ordinal(simple_ordinal(1, 3));
//     expected += ordinal(simple_ordinal(3, 2));
//     expected += ordinal(5);
//     ASSERT_TRUE(c == expected);
//     ASSERT_FALSE(a == b);
// }