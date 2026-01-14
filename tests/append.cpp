#include <asrt.h>
#include <DynamicArray.h>
#include <AppendGenerator.h>

using namespace containers;
using namespace smartptr;

TEST(AppendGenerator, Empty)
{
    DynamicArray<int> emptyArray;
    auto baseGen = emptyArray.GetGenerator();
    auto appendGen = append(MoveRef(baseGen), 42);

    ASSERT_TRUE(appendGen->HasNext());
    ASSERT_EQ(appendGen->GetCurrent(), 42);

    ASSERT_NO_THROW(appendGen->Next());
    ASSERT_FALSE(appendGen->HasNext());
    ASSERT_THROW(appendGen->GetCurrent());
    ASSERT_THROW(appendGen->Next());
}

TEST(AppendGenerator, OneElemArray)
{
    DynamicArray<int> singleArray{42};
    auto appendGen = append(singleArray.GetGenerator(), 99);

    ASSERT_EQ(appendGen->GetCurrent(), 42);
    appendGen->Next();
    ASSERT_EQ(appendGen->GetCurrent(), 99);
    appendGen->Next();
    ASSERT_FALSE(appendGen->HasNext());
}

TEST(AppendGenerator, ArrayAndElems)
{
    DynamicArray<int> array{1, 2, 3};
    auto appendGen = append(array.GetGenerator(), 4);

    ASSERT_TRUE(appendGen->HasNext());
    ASSERT_EQ(appendGen->GetCurrent(), 1);

    appendGen->Next();
    ASSERT_TRUE(appendGen->HasNext());
    ASSERT_EQ(appendGen->GetCurrent(), 2);

    appendGen->Next();
    ASSERT_TRUE(appendGen->HasNext());
    ASSERT_EQ(appendGen->GetCurrent(), 3);

    appendGen->Next();
    ASSERT_TRUE(appendGen->HasNext());
    ASSERT_EQ(appendGen->GetCurrent(), 4);

    appendGen->Next();
    ASSERT_FALSE(appendGen->HasNext());
    ASSERT_THROW(appendGen->GetCurrent());
}

TEST(AppendGenerator, HasNextStaysCalm)
{
    DynamicArray<int> array{10, 20};
    auto appendGen = append(array.GetGenerator(), 30);

    ASSERT_TRUE(appendGen->HasNext());
    ASSERT_TRUE(appendGen->HasNext());
    ASSERT_TRUE(appendGen->HasNext());
    ASSERT_EQ(appendGen->GetCurrent(), 10);
}

TEST(AppendGenerator, AppendChain)
{
    DynamicArray<int> array{100};
    auto baseGen = array.GetGenerator();
    auto appendGen1 = append(MoveRef(baseGen), 200);
    auto appendGen2 = append(MoveRef(appendGen1), 300);

    ASSERT_EQ(appendGen2->GetCurrent(), 100);
    appendGen2->Next();
    ASSERT_EQ(appendGen2->GetCurrent(), 200);
    appendGen2->Next();
    ASSERT_EQ(appendGen2->GetCurrent(), 300);
    appendGen2->Next();
    ASSERT_FALSE(appendGen2->HasNext());
}