#ifndef _BAD_CONFIGURATION_EXCEPTION_H_
#define _BAD_CONFIGURATION_EXCEPTION_H_

#include "core_exception.h"

namespace xicor {
namespace core {
    /**
     * @brief This class defines configuration problem (in loading or parsing conf files etc) exception
     */
    class BadConfigurationException: public CoreException {
        protected:
            std::string module() const
            {
                return "ConfigurationManager";
            }
        public:
            BadConfigurationException() {}
            
            BadConfigurationException(std::string str) 
                :CoreException(str) {}
                
            BadConfigurationException(std::string message, 
                                        std::string fname, 
                                        uint32 lnum)
                :CoreException(message, fname, lnum)
            {}
                
            BadConfigurationException(const Exception& ex) 
                :CoreException(ex) {}
    };
    
} //namespace core
} //namespace xicor

#endif //_BAD_CONFIGURATION_EXCEPTION_H_
