#include <asrt.h>
#include <Cardinal.h>

using namespace cardinality;

TEST(cardinal, InvalidCompareOperator) {
    cardinal<int> infinity1(W{0});
    cardinal<int> infinity2(W{0});
    cardinal<int> little1(0);
    cardinal<int> little2(0);
    cardinal<int> big(500);

    ASSERT_FALSE(infinity1 == little1); //==
    ASSERT_TRUE(little1 == little2);
    ASSERT_FALSE(little1 == big);
    ASSERT_TRUE(infinity1 == infinity2);


    ASSERT_TRUE(infinity1 != little1); //!=
    ASSERT_FALSE(little1 != little2);
    ASSERT_TRUE(little1 != big);
    ASSERT_FALSE(infinity1 != infinity2);

    ASSERT_FALSE(infinity1 < little1); //<
    ASSERT_FALSE(little1 < little2);
    ASSERT_TRUE(little1 < big);
    ASSERT_FALSE(infinity1 < infinity2);

    ASSERT_FALSE(infinity1 <= little1); //<=
    ASSERT_TRUE(little1 <= little2);
    ASSERT_TRUE(little1 <= big);
    ASSERT_TRUE(infinity1 <= infinity2);

    ASSERT_TRUE(infinity1 > little1); //>
    ASSERT_FALSE(little1 > little2);
    ASSERT_FALSE(little1 > big);
    ASSERT_FALSE(infinity1 > infinity2);

    ASSERT_TRUE(infinity1 >= little1); //>=
    ASSERT_TRUE(little1 >= little2);
    ASSERT_FALSE(little1 >= big);
    ASSERT_TRUE(infinity1 >= infinity2);
}

TEST(Cardinal, Swap) {
    cardinal<int> infinity1;
    cardinal<int> infinity2;
    cardinal<int> infinity3;
    cardinal<int> little1(0);
    cardinal<int> little2(0);
    cardinal<int> big(35);
    little1.swap(big);
    little2.swap(infinity3);
    infinity1.swap(infinity2);
    ASSERT_EQ(infinity3.get_value(),0);
    ASSERT_EQ(little1.get_value(),35);
    ASSERT_EQ(big.get_value(), 0);
    ASSERT_TRUE(infinity1.is_inf());
    ASSERT_TRUE(infinity2.is_inf());
    ASSERT_TRUE(little2.is_inf());
}

TEST(Cardinal, ImmutableAddition) {
    cardinal<int> a(5);
    cardinal<int> b(10);
    cardinal<int> inf;

    auto r1 = a + b;
    ASSERT_FALSE(r1.is_inf());
    ASSERT_EQ(r1.get_value(), 15);

    auto r2 = a + inf;
    ASSERT_TRUE(r2.is_inf());

    auto r3 = inf + a;
    ASSERT_TRUE(r3.is_inf());

    auto r4 = inf + inf;
    ASSERT_TRUE(r4.is_inf());
}

TEST(Cardinal, ImmutableMultiplication) {
    cardinal<int> a(3);
    cardinal<int> b(4);
    cardinal<int> inf;

    auto r1 = a * b;
    ASSERT_FALSE(r1.is_inf());
    ASSERT_EQ(r1.get_value(), 12);

    auto r2 = a * inf;
    ASSERT_TRUE(r2.is_inf());

    auto r3 = inf * a;
    ASSERT_TRUE(r3.is_inf());

    auto r4 = inf * inf;
    ASSERT_TRUE(r4.is_inf());
}

TEST(Cardinal, MutableAddition) {
    cardinal<int> r(0);
    cardinal<int> a(5);
    cardinal<int> inf1;
    cardinal<int> inf2;

    r+=a;
    ASSERT_EQ(r.get_value(), 5);
    ASSERT_FALSE(r.is_inf());

    r+=inf1;
    ASSERT_TRUE(r.is_inf());

    inf1+=a;
    ASSERT_TRUE(inf1.is_inf());

    inf1+=inf2;
    ASSERT_TRUE(inf1.is_inf());
}

TEST(Cardinal, MutableMultiplication) {
    cardinal<int> r(1);
    cardinal<int> a(5);
    cardinal<int> inf1;
    cardinal<int> inf2;

    r*=a;
    ASSERT_EQ(r.get_value(), 5);
    ASSERT_FALSE(r.is_inf());

    r*=inf1;
    ASSERT_TRUE(r.is_inf());

    inf1*=a;
    ASSERT_TRUE(inf1.is_inf());

    inf1*=inf2;
    ASSERT_TRUE(inf1.is_inf());
}

