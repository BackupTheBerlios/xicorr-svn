#ifndef _BAD_PLUGIN_EXCEPTION_H_
#define _BAD_PLUGIN_EXCEPTION_H_

#include "core_exception.h"

namespace xicor {
namespace core {
    /**
     * @brief This class defines incorrect plugin problem (in loading
     * or verifying plugin files etc) exception
     */
    class BadPluginException: public CoreException {
        protected:
            std::string module() const
            {
                return "PluginManager";
            }
        public:
            BadPluginException() {}
            
            BadPluginException(std::string str) 
                :CoreException(str) {}
                
            BadPluginException(const Exception& ex) 
                :CoreException(ex) {}
    };
    
} //namespace core
} //namespace xicor

#endif //_BAD_PLUGIN_EXCEPTION_H_
