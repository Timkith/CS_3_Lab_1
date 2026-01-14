#include <asrt.h>
#include <Option.h>

using namespace optional;

TEST(Option, InvalidOperator )
{
    option<int> nullOption1;
    option<int> nullOption2;
    option little1(0);
    option little2(0);
    option big(35);

    ASSERT_FALSE(nullOption1 == little1); //==
    ASSERT_TRUE(little1 == little2);
    ASSERT_FALSE(little1 == big);
    ASSERT_TRUE(nullOption1 == nullOption2);


    ASSERT_TRUE(nullOption1 != little1); //!=
    ASSERT_FALSE(little1 != little2);
    ASSERT_TRUE(little1 != big);
    ASSERT_FALSE(nullOption1 != nullOption2);

    ASSERT_TRUE(nullOption1 < little1); //<
    ASSERT_FALSE(little1 < little2);
    ASSERT_TRUE(little1 < big);
    ASSERT_FALSE(nullOption1 < nullOption2);

    ASSERT_TRUE(nullOption1 <= little1); //<=
    ASSERT_TRUE(little1 <= little2);
    ASSERT_TRUE(little1 <= big);
    ASSERT_TRUE(nullOption1 <= nullOption2);

    ASSERT_FALSE(nullOption1 > little1); //>
    ASSERT_FALSE(little1 > little2);
    ASSERT_FALSE(little1 > big);
    ASSERT_FALSE(nullOption1 > nullOption2);

    ASSERT_FALSE(nullOption1 >= little1); //>=
    ASSERT_TRUE(little1 >= little2);
    ASSERT_FALSE(little1 >= big);
    ASSERT_TRUE(nullOption1 >= nullOption2);
}

TEST(Option, Swap) {
    option<int> nullOption1;
    option<int> nullOption2;
    option<int> nullOption3;
    option little1(0);
    option little2(0);
    option big(35);
    little1.swap(big);
    little2.swap(nullOption3);
    nullOption1.swap(nullOption2);
    ASSERT_EQ(nullOption3.get_value(),0);
    ASSERT_EQ(little1.get_value(),35);
    ASSERT_EQ(big.get_value(), 0);
    ASSERT_FALSE(nullOption1.has_value());
    ASSERT_FALSE(nullOption2.has_value());
    ASSERT_FALSE(little2.has_value());
}

TEST(Option, MakeOption) {
    auto opt1 = MakeOption<int>(10);
    ASSERT_TRUE(opt1.has_value());
    ASSERT_EQ(opt1.get_value(), 10);

    auto opt2 = MakeOption<int>(-5);
    ASSERT_TRUE(opt2.has_value());
    ASSERT_EQ(opt2.get_value(), -5);
}

TEST(Option, DereferenceAndReset) {
    option<int> opt(42);

    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(*opt, 42);

    opt.reset();
    ASSERT_FALSE(opt.has_value());
}

TEST(Option, CopyAndMove) {
    option<int> a(7);
    option<int> b(a);

    ASSERT_TRUE(b.has_value());
    ASSERT_EQ(b.get_value(), 7);

    option<int> c(smartptr::MoveRef(a));
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.get_value(), 7);
}

TEST(Option, AssignOp) {
    option<int> a(7);
    option<int> b(1);

    b = a;

    ASSERT_TRUE(a == b);
}


