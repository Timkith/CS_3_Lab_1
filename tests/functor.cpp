#include <asrt.h>

#include <FunctorGenerator.h>
#include <Fib2Functor.h>
#include <Fib3Functor.h>

using namespace gens;
using namespace functors;


TEST(FunctorGenerator, Fib2Sequence)
{
    Fib2Functor<int> fib(1, 1);
    FunctorGenerator<int> gen(fib);

    ASSERT_EQ(gen.GetCurrent(), 0);

    gen.Next();
    ASSERT_EQ(gen.GetCurrent(), 2);

    gen.Next();
    ASSERT_EQ(gen.GetCurrent(), 3);

    gen.Next();
    ASSERT_EQ(gen.GetCurrent(), 5);

    gen.Next();
    ASSERT_EQ(gen.GetCurrent(), 8);
}


TEST(FunctorGenerator, Fib3Sequence)
{
    Fib3Functor<int> fib(1, 1, 1);
    FunctorGenerator<int> gen(fib);

    ASSERT_EQ(gen.GetCurrent(), 0);

    gen.Next();
    ASSERT_EQ(gen.GetCurrent(), 3);

    gen.Next();
    ASSERT_EQ(gen.GetCurrent(), 5);

    gen.Next();
    ASSERT_EQ(gen.GetCurrent(), 9);

    gen.Next();
    ASSERT_EQ(gen.GetCurrent(), 17);
}


TEST(FunctorGenerator, HasNextAlwaysTrue)
{
    Fib2Functor<int> fib(0, 1);
    FunctorGenerator<int> gen(fib);

    ASSERT_TRUE(gen.HasNext());
    gen.Next();
    ASSERT_TRUE(gen.HasNext());
    gen.Next();
    ASSERT_TRUE(gen.HasNext());
    gen.Next();
    ASSERT_TRUE(gen.HasNext());
    gen.Next();
    ASSERT_TRUE(gen.HasNext());

    for(size_t i = 0; i < 150; i++) {
        gen.Next();
    }
    ASSERT_TRUE(gen.HasNext());
}


TEST(FunctorGenerator, NextReturnsSelf)
{
    Fib2Functor<int> fib(1, 1);
    FunctorGenerator<int> gen(fib);

    IGenerator<int>& ref = gen.Next();
    ASSERT_TRUE(&ref == &gen);
}


TEST(FunctorGenerator, IndependentGenerators)
{
    Fib2Functor<int> fib1(1, 1);
    Fib2Functor<int> fib2(1, 1);

    FunctorGenerator<int> gen1(fib1);
    FunctorGenerator<int> gen2(fib2);

    gen1.Next();
    gen1.Next();

    gen2.Next();

    ASSERT_EQ(gen1.GetCurrent(), 3);
    ASSERT_EQ(gen2.GetCurrent(), 2);
}
