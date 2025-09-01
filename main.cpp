#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include "String.h"

int main()
{
    String* str1 = new String("hi");
    for(auto iter = str1->begin(); iter != str1->end(); iter->next())
        std::cout << iter->CurrentItem() << std::endl;

    return 0;
}