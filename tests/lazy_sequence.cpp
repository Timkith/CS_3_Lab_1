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
TEST(LazySequence, LazyGetAndCaching)
{
    DynamicArray<int> array{10, 20, 30, 40, 50};
    LazySequence<int> seq(array);

    ASSERT_EQ(seq.Get(2), 30);
    ASSERT_EQ(seq.Get(0), 10);
    ASSERT_EQ(seq.Get(1), 20);

    ASSERT_THROW(seq.Get(10));
}

TEST(LazySequence, InfiniteFibonacci)
{
    functors::Fib2Functor<int> fibFunc(0, 1);
    auto fibGen = gens::functor<int>(fibFunc);
    LazySequence<int> seq(MoveRef(fibGen));

    ASSERT_TRUE(seq.GetLength().is_inf());

    ASSERT_EQ(seq.Get(0), 1);
    ASSERT_EQ(seq.Get(1), 2);
    ASSERT_EQ(seq.Get(2), 3);
    ASSERT_EQ(seq.Get(3), 5);

    ASSERT_THROW(seq.GetLast());
}

TEST(LazySequence, ConcatInfCheck)
{
    DynamicArray<int> arr{1, 2, 3};
    LazySequence<int> finite(arr);

    functors::Fib2Functor<int> fib(0, 1);
    LazySequence<int> infinite(gens::functor<int>(fib));

    auto res = finite.Concat(MoveRef(infinite));

    ASSERT_TRUE(res.GetLength().is_inf());

    ASSERT_EQ(res.Get(2), 3);
    ASSERT_EQ(res.Get(3), 1);
}

TEST(LazySequence, GetLastFiniteFix)
{
    DynamicArray<int> array{100, 200, 300};
    LazySequence<int> seq(array);

    ASSERT_EQ(seq.GetLast(), 300);

    ASSERT_FALSE(seq.GetLength().is_inf());
    ASSERT_EQ(seq.GetLength().get_value(), 3);
}

TEST(LazySequence, MovePreservesCache)
{
    DynamicArray<int> array{1, 2, 3, 4, 5};
    LazySequence<int> seq1(array);

    ASSERT_EQ(seq1.Get(2), 3);

    LazySequence<int> seq2(MoveRef(seq1));

    ASSERT_EQ(seq2.Get(0), 1);
    ASSERT_EQ(seq2.Get(1), 2);
    ASSERT_EQ(seq2.Get(2), 3);

    ASSERT_EQ(seq2.Get(3), 4);
}

TEST(LazySequence, LazyChainComplexity)
{
    functors::Fib2Functor<int> fib(0, 1);
    LazySequence<int> seq(gens::functor<int>(fib));

    auto sub = seq.GetSubSequence(2, 4);
    
    ASSERT_EQ(sub.Get(0), 3);
    ASSERT_EQ(sub.Get(1), 5);
    ASSERT_EQ(sub.Get(2), 8);
    ASSERT_THROW(sub.Get(3));
}