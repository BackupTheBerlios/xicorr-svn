#ifndef _ISYSTEM_PLUGIN_H_
#define _ISYSTEM_PLUGIN_H_

namespace xicor {
    namespace plugins {
        class iComDataStorage;
    }
    namespace conf {
        class iConfiguration;
    }
}

#include "plugin_result.h"
#include "destroyable.h"
#include "observable.h"

#include <string>
#include "stl_ext.h"
#include <iostream>

namespace xicor {
namespace plugins {

    /**
     * @brief This class provides interface to system plugin object.
     * First of all, core will initialize plugin by its <i>init()</i> 
     * method invocation. After that core will invocate <i>runOnInput()</i> 
     * method (notice, input method may sleep in select like routine) on the 
     * input stage of work and <i>runOnOutput()</i> method on the output stage.
     * When core will need to restart or shutdown plugin will be deinitialized 
     * by <i>deinit()</i> method invocation.
     * Notice, system plugin gets all work on environment (X Server, for example).
     * It is useful in some reasons. Also, this type of plugins doesn't work with 
     * threads because some environment API implementations (general Xlib, for 
     * example) are not thread safe.
     * NOTE: Don't delete plugin.
     */
    class iSystemPlugin: public Observable {
        protected:
            virtual ~iSystemPlugin(){};
        public:
            /**
             * @brief Init method.
             */
            virtual PluginResult init(xicor::conf::iConfiguration* conf,
                                        iComDataStorage* comdata) throw() = 0;
            /**
             * @brief Deinit method.
             */
            virtual void deinit() const throw() = 0;
            /**
             * @brief Input stage process method.
             */
            virtual void workOnInput() throw(Exception) = 0;
            /**
             * @brief Output stage process method.
             */
            virtual void workOnOutput() throw(Exception) = 0;
            
            void run(void (iSystemPlugin::*work_method)()) throw()
            {
                try {
                    (this->*work_method)();
                }
                catch (const Exception& ex) {
                    std::cout << "ERROR: "
                            << ex.getModuleName() << ": "
                            << ex.getMessage() << std::endl;
                }
            }
            
            void runOnInput() throw ()
            {
                this->run(& iSystemPlugin::workOnInput);
                notifyObservers();
            }
            
            void runOnOutput() throw ()
            {
                this->run(& iSystemPlugin::workOnOutput);
            }
    };

} //namespace plugins
} //namespace xicor

/**
 * @brief Macros that defines system plugin factory function.
 */
#define SET_FACTORY_FOR_SYSTEM_PLUGIN(plugin_class_name) \
    extern "C" xicor::plugins::iSystemPlugin* makeSystemPlugin() \
    { \
        xicor::plugins::plugin_class_name * pluginInstance = new xicor::plugins::plugin_class_name(); \
        return pluginInstance; \
    }
//      static xicor::plugins::plugin_class_name pluginInstance;

#endif //_ISYSTEM_PLUGIN_H_
