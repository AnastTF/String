#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "String.h"

int main()
{
    String str1 = "Hi!";
    String str2 = "How are you?";
    String str3 = "Hi!";
    String str4 = "How are you?Hi";
    auto res1 =  str1 == str2;
    auto res2 =  str1 == str3;
    auto res3 =  str2 == str4;
    return 0;
}