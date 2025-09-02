#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include "String.h"

int main()
{
    String s1("Hello "); // len=6 cap=7
    auto res1 = s1.size() == 6;
    auto res2 = s1.get_capacity() == 7;

    s1.push_back('m'); // len=7 cap=7
    s1.push_back('y'); // len=8 cap=14
    s1.push_back(' '); // len=9 cap=14

    auto res3 = s1.size() == 9;
    auto res4 = s1.get_capacity() == 14;

    s1.push_back('f'); // len=10 cap=14
    s1.push_back('r'); // len=11 cap=14
    s1.push_back('i'); // len=12 cap=14
    s1.push_back('e'); // len=13 cap=14
    s1.push_back('n'); // len=14 cap=14*2=28
    s1.push_back('d'); // len=15 cap=28
    s1.push_back('!'); // len=16 cap=28
    s1.push_back('!'); // len=17 cap=28

    auto res5 = s1.size() == 17;
    auto res6 = s1.get_capacity() == 28;

    auto res = s1 == "Hello my friend!!";
    return 0;
}