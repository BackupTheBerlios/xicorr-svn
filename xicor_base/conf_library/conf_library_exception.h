#ifndef _CONF_LIBRARY_EXCEPTION_H_
#define _CONF_LIBRARY_EXCEPTION_H_

#include "exception.h"

namespace xicor {
namespace conf {
    /**
     * @brief Base exception thrown from conf_library (part of base) class
     */
    class ConfLibraryException: public Exception {
        protected:
            std::string module() const
            {
                return "ConfLibrary";
            }
        public:
            ConfLibraryException () {}
            
            ConfLibraryException (std::string str)
                :Exception(str) {}

            ConfLibraryException (const Exception& ex)
                :Exception(ex) {}
    };
    
} //namespace conf
} // namespace xicor

#endif //_CONF_LIBRARY_EXCEPTION_H_
