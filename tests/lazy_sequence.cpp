#include <asrt.h>
#include <DynamicArray.h>
#include <LazySequence.h>
#include <Fib2Functor.h>
#include <Fib3Functor.h>
#include <FunctorGenerator.h>

using namespace containers;
using namespace smartptr;
using namespace lazy;

TEST(LazySequence, BasicCreationAndFirst)
{
    DynamicArray<int> array{10, 20, 30};
    LazySequence<int> seq(array);

    auto g = seq.GetGenerator();
    ASSERT_EQ(g->GetCurrent(), 10);
}

TEST(LazySequence, AppendAndPrependChain)
{
    DynamicArray<int> array{10};
    LazySequence<int> seq(array);

    auto result = seq.Prepend(5).Append(15);
    auto g = result.GetGenerator();

    ASSERT_EQ(g->GetCurrent(), 5);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 10);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 15);
    g->Next();
    ASSERT_FALSE(g->HasNext());
}

TEST(LazySequence, GetSubSequence)
{
    DynamicArray<int> array{1, 2, 3, 4, 5};
    LazySequence<int> seq(array);

    auto sub = seq.GetSubSequence(1, 3);
    auto g = sub.GetGenerator();

    ASSERT_EQ(g->GetCurrent(), 2);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 3);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 4);
    g->Next();
    ASSERT_FALSE(g->HasNext());
}

TEST(LazySequence, ConcatTest)
{
    DynamicArray<int> arr1{1, 2};
    DynamicArray<int> arr2{3, 4};

    LazySequence<int> seq1(arr1);
    LazySequence<int> seq2(arr2);

    auto res = seq1.Concat(MoveRef(seq2));
    auto g = res.GetGenerator();

    ASSERT_EQ(g->GetCurrent(), 1);
    g->Next();
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 3);
}

TEST(LazySequence, MoveSemanticsTest)
{
    DynamicArray<int> array{100};
    LazySequence<int> seq1(array);
    LazySequence<int> seq2(MoveRef(seq1));

    auto g2 = seq2.GetGenerator();
    ASSERT_TRUE(g2);
    ASSERT_EQ(g2->GetCurrent(), 100);

    auto g1 = seq1.GetGenerator();
    ASSERT_FALSE(g1);
}

TEST(LazySequence, ComplexChain)
{
    DynamicArray<int> base{10, 20};
    LazySequence<int> seq(base);

    auto res = seq.Prepend(5).Append(25).GetSubSequence(1, 2);

    auto g = res.GetGenerator();
    ASSERT_EQ(g->GetCurrent(), 10);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 20);
    g->Next();
    ASSERT_FALSE(g->HasNext());
}

TEST(LazySequence, Fibonacci2Test)
{
    functors::Fib2Functor<int> fibFunc(0, 1);
    auto gen = gens::functor<int>(fibFunc);
    LazySequence<int> seq(smartptr::MoveRef(gen));

    auto g = seq.GetGenerator();

    ASSERT_EQ(g->GetCurrent(), 0);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 1);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 2);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 3);
    g->Next();
    ASSERT_EQ(g->GetCurrent(), 5);
}

TEST(LazySequence, Fibonacci3TestWithSubSequence)
{
    functors::Fib3Functor<int> fib3(0, 0, 1);
    auto gen = gens::functor<int>(fib3);
    LazySequence<int> seq(smartptr::MoveRef(gen));

    auto sub = seq.GetSubSequence(3, 5);
    auto g = sub.GetGenerator();

    ASSERT_TRUE(g->HasNext());
}

TEST(LazySequence, InfiniteAppendTest)
{
    functors::Fib2Functor<int> fibFunc(0, 1);
    LazySequence<int> seq(smartptr::MoveRef(gens::functor<int>(fibFunc)));

    auto appended = seq.Append(999);

    auto g = appended.GetGenerator();
    ASSERT_EQ(g->GetCurrent(), 0);
    ASSERT_TRUE(g->HasNext());
}

TEST(LazySequence, FunctorHasNextAlwaysTrue)
{
    functors::Fib2Functor<int> fib(1, 1);
    auto gen = gens::functor<int>(fib);
    ASSERT_TRUE(gen->HasNext());
    gen->Next();
    ASSERT_TRUE(gen->HasNext());
}
