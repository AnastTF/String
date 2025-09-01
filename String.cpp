#include "String.h"
#include <cstring>
#include <exception>

String::String(): length(0), capacity(start_length_array)
{
    str = new char[capacity];
}

String::String(const String& other): length(other.length), capacity(other.capacity)
{
    str = new char[capacity];
    strcpy(str, other.str);
}

String::String(const char* other)
{
    length = strlen(other);
    capacity = length + 1;
    str = new char[capacity];
    strcpy(str, other);
}

String::String(String&& move_other) noexcept: length(move_other.length), capacity(move_other.capacity)
{
    str = move_other.str;
    move_other.length = 0;
    move_other.capacity = 0;
    move_other.str = nullptr;
}

String::~String()
{
    delete[] str;
}

size_t String::size() const noexcept
{
    return length;
}

const char* String::data() const noexcept
{
    return str;
}

void String::resize(size_t new_size)
{
    if(new_size <= capacity)
        return;
    while (capacity < new_size)
    {
        capacity *= resize_factor;
        if(capacity >= max_length_array){
            capacity = max_length_array;
            break;
        }
    }

    char* p = new char[capacity];
    strcpy(p, str);
    delete str;
    str = p;    
}

String& String::operator= (const String& other)
{
    if(this == &other)
        return *this;
    length = other.length;
    capacity = other.capacity;
    delete[] str;
    str = new char[capacity];
    strcpy(str, other.str);
    return *this;
}

String& String::operator= (String&& other) noexcept
{
    if(this == &other)
        return *this;
    delete[] str;
    length = other.length;
    capacity = other.capacity;
    str = other.str;
    other.str = nullptr;
    other.length = 0;
    other.capacity = 0;

    return *this;
}

void String::push_back (const char c)
{
    if(length >= capacity)
        resize(capacity * resize_factor);
    if(length < capacity){
        str[length++] = c;
    }
}

void String::pop_back()
{
    if(length <= 0)
        return;

    if(length > 0)
        --length;
}

void String::clear() noexcept
{
    length = 0;
    capacity = 0;
    delete[] str;
    str = nullptr;
}

bool String::empty() const noexcept
{
    return !(length);
}

String::Item String::operator[](int indx)
{
    return String::Item(this, indx);
}

String::Item::operator char() const
{
    if(indx > current->length || indx < 0)
        throw std::out_of_range("String: at() out of range");
    return current->str[indx];
}

char String::Item::operator=(char ch) const
{
    if(indx >= max_length_array || indx < 0)
        return ch; 
 
    if(indx >= current->capacity) {
        current->resize(indx+1);
    }
 
    for(int i = current->length; i < indx; ++i)
        current->str[i] = '\0';   
 
    if(indx >= current->length)
        current->length = indx + 1; 
 
    current->str[indx] = ch;
    return ch;
}

String& String::append (const String& other)
{
    for(int i = 0; i != other.size(); ++i)
        push_back(other.str[i]);
    return *this;
}

String& String::append (const char* s)
{
    if(s == nullptr)
        throw std::logic_error("Invalid argument append");
    for(int i = 0; i != strlen(s); ++i)
        push_back(s[i]);
    return *this;
}

String& String::operator+= (const String& other)
{
    return append(other);
}

String& String::operator+= (const char* other)
{
    return append(other);
}

const String operator+ (const String& left, const String& right)
{
    String str_result;
    str_result.length = left.length + right.length;
    str_result.capacity = str_result.length + 1;
    str_result.str = new char[str_result.capacity];
    std::memcpy(str_result.str, left.data(), left.size());
    std::memcpy(str_result.str + left.size(), right.data(), right.size());
    str_result.str[str_result.length] = '\0';
    return str_result;
}

const String operator+ (const String& left, const char* right)
{
    return left + String(right);
}

const String operator+ (const char* left, const String& right)
{
    return String(left) + right;
}

bool String::operator< (const String& other) const
{
    auto cmp_len = std::min(length, other.length);
    return (strncmp(str, other.str, cmp_len) < 0);
}

bool operator== (const String& left, const String& right)
{
    auto left_sz = left.length;
    auto right_sz = right.length;
    if(left_sz == 0 && right_sz == 0)
        return true;
    if(left.str == nullptr || right.str == nullptr)
        return false;
    
    return !(strcmp(left.str, right.str));
}

bool operator== (const String& left, const char* right)
{
    return left == String(right);
}

bool operator!= (const String& left, const String& right)
{
    return !(left == right);
}