#ifndef _STRING_H_
#define _STRING_H_
#include <iostream>
#include "Exception.h"

class String;

class Iterator{
public:
    virtual void next() = 0;
    virtual void first() = 0;
    virtual bool IsEnd() const = 0;
    virtual char CurrentItem() const = 0;
};

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
    char& at(const size_t pos) const;

    String& operator+= (const String& other);
    String& operator+= (const char* other);

    friend const String operator+ (const String& left, const String& right);
    friend const String operator+ (const String& left, const char* right);
    friend const String operator+ (const char* left, const String& right);

    bool operator< (const String& other) const;
    friend bool operator== (const String& left, const String& right);
    friend bool operator== (const String& left, const char* right);
    friend bool operator!= (const String& left, const String& right);

    Iterator* createIterator() const;
    const char& Get(const size_t indx) const;
private:
    void resize(size_t new_size);
};

class StringIterator: public Iterator{
    unsigned indx {0};
    const String* ptr;
public:
    StringIterator(const String* vl_ptr): ptr(vl_ptr)
    {}
    void first() override { indx = 0; }
    void next() override { indx++; }
    bool IsEnd() const override { return indx >= ptr->size(); }
    char CurrentItem() const override
    {
        if(IsEnd())
            throw IndxOutOfRange();
        return ptr->Get(indx);
    }
};

#endif