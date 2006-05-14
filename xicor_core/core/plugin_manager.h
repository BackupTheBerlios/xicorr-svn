#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

namespace xicor {
    namespace plugins {
        class iPlugin;
        class iSystemPlugin;
        class iComDataStorage;
    }
    namespace thread {
        class Lock;
        class WaitCondition;
    }
    namespace conf {
        class iConfiguration;
    }
}

#include "bad_plugin_exception.h"
#include "plugin_runtime_exception.h"
#include "plugin_monitor_impl.h"

#include "stl_ext.h"

namespace xicor {
namespace core {

/**
 * @brief Class that verify, loads/unloads and makes other
 * plugin management operations.
 */
class PluginManager {
    private:
        xicor::plugins::iSystemPlugin* system_plugin;
        PluginMonitor* process_plugin_monitor;
        std::list<xicor::plugins::iPlugin*> process_plugin_list;
        std::list<void*> library_list;
    public:
        PluginManager();
        virtual ~PluginManager();

        /**
         * @brief Verifies and loads plugin(s) by their filename(s).
         * @param filenames Contains one or more filenames separated
         * by spaces or '\n'
         */
        void loadPlugins(std::string filenames) throw (BadPluginException);

        /**
         * @brief Run init methods of the plugins in order of
         *  their loading.
         */
        void initPlugins(xicor::conf::iConfiguration* conf,
                            xicor::plugins::iComDataStorage* comdata)
                                                throw (BadPluginException);     

        /**
         * @brief Runs plugin working cycle.
         */
        void runSystem() throw (PluginRuntimeException);

        /**
         * @brief Run deinit methods of the plugins in order of
         *  their loading.
         */
        void deinitPlugins() const throw ();        
    
};

} //namespace core
} //namespace xicor

#endif //_PLUGIN_MANAGER_H_
