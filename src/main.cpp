#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include "String.h"

int main()
{
    std::vector<String> v;
    String s;
    while(std::cin >> s)
        v.push_back(s);

    std::sort(v.begin(), v.end(), [](const String& str1, const String& str2) 
                                    { return strcasecmp(str1.data(), str2.data()) > 0; });

    
    for(const auto& str: v)
        std::cout << str << std::endl;                       
    return 0;
}