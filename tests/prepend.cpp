#include <asrt.h>
#include <DynamicArray.h>
#include <PrependGenerator.h>
using namespace containers;
using namespace smartptr;





TEST(PrependGenerator, ArrayAndElems)
{

    DynamicArray<int> array{2, 3, 4};
    auto prependGen = prepend(array.GetGenerator(), 1);

    ASSERT_EQ(prependGen->GetCurrent(), 1);
    prependGen->Next();
    ASSERT_EQ(prependGen->GetCurrent(), 2);
    prependGen->Next();
    ASSERT_EQ(prependGen->GetCurrent(), 3);
    prependGen->Next();
    ASSERT_EQ(prependGen->GetCurrent(), 4);
    prependGen->Next();
    ASSERT_FALSE(prependGen->HasNext());
}