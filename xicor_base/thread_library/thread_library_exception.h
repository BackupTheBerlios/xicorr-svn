#ifndef _THREAD_LIBRARY_EXCEPTION_H_
#define _THREAD_LIBRARY_EXCEPTION_H_

#include "exception.h"

namespace xicor {
namespace thread {
    /**
     * @brief Base exception thrown from thread_library (part of base) class
     */
    class ThreadLibraryException: public Exception {
        protected:
            std::string module() const
            {
                return "ThreadLibrary";
            }
        public:
            ThreadLibraryException () {}
            
            ThreadLibraryException (std::string str)
                :Exception(str) {}

            ThreadLibraryException (const Exception& ex)
                :Exception(ex) {}
    };
    
} //namespace thread
} //namespace xicor

#endif //_THREAD_LIBRARY_EXCEPTION_H_
