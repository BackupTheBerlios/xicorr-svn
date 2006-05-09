#ifndef _BAD_EVENT_EXCEPTION_H_
#define _BAD_EVENT_EXCEPTION_H_

#include "core_exception.h"

namespace xicor {
namespace core {
    /**
     * @brief This class defines event problem.
     */
    class BadEventException: public CoreException {
        protected:
            std::string module() const
            {
                return "EventManager";
            }
        public:
            BadEventException() {}
            
            BadEventException(std::string str) 
                :CoreException(str) {}
                
            BadEventException(const Exception& ex) 
                :CoreException(ex) {}
    };
    
} //namespace core
} //namespace xicor

#endif //_BAD_EVENT_EXCEPTION_H_
