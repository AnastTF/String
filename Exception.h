#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <iostream>
#include <string>

class IndxOutOfRange: public std::exception{
    std::string msg;
public:
    IndxOutOfRange(const char* error="IndxOutOfRange"): msg(error) {}
    const char* what() const noexcept override { return msg.data(); }
};

#endif