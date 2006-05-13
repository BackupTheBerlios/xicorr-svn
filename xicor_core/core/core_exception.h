#ifndef _CORE_EXCEPTION_H_
#define _CORE_EXCEPTION_H_

#include "exception.h"

namespace xicor {
namespace core {
    /**
     * @brief Base exception thrown from core class
     */
    class CoreException: public Exception {
        protected:
            std::string module() const
            {
                return "Core";
            }
        public:
            CoreException () {}
            
            CoreException (std::string str)
                :Exception(str) {}
                
            CoreException(std::string message, 
                          std::string fname, 
                          uint32 lnum)
                :Exception(message, fname, lnum)
            {}

            CoreException (const Exception& ex)
                :Exception(ex) {}
    };
    
} //namespace core
} // namespace xicor

#endif //_CORE_EXCEPTION_H_
