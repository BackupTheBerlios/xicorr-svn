#include "exception.h"
#include <iostream>

namespace xicor {
    
    Exception::Exception ()
    {
        location.line_num = 0;
    }
    
    Exception::Exception (const Exception& ex)
    {
        location = ex.getLocation();
        this->message = ex.getMessage();
        if (!ex.getModuleName().empty())
            this->previous = ex.getModuleName();
        else
        if (!ex.module().empty())
            this->previous = ex.module() + "::";
    }
    
    Exception::Exception (std::string _message)
    {
        location.line_num = 0;
        
        message = _message;
    }
    
    Exception::Exception (std::string _message, std::string fname, uint32 lnum)
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
    
    const ELocation& Exception::getLocation() const
    {
        return location;
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
    
    TypeCastingFailedException::TypeCastingFailedException () 
    {
    }
            
    TypeCastingFailedException::TypeCastingFailedException (std::string str)
        :Exception(str) 
    {
    }

    TypeCastingFailedException::TypeCastingFailedException(std::string message, 
                                                            std::string fname, 
                                                            uint32 lnum)
        :Exception(message, fname, lnum)
    {
    }
    
    TypeCastingFailedException::TypeCastingFailedException (const Exception& ex)
        :Exception(ex) 
    {
    }

    ObjectNotFoundException::ObjectNotFoundException () 
    {
    }
            
    ObjectNotFoundException::ObjectNotFoundException (std::string str)
        :Exception(str) 
    {
    }

    ObjectNotFoundException::ObjectNotFoundException(std::string message, 
                                                    std::string fname, 
                                                    uint32 lnum)
        :Exception(message, fname, lnum)
    {
    }

    ObjectNotFoundException::ObjectNotFoundException (const Exception& ex)
        :Exception(ex) 
    {
    }
    
    AlreadyExistsException::AlreadyExistsException () 
    {
    }
            
    AlreadyExistsException::AlreadyExistsException (std::string str)
        :Exception(str) 
    {
    }

    AlreadyExistsException::AlreadyExistsException(std::string message, 
                                                    std::string fname, 
                                                    uint32 lnum)
        :Exception(message, fname, lnum)
    {
    }
    
    AlreadyExistsException::AlreadyExistsException (const Exception& ex)
        :Exception(ex) 
    {
    }
    
} //namespace xicor
