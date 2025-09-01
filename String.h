#ifndef _STRING_H_
#define _STRING_H_
#include <iostream>

class String{
    enum {
        start_length_array = 8, // init length of string
        resize_factor = 2,      // resize factor is in order to increase capacity of string
        max_length_array = 1000,  // max length of string
    };
    char* str {nullptr};
    size_t length {0};
    size_t capacity {0};
    class Item{ 
        String* current {nullptr};
        int indx {-1};
    public:
        Item(String* obj, int indx): current(obj), indx(indx)
        {}
        operator char() const;
        char operator=(char ch) const;
    };
public:
    String();
    String(const String& other);
    String(const char* other);
    String(String&& move_other) noexcept;
    ~String();

    size_t size() const noexcept;
    void clear() noexcept;
    bool empty() const noexcept;
    const char* data() const noexcept;

    String& operator= (const String& other);
    String& operator= (String&& other) noexcept;

    void push_back (const char c);
    void pop_back();
    String& append (const String& other);
    String& append (const char* s);
    Item operator[](int indx);

    String& operator+= (const String& other);
    String& operator+= (const char* other);

    friend const String operator+ (const String& left, const String& right);
    friend const String operator+ (const String& left, const char* right);
    friend const String operator+ (const char* left, const String& right);

    bool operator< (const String& other) const;
    friend bool operator== (const String& left, const String& right);
    friend bool operator== (const String& left, const char* right);
    friend bool operator!= (const String& left, const String& right);

private:
    void resize(size_t new_size);
};

#endif