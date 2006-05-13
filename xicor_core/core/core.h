#ifndef _CORE_H_
#define _CORE_H_

namespace xicor {
    namespace core {
        class ConfigurationManager;
        class PluginManager;
    }
    namespace plugins {
        class iComDataStorage;
    }
    namespace conf {
        class iConfiguration;
    }
}

#include "serializeable.h"
#include "thread_library/lock.h"
#include "thread_library/wait_condition.h"
#include "core_exception.h"

namespace xicor {
namespace core {
    
    /**
     * @brief Main application class. Creates, initializes and runs configuration, logs, plugins and their communication structures.
     * Registers application signal handlers.
     */
    class Core: public iSerializeable {
        private:
            bool exit;
            ConfigurationManager* cfg_manager;
            PluginManager* pm_manager;
            xicor::conf::iConfiguration* cfg;
            xicor::plugins::iComDataStorage* cd_storage;
        public:
            Core () throw (CoreException);
            virtual ~Core ();
            /// Initialize core structures: configuration, configuration manager, plugin manager and communication data storage
            void init () throw (CoreException);
            /// Starts main application routine
            void start () throw (CoreException);
            /// Stops main application routine. No data delete.
            void stop () throw (CoreException);
            /// Stops main application routine. Then reinits structures and starts again.
            void restart () throw (CoreException);
            
            /// Prints all internal data into given stream.
            void serialize (std::ostream& out) const throw (xicor::Exception);
    };
    
} //namespace core
} //namespace xicor

#endif //_CORE_H_
