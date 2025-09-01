#ifndef _ITERATOR_H_
#define _ITERATOR_H_
#include "Exception.h"
#include "String.h"


class Iterator{
public:
    virtual void next() = 0;
    virtual void first() = 0;
    virtual bool IsEnd() const = 0;
    virtual char CurrentItem() const = 0;
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

