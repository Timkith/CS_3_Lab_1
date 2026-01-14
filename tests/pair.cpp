#include <asrt.h>
#include <Pair.h>

using namespace types;


TEST(pair, DefaultConstructor)
{
    pair<int,int> p;
    ASSERT_EQ(p.first,0);
    ASSERT_EQ(p.second,0);
}

TEST(pair, DoubleConstructor)
{
    pair<int,int> p(3,7);
    ASSERT_EQ(p.first,3);
    ASSERT_EQ(p.second,7);
}

TEST(pair, CopyAssignment)
{
    pair<int,int> a(1,2);
    pair<int,int> b;
    b = a;
    ASSERT_EQ(b.first,1);
    ASSERT_EQ(b.second,2);
}

TEST(pair, Equality)
{
    pair<int,int> a(1,2);
    pair<int,int> b(1,2);
    pair<int,int> c(2,3);

    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a == c);
}

TEST(pair, Inequality)
{
    pair<int,int> a(1,2);
    pair<int,int> b(1,2);
    pair<int,int> c(2,3);

    ASSERT_FALSE(a != b);
    ASSERT_TRUE(a != c);
}

TEST(pair, Less)
{
    pair<int,int> a(1,2);
    pair<int,int> b(1,3);
    pair<int,int> c(2,0);

    ASSERT_TRUE(a < b);
    ASSERT_TRUE(b < c);
    ASSERT_FALSE(c < a);
}

TEST(pair, LessEqual)
{
    pair<int,int> a(1,2);
    pair<int,int> b(1,2);
    pair<int,int> c(2,0);

    ASSERT_TRUE(a <= b);
    ASSERT_TRUE(a <= c);
    ASSERT_FALSE(c <= a);
}

TEST(pair, Greater)
{
    pair<int,int> a(2,1);
    pair<int,int> b(1,5);
    pair<int,int> c(2,1);

    ASSERT_TRUE(a > b);
    ASSERT_FALSE(a > c);
}

TEST(pair, GreaterEqual)
{
    pair<int,int> a(2,1);
    pair<int,int> b(2,1);
    pair<int,int> c(1,9);

    ASSERT_TRUE(a >= b);
    ASSERT_TRUE(a >= c);
    ASSERT_FALSE(c >= a);
}

TEST(pair, Swap)
{
    auto p1 = MakePair(1,2);
    auto p2 = MakePair(3,4);

    swapper::swap(p1,p2);

    ASSERT_EQ(Get<1>(p2), 2);
}

TEST(pair, MakePair)
{
    auto p = MakePair(10,20);
    ASSERT_EQ(p.first,10);
    ASSERT_EQ(p.second,20);
}

TEST(pair, SelfAssignment)
{
    pair<int,int> p(5,6);
    p = p;
    ASSERT_EQ(p.first,5);
    ASSERT_EQ(p.second,6);
}

TEST(pair, Get0Lvalue)
{
    auto p = MakePair(10, 20);
    int& a = Get<0>(p);
    ASSERT_EQ(a,10);
    a = 30;
    ASSERT_EQ(p.first,30);
}

TEST(pair, Get1Lvalue)
{
    pair<int,int> p(10,20);
    int& b = Get<1>(p);
    ASSERT_EQ(b,20);
    b = 40;
    ASSERT_EQ(p.second,40);
}

TEST(pair, Get0Rvalue)
{
    auto p = MakePair(1,2);
    int&& a = Get<0>(smartptr::MoveRef(p));
    ASSERT_EQ(a,1);
}

TEST(pair, Get1Rvalue)
{
    auto p = MakePair(3,4);
    int&& b = Get<1>(smartptr::MoveRef(p));
    ASSERT_EQ(b,4);
}
