#include <asrt.h>
#include <HashMap.h>

using namespace containers;
using namespace types;


TEST(HashMap, EmptyAtThrows) {
    HashMap<int, int> map;

    ASSERT_THROW(map.at(20));
}

TEST(HashMap, OperatorInsertAndGet) {
    HashMap<int, int> map;

    map[1] = 100;
    map[2] = 200;

    ASSERT_EQ(map[1], 100);
    ASSERT_EQ(map[2], 200);
}

TEST(HashMap, OperatorCreatesDefault) {
    HashMap<int, int> map;

    int& v = map[5];
    ASSERT_EQ(v, 0);

    v = 42;
    ASSERT_EQ(map[5], 42);
}

TEST(HashMap, AddAndAt) {
    HashMap<int, int> map;

    map.Add(MakePair(3, 33));
    map.Add(MakePair(7, 77));

    ASSERT_EQ(map.at(3), 33);
    ASSERT_EQ(map.at(7), 77);
}

TEST(HashMap, HasValue) {
    HashMap<int, int> map;

    map[1] = 10;
    map[2] = 20;

    ASSERT_TRUE(map.HasValue(10));
    ASSERT_TRUE(map.HasValue(20));
    ASSERT_FALSE(map.HasValue(30));
}

TEST(HashMap, RemoveExisting) {
    HashMap<int, int> map;

    map[1] = 11;
    map[2] = 22;

    ASSERT_NO_THROW(map.Remove(1));
    ASSERT_THROW(map.at(1));

    ASSERT_EQ(map.at(2), 22);
}

TEST(HashMap, RemoveMissingThrows) {
    HashMap<int, int> map;

    ASSERT_THROW(map.Remove(100));
}

TEST(HashMap, GeneratorEmpty) {
    HashMap<int, int> map;

    auto g = map.GetGenerator();
    ASSERT_FALSE(g->HasNext());
}

TEST(HashMap, GeneratorIteratesAll) {
    HashMap<int, int> map;

    map[1] = 10;
    map[2] = 20;
    map[3] = 30;

    auto g = map.GetGenerator();

    int count = 0;
    int sum = 0;

    while (g->HasNext()) {
        auto p = g->GetCurrent();
        sum += Get<1>(p);
        count++;
        g->Next();
    }

    ASSERT_EQ(count, 3);
    ASSERT_EQ(sum, 60);
}

TEST(HashMap, GeneratorOutOfRange) {
    HashMap<int, int> map;

    map[1] = 1;

    auto g = map.GetGenerator();

    ASSERT_TRUE(g->HasNext());
    ASSERT_NO_THROW(g->GetCurrent());
    ASSERT_NO_THROW(g->Next());

    ASSERT_FALSE(g->HasNext());
    ASSERT_THROW(g->GetCurrent());
    ASSERT_THROW(g->Next());
}
