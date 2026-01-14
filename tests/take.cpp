#include <asrt.h>
#include <DynamicArray.h>
#include <TakeSkipGenerator.h>
using namespace containers;
using namespace smartptr;
using namespace gens;

TEST(TakeGenerator, ArrayAndElems)
{
    DynamicArray<int> array{1, 2, 3, 4, 5};
    auto baseGen = array.GetGenerator();
    auto takeGen = gens::take(std::move(baseGen), 3);

    ASSERT_TRUE(takeGen->HasNext());
    ASSERT_EQ(takeGen->GetCurrent(), 1);

    takeGen->Next();
    ASSERT_TRUE(takeGen->HasNext());
    ASSERT_EQ(takeGen->GetCurrent(), 2);

    takeGen->Next();
    ASSERT_TRUE(takeGen->HasNext());
    ASSERT_EQ(takeGen->GetCurrent(), 3);

    takeGen->Next();
    ASSERT_FALSE(takeGen->HasNext());
    ASSERT_THROW(takeGen->GetCurrent());
    ASSERT_THROW(takeGen->Next());
}