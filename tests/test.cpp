#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "String.cpp"
#include <cstring>

TEST(TestGroupName, test_default_constructor){
    String s;
    ASSERT_TRUE(s.size() == 0);
    ASSERT_TRUE(s.get_capacity() == 8);
}

TEST(TestGroupName, test_cstr_constructor){
    char str[15] {"Hello, World!"};
    ASSERT_TRUE(String(str) == str);
}

TEST(TestGroupName, test_copy_constructor){
    String s1("Hello");
    String s2(s1);
    ASSERT_TRUE(s1 == s2);
}

TEST(TestGroupName, test_move_constructor){
    String s1("Test");
    String s2(std::move(s1));
    ASSERT_TRUE(s1.empty());
    ASSERT_TRUE(s2 == "Test");
}

TEST(TestGroupName, test_eq_operator)
{
    String s1 = "Test";
    String s2 = s1;
    ASSERT_TRUE(s1 == s2);

    String s3(std::move(s1));
    s1 = s3;
    ASSERT_TRUE(s1 == s3);
}

TEST(TestGroupName, test_plus_operator){
    String s1 = "Hello ";
    String s2 = "World!";
    String s3 = s1 + s2;
    ASSERT_TRUE(s3 == "Hello World!");

    String s4 = "Hello ";
    const char* cstr = "World!";

    String s5 = s4 + cstr;
    ASSERT_TRUE(s5 == "Hello World!");
    ASSERT_TRUE(s5.size() == 12);

    String s6 = cstr + s4;
    ASSERT_TRUE(s6  == "World!Hello ");
}

TEST(TestGroupName, test_plus_operator_2){
    char str1[10] {"Hello"};
    char str2[10] {", World!"};
    ASSERT_TRUE(String(str1) + str2 == "Hello, World!");
}

TEST(TestGroupName, test_plus_operator_3){
    char str1[15] {"Hello, World!"};
    char str2[15] {" Hello, World"};
    ASSERT_TRUE(str1 + String(str2) == "Hello, World! Hello, World");
}

TEST(TestGroupName, test_plusEq_operator){
    String str;
    char str1[15] {"Hello, World!"};
    str += str1;
    ASSERT_TRUE(str == str1);
}

TEST(TestGroupName, test_plusEq_operator_2){
    String s1 = "Hello ";
    String s2 = "World";
    s1 += s2;
    ASSERT_TRUE(s1 == "Hello World");

    const char* cstr = "!!!!";
    s1 += cstr;
    ASSERT_TRUE(s1 == "Hello World!!!!");
}

TEST(TestGroupName, test_plusEq_operator_3){
    String s1 = "Hello ";
    String s2 = "World";
    s1 += s2;
    ASSERT_TRUE(s1 == "Hello World");
}

TEST(TestGroupName, test_plusEq_operator_4){
    String s1 = "Hello ";
    s1 += s1;
    ASSERT_TRUE(s1 == "Hello Hello ");
}

TEST(TestGroupName, test_push_back){
    String s1("Hello "); // len=6 cap=7

    ASSERT_TRUE(s1.size() == 6);
    ASSERT_TRUE(s1.get_capacity() == 7);

    s1.push_back('m'); // len=7 cap=14
    s1.push_back('y'); // len=8 cap=14
    s1.push_back(' '); // len=9 cap=14

    ASSERT_TRUE(s1.size() == 9);
    ASSERT_TRUE(s1.get_capacity() == 14);

    s1.push_back('f'); // len=10 cap=14
    s1.push_back('r'); // len=11 cap=14
    s1.push_back('i'); // len=12 cap=14
    s1.push_back('e'); // len=13 cap=14
    s1.push_back('n'); // len=14 cap=14*2=28
    s1.push_back('d'); // len=15 cap=28
    s1.push_back('!'); // len=16 cap=28
    s1.push_back('!'); // len=17 cap=28

    ASSERT_TRUE(s1.size() == 17);
    ASSERT_TRUE(s1.get_capacity() == 28);
    ASSERT_TRUE(s1 == "Hello my friend!!");
}

TEST(TestGroupName, test_append){
    String str("В 1878 году я окончил Лондонский университет, получив звание врача, и сразу же отправился в Нетли, где прошел специальный курс для военных хирургов. ");
    str.append("После окончания занятий я был назначен ассистентом хирурга в Пятый Нортумберлендский стрелковый полк. В то время полк стоял в Индии, и не успел я до него добраться, как вспыхнула вторая война с Афганистаном. Высадившись в Бомбее, я узнал, что мой полк форсировал перевал и продвинулся далеко в глубь неприятельской территории. ");
    ASSERT_TRUE(str == "В 1878 году я окончил Лондонский университет, получив звание врача, и сразу же отправился в Нетли, где прошел специальный курс для военных хирургов. После окончания занятий я был назначен ассистентом хирурга в Пятый Нортумберлендский стрелковый полк. В то время полк стоял в Индии, и не успел я до него добраться, как вспыхнула вторая война с Афганистаном. Высадившись в Бомбее, я узнал, что мой полк форсировал перевал и продвинулся далеко в глубь неприятельской территории. ");
}

TEST(TestGroupName, test_append2){
    String str("Hello, world!");
    str.append(str);
    ASSERT_TRUE(str == "Hello, world!Hello, world!");
}

TEST(TestGroupName, test_append3){
    String str("Hello, world!"); 
    auto str_res = str.append(str);
    ASSERT_TRUE(str_res == "Hello, world!Hello, world!");
}

TEST(TestGroupName, test_append4){
    String str; 
    str.append("On the very day that i had come to this conclusion");
    str.append(str);
    ASSERT_TRUE(str == "On the very day that i had come to this conclusionOn the very day that i had come to this conclusion");
}


TEST(TestGroupName, test_sq_brackets1){
    String str("On the very day that i had come to this conclusion, I was standing at the Criterion Bar, when someone tapped me on the shoulder, and turning round I recognized young Stamford, who had been a dresser under me at Bart's. ");
    str[21] = 'I';
    ASSERT_TRUE(str == "On the very day that I had come to this conclusion, I was standing at the Criterion Bar, when someone tapped me on the shoulder, and turning round I recognized young Stamford, who had been a dresser under me at Bart's. ");
}

TEST(TestGroupName, test_sq_brackets2){
    String str("On the very day that I had come to this conclusion, I was standing at the Criterion Bar, when someone tapped me on the shoulder, and turning round I recognized young Stamford, who had been a dresser under me at Bart's. ");
    ASSERT_TRUE(str[10] == 'y' && str[17] == 'h' && str[50] == ',');
}

TEST(TestGroupName, test_sq_brackets3){
    String str("hello, world?");
    str[0] = 'H';
    str[str.size() - 1] = '!';
    ASSERT_TRUE(str == "Hello, world!");
}

TEST(TestGroupName, test_sq_brackets4){
    const String str("hello, world?");
    ASSERT_TRUE(str[2] == 'l' && str[5] == ',');
}

TEST(TestGroupName, test_clear){
    String s("IN the year 1878 I took my degree of Doctor of Medicine of the University of London, and proceeded to Netley to go through the course prescribed for surgeons in the army. Having completed my studies there, I was duly attached to the Fifth Northumberland Fusiliers as Assistant Surgeon. ");
    s.clear();
    ASSERT_TRUE(s.size() == 0);
    ASSERT_TRUE(s.get_capacity() == 0);
    ASSERT_TRUE(s.data() == nullptr);
}

TEST(TestGroupName, test_at){
    String s("Hello");
    ASSERT_TRUE(s.at(0) == 'H');

    ASSERT_TRUE(s.at(4) == 'o');
    ASSERT_TRUE(s.at(5) == '\0');
}

TEST(TestGroupName, test_toLower){
    String s("HelLo, WorlD");
    ASSERT_EQ(s.toLower(), "hello, world");
}

TEST(TestGroupName, test_iterator1){
    String s("HelLo, WorlD");
    size_t cnt = 0;
    for( auto iter = s.begin(); iter != s.end(); ++iter)
        cnt++;
    
    ASSERT_TRUE(cnt == s.size());
}

TEST(TestGroupName, test_iterator2){
    String s("HelLo, WorlD");
    size_t cnt = 0;
    for( auto iter = s.begin(); iter != s.end(); ++iter)
        *iter = std::toupper(*iter);
    
    ASSERT_TRUE(s == "HELLO, WORLD");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}