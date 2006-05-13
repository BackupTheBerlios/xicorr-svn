#ifndef _PLUGIN_RUNTIME_EXCEPTION_H_
#define _PLUGIN_RUNTIME_EXCEPTION_H_

#include "core_exception.h"

namespace xicor {
namespace core {
    /**
     * @brief This class defines raised plugin runtime error exception
     */
    class PluginRuntimeException: public CoreException {
        protected:
            std::string module() const
            {
                return "PluginManager";
            }
        public:
            PluginRuntimeException() {}
            
            PluginRuntimeException(std::string str) 
                :CoreException(str) {}
                
            PluginRuntimeException(std::string message, 
                                std::string fname, 
                                uint32 lnum)
                :CoreException(message, fname, lnum)
            {}
                
            PluginRuntimeException(const Exception& ex) 
                :CoreException(ex) {}
    };
    
} //namespace core
} //namespace xicor

#endif //_PLUGIN_RUNTIME_EXCEPTION_H_
