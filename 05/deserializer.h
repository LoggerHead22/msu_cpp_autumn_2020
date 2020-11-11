#pragma once
#include "serializer.h"

class Deserializer
{
private:
    static constexpr char Separator = ' ';
	istream *in_;
public:
    explicit Deserializer(std::istream& in)
        : in_(&in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
	Error operator()(ArgsT&... args)
    {
        return process(args...);
    }
   

private:
    Error process(uint64_t &value){
        string number;
        uint64_t num;
        
        *in_ >> number;
        try{
        	num = stoull(number);	
        }catch(const std::invalid_argument&){
        	return Error::CorruptedArchive;
        }
        
        value = num;
        return Error::NoError;
    }
    
    Error process(bool &value)
    {	
        std::string text;
        *in_ >> text;
        
        if (text == "true")
        	value = true;
        else if (text == "false")
        	value = false;
        else
        	return Error::CorruptedArchive;
        
        return Error::NoError;
    }
    
    template <class T, class... ArgsT>
    Error process(T& arg, ArgsT&... args)
    {
        if(process(arg) == Error::NoError && 
        	process(forward<ArgsT&>(args)...) == Error::NoError){	
        	return Error::NoError;
        }
        
        return Error::CorruptedArchive;
    }
};