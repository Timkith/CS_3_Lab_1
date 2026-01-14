#include <asrt.h>
#include <LinkedList.h>

using namespace containers;


TEST(LinkedList, Empty) {
    LinkedList<int> list;
    ASSERT_EQ(list.GetLength(), 0);
}

TEST(LinkedList, EmptyGenerator) {
    LinkedList<int> list;
    auto g = list.GetGenerator();
    ASSERT_FALSE(g->HasNext());
    ASSERT_THROW(g->GetCurrent());
    ASSERT_THROW(g->Next());
}


TEST(LinkedList, Append) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);
    list.Append(3);

    ASSERT_EQ(list.GetLength(), 3);
    ASSERT_EQ(list.Get(0), 1);
    ASSERT_EQ(list.Get(1), 2);
    ASSERT_EQ(list.Get(2), 3);
}

TEST(LinkedList, Prepend) {
    LinkedList<int> list;
    list.Prepend(3);
    list.Prepend(2);
    list.Prepend(1);

    ASSERT_EQ(list.GetLength(), 3);
    ASSERT_EQ(list.Get(0), 1);
    ASSERT_EQ(list.Get(1), 2);
    ASSERT_EQ(list.Get(2), 3);
}


TEST(LinkedList, GetFirstAndLast) {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.Append(30);

    ASSERT_EQ(list.GetFirst(), 10);
    ASSERT_EQ(list.GetLast(), 30);
}

TEST(LinkedList, GetFirstEmpty) {
    LinkedList<int> list;
    ASSERT_THROW(list.GetFirst());
}

TEST(LinkedList, GetLastEmpty) {
    LinkedList<int> list;
    ASSERT_THROW(list.GetLast());
}


TEST(LinkedList, GetByIndex) {
    LinkedList<int> list;
    list.Append(5);
    list.Append(6);
    list.Append(7);

    ASSERT_EQ(list.Get(0), 5);
    ASSERT_EQ(list.Get(1), 6);
    ASSERT_EQ(list.Get(2), 7);
}

TEST(LinkedList, GetInvalidIndex) {
    LinkedList<int> list;
    list.Append(1);

    ASSERT_THROW(list.Get(1));
    ASSERT_THROW(list.Get(100));
}


TEST(LinkedList, InsertAtBeginning) {
    LinkedList<int> list;
    list.Append(2);
    list.Append(3);

    list.InsertAt(1, 0);

    ASSERT_EQ(list.GetLength(), 3);
    ASSERT_EQ(list.Get(0), 1);
}

TEST(LinkedList, InsertAtMiddle) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(3);

    list.InsertAt(2, 1);

    ASSERT_EQ(list.GetLength(), 3);
    ASSERT_EQ(list.Get(1), 2);
}

TEST(LinkedList, InsertAtEnd) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);

    list.InsertAt(3, 2);

    ASSERT_EQ(list.GetLength(), 3);
    ASSERT_EQ(list.GetLast(), 3);
}

TEST(LinkedList, InsertAtInvalidIndex) {
    LinkedList<int> list;
    ASSERT_THROW(list.InsertAt(1, 1));
}



TEST(LinkedList, GetSubList) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);
    list.Append(3);
    list.Append(4);

    auto* sub = list.GetSubList(1, 2);

    ASSERT_EQ(sub->GetLength(), 2);
    ASSERT_EQ(sub->Get(0), 2);
    ASSERT_EQ(sub->Get(1), 3);

    delete sub;
}

TEST(LinkedList, GetSubListInvalidIndex) {
    LinkedList<int> list;
    list.Append(1);

    ASSERT_THROW(list.GetSubList(0, 1));
    ASSERT_THROW(list.GetSubList(1, 0));
}



TEST(LinkedList, Concat) {
    LinkedList<int> a;
    a.Append(1);
    a.Append(2);

    LinkedList<int> b;
    b.Append(3);
    b.Append(4);

    a.Concat(b);

    ASSERT_EQ(a.GetLength(), 4);
    ASSERT_EQ(a.Get(0), 1);
    ASSERT_EQ(a.Get(1), 2);
    ASSERT_EQ(a.Get(2), 3);
    ASSERT_EQ(a.Get(3), 4);
}


TEST(LinkedList, Clear) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);

    list.Clear();

    ASSERT_EQ(list.GetLength(), 0);
    ASSERT_THROW(list.GetFirst());
}


TEST(LinkedList, CopyConstructor) {
    LinkedList<int> original;
    original.Append(1);
    original.Append(2);

    LinkedList<int> copy(original);

    ASSERT_EQ(copy.GetLength(), 2);
    ASSERT_EQ(copy.Get(0), 1);
    ASSERT_EQ(copy.Get(1), 2);
}


TEST(LinkedList, GeneratorTraversal) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);
    list.Append(3);

    auto g = list.GetGenerator();

    ASSERT_TRUE(g->HasNext());
    ASSERT_EQ(g->GetCurrent(), 1);

    ASSERT_NO_THROW(g->Next());
    ASSERT_TRUE(g->HasNext());
    ASSERT_EQ(g->GetCurrent(), 2);

    ASSERT_NO_THROW(g->Next());
    ASSERT_TRUE(g->HasNext());
    ASSERT_EQ(g->GetCurrent(), 3);

    ASSERT_NO_THROW(g->Next());
    ASSERT_FALSE(g->HasNext());
    ASSERT_THROW(g->GetCurrent());
    ASSERT_THROW(g->Next());
}

