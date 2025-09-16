#include <iostream>
#include <algorithm>
#include <vector>
#include "String.h"
#include <cstring>

int main()
{
    std::vector<String> v;
    String s;
    while(std::cin >> s)
        v.push_back(s);

    std::sort(v.begin(), v.end(), []( const String& str1, const String& str2 ) { return str1.toLower() > str2.toLower(); });

   for(const auto& str: v)
        std::cout << str << std::endl;
   return 0;
}

