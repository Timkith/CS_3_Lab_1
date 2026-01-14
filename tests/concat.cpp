#include <asrt.h>
#include <DynamicArray.h>
#include <ConcatGenerator.h>
using namespace containers;
using namespace smartptr;

TEST(ConcatGenerator, ArrayAndElems)
{

    DynamicArray<int> firstArray{1, 2, 3};
    DynamicArray<int> secondArray{4, 5, 6};

    auto firstGen = firstArray.GetGenerator();
    auto secondGen = secondArray.GetGenerator();
    auto concatGen = concat(smartptr::MoveRef(firstGen), smartptr::MoveRef(secondGen));

    ASSERT_TRUE(concatGen->HasNext());
    ASSERT_EQ(concatGen->GetCurrent(), 1);

    concatGen->Next();
    ASSERT_TRUE(concatGen->HasNext());
    ASSERT_EQ(concatGen->GetCurrent(), 2);

    concatGen->Next();
    ASSERT_TRUE(concatGen->HasNext());
    ASSERT_EQ(concatGen->GetCurrent(), 3);

    concatGen->Next();
    ASSERT_TRUE(concatGen->HasNext());
    ASSERT_EQ(concatGen->GetCurrent(), 4);

    concatGen->Next();
    ASSERT_TRUE(concatGen->HasNext());
    ASSERT_EQ(concatGen->GetCurrent(), 5);

    concatGen->Next();
    ASSERT_TRUE(concatGen->HasNext());
    ASSERT_EQ(concatGen->GetCurrent(), 6);

    concatGen->Next();
    ASSERT_FALSE(concatGen->HasNext());
    ASSERT_THROW(concatGen->GetCurrent());
    ASSERT_THROW(concatGen->Next());
}

TEST(ConcatGenerator, LeftEmpty)
{
    DynamicArray<int> emptyArray;
    DynamicArray<int> secondArray{7, 8, 9};

    auto firstGen = emptyArray.GetGenerator();
    auto secondGen = secondArray.GetGenerator();
    auto concatGen = concat(smartptr::MoveRef(firstGen), smartptr::MoveRef(secondGen));

    ASSERT_TRUE(concatGen->HasNext());
    ASSERT_EQ(concatGen->GetCurrent(), 7);

    concatGen->Next();
    ASSERT_EQ(concatGen->GetCurrent(), 8);

    concatGen->Next();
    ASSERT_EQ(concatGen->GetCurrent(), 9);

    concatGen->Next();
    ASSERT_FALSE(concatGen->HasNext());
}

TEST(ConcatGenerator, BothEmpty)
{
    DynamicArray<int> emptyArray1;
    DynamicArray<int> emptyArray2;

    auto firstGen = emptyArray1.GetGenerator();
    auto secondGen = emptyArray2.GetGenerator();
    auto concatGen = concat(smartptr::MoveRef(firstGen), smartptr::MoveRef(secondGen));

    ASSERT_FALSE(concatGen->HasNext());
    ASSERT_THROW(concatGen->GetCurrent());
}

TEST(ConcatGenerator, ConcatChain)
{
    DynamicArray<int> arr1{1, 2};
    DynamicArray<int> arr2{3, 4};
    DynamicArray<int> arr3{5, 6};

    auto gen1 = arr1.GetGenerator();
    auto gen2 = arr2.GetGenerator();
    auto gen3 = arr3.GetGenerator();

    auto concat12 = concat(smartptr::MoveRef(gen1), smartptr::MoveRef(gen2));
    auto concat123 = concat(smartptr::MoveRef(concat12), smartptr::MoveRef(gen3));


    ASSERT_EQ(concat123->GetCurrent(), 1);
    concat123->Next();
    ASSERT_EQ(concat123->GetCurrent(), 2);
    concat123->Next();
    ASSERT_EQ(concat123->GetCurrent(), 3);
    concat123->Next();
    ASSERT_EQ(concat123->GetCurrent(), 4);
    concat123->Next();
    ASSERT_EQ(concat123->GetCurrent(), 5);
    concat123->Next();
    ASSERT_EQ(concat123->GetCurrent(), 6);
    concat123->Next();
    ASSERT_FALSE(concat123->HasNext());
}