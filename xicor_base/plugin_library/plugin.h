#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

namespace xicor {
    namespace plugins {
        class iComDataStorage;
    }
    namespace conf {
        class iConfiguration;
    }
}

#include "plugin_result.h"
#include "thread_library/thread.h"
#include "thread_library/lock.h"
#include "thread_library/locker.h"
#include "thread_library/wait_condition.h"
#include "plugin_monitor.h"

#include <string>
#include <iostream>

namespace xicor {
namespace plugins {
    
    /**
     * @brief This class provides interface to plugin object.
     * It consists of:
     * type - string that specified type of plugin
     * current types are:
     * process
     * These plugins asynchronically work after any input recieved by system 
     * plugin and before any output done by system.
     * NOTE: Don't delete plugin.
     */
    class iPlugin: public xicor::thread::Thread {
        private:
            byte id;
            xicor::thread::Lock* lock;
            xicor::thread::WaitCondition* wCond;
            iPluginMonitor* pmonitor;
        protected:
            iPlugin()
            {}
            
            virtual ~iPlugin()
            {}
        public:
            /**
             * @brief Service method. Used by PluginManager.
             */
            void _set_monitoring_on(iPluginMonitor* _pmonitor)
            {
                pmonitor = _pmonitor;
                id = pmonitor->registerPlugin(this);
                lock = pmonitor->getLock();
                wCond = pmonitor->getWaitCondition();
            }
            /**
             * @brief Returns plugin type.
             */
            virtual const std::string getType() const throw() = 0;
            /**
             * @brief Init method.
             */
            virtual PluginResult init(xicor::conf::iConfiguration* conf,
                                        iComDataStorage* comdata) throw()
            {
                return PluginResult();
            }
            /**
             * @brief Deinit method.
             */
            virtual void deinit() throw()
            {}
            /**
             * @brief Process method.
             */
            virtual PluginResult work() const throw() = 0;
            /**
             * @brief Service method. In-thread running method.
             */
            void run() throw()
            {
                if (!pmonitor)
                    return;

                while(!test_stop())
                {
                    {
                        xicor::thread::Locker locker(lock);
                        pmonitor->workIsDone(id);
                        do
                            wCond->wait(lock);
                        while (!pmonitor->legalPluginsWakingUp());
                    }
                    
                    PluginResult res;
                    res = this->work();
                    if (!res.isSuccessful()) {
                        std::cout << "Error in plugin: " << res.what() << std::endl;
                        exit(-1);
                    }
                }
            }
    };

} //namespace plugins
} //namespace xicor

/**
 * @brief Macros that defines plugin factory function.
 */
#define SET_FACTORY_FOR_PLUGIN(plugin_class_name) \
    static xicor::plugins::plugin_class_name pluginInstance; \
    extern "C" xicor::plugins::iPlugin* makePlugin() \
    { \
        return &pluginInstance; \
    }

#endif //_IPLUGIN_H_
