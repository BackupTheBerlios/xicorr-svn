#include "exception.h"
#include <iostream>

namespace xicor {
    
    Exception::Exception ()
    {
        //TODO
        location.filename = __FILE__;
        location.line_num = __LINE__;
    }
    
    Exception::Exception (const Exception& ex)
    {
        Exception();
        this->message = ex.getMessage();
        if (!ex.getModuleName().empty())
            this->previous = ex.getModuleName();
        else
        if (!ex.module().empty())
            this->previous = ex.module() + "::";
    }
    
    Exception::Exception (std::string _message)
    {
        Exception();
        
        message = _message;
    }
    
    Exception::Exception (std::string _message, std::string fname, unsigned int lnum)
    {
        message = _message;
        location.filename = fname;
        location.line_num = lnum;
    }
    
    Exception::~Exception () throw ()
    {
    }
            
    std::string Exception::getMessage () const
    {
        return message;
    }
    
    std::string Exception::getLocationFilename() const
    {
        return location.filename;
    }
    
    unsigned int Exception::getLocationLineNumber () const
    {
        return location.line_num;
    }
    
    std::string Exception::getModuleName() const
    {
        if (previous.empty())
            return this->module();
        return this->module() + "::" + previous;
    }
    
    const char* Exception::what() const throw()
    {
    	return message.c_str();
    }

} //namespace xicor
