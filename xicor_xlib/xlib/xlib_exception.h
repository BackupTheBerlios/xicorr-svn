#ifndef _XLIB_EXCEPTION_H_
#define _XLIB_EXCEPTION_H_

#include "exception.h"

namespace xicor {
namespace xlib {
    /**
     * @brief Base exception thrown from xlib library.
     */
    class XlibException: public Exception {
        protected:
            std::string module() const
            {
                return "Xlib";
            }
        public:
            XlibException () {}
            
            XlibException (std::string str)
                :Exception(str) {}
                
            XlibException(std::string message, 
                          std::string fname, 
                          uint32 lnum)
                :Exception(message, fname, lnum)
            {}

            XlibException (const Exception& ex)
                :Exception(ex) {}
    };
    
} //namespace xlib
} // namespace xicor

#endif //_XLIB_EXCEPTION_H_
