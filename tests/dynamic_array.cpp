#include <asrt.h>
#include <DynamicArray.h>

using namespace containers;


TEST(DynamicArray, Empty) {
    DynamicArray<int> arr;
    ASSERT_EQ(arr.GetLength(), 0);
}

TEST(DynamicArray, EmptyGenerator) {
    DynamicArray<int> arr;
    auto g = arr.GetGenerator();
    ASSERT_FALSE(g->HasNext());
}

TEST(DynamicArray, PushBack) {
    DynamicArray<int> arr;
    arr.Append(42);
    arr.Append(100);
    ASSERT_EQ(arr.GetLength(), 2);
    ASSERT_EQ(arr[0], 42);
    ASSERT_EQ(arr[1], 100);
}

TEST(DynamicArray, InitList) {
    DynamicArray<int> arr = {1,2,3};
    ASSERT_EQ(arr.GetLength(), 3);
    ASSERT_EQ(arr.Get(0), 1);
    ASSERT_EQ(arr.Get(1), 2);
    ASSERT_EQ(arr.Get(2), 3);
}

TEST(DynamicArray, InvalidIndex) {
    DynamicArray<int> arr = {1,2,3};
    ASSERT_NO_THROW(arr[1] = 1);
    ASSERT_THROW(arr[100] = 1);
}


TEST(DynamicArray, Generator) {
    DynamicArray<int> arr = {1,2,3};

    auto g = arr.GetGenerator();

    ASSERT_TRUE(g->HasNext());
    ASSERT_EQ(g->GetCurrent(), 1);

    ASSERT_NO_THROW(g->Next());
    
    ASSERT_TRUE(g->HasNext());
    ASSERT_EQ(g->GetCurrent(), 2);
    
    ASSERT_NO_THROW(g->Next());
    
    ASSERT_TRUE(g->HasNext());
    ASSERT_EQ(g->GetCurrent(), 3);

    ASSERT_NO_THROW(g->Next());
    ASSERT_THROW(g->GetCurrent());
    ASSERT_THROW(g->Next());

}