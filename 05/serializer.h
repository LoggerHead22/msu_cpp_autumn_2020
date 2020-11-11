#pragma once
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cassert>
using namespace std;

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
	
private:
    static constexpr char Separator = ' ';
    ostream *out_;
	
public:
    explicit Serializer(std::ostream& out)
        : out_(&out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        process(args...);
        return Error::NoError;
    }
    
private:

    void process(uint64_t value)
    {
        *out_ << value;
        *out_ << Separator;
    }
    
    void process(bool value)
    {
        if(value){
            *out_ << "true";
        }else{
            *out_ << "false";
        }
        *out_ << Separator;
    }
    
    template <class T, class... ArgsT>
    Error process(T arg, ArgsT... args)
    {
        process(arg);
        process(forward<ArgsT>(args)...);
        return Error::NoError;
    }

};