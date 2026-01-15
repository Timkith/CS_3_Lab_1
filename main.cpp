#include <DynamicArray.h>
#include <SmartPtr.h>
#include <iostream>
#include <AppendGenerator.h>
#include <HashMap.h>
#include <iostream>

using namespace containers;

int main() {
    HashMap<int, int> map;

    map[1] = 10;
    map[2] = 20;

    bool flag = map.HasValue(20);
    std::cout<<map[2];
    return 0;
}