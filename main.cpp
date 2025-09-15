#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "String.h"

#include <string>

/*int main()
{
    std::vector<String> v;
    String s;
    while(std::cin >> s)
        v.push_back(s);

    std::sort(v.begin(), v.end(), []( const String& str1, const String& str2 ) { return str1.toLower() > str2.toLower(); });

   for(const auto& str: v)
        std::cout << str << std::endl;
   return 0;
}*/

int main()
{
    String s1 = "Hello";
    /*s1.append(",");
    s1.append(" World!");*/
    String s2;
    s2.append(s1);
    s2.append(", World!");
    s2.append(s2);
    auto s3 = s2.append(s2);

    return 0;
}