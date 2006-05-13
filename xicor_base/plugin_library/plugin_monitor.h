#ifndef _IPLUGIN_MONITOR_H_
#define _IPLUGIN_MONITOR_H_

namespace xicor {
    namespace plugins {
        class iPlugin;
    }
}

#include "observable.h"
#include "thread_library/thread.h"
#include "thread_library/lock.h"
#include "thread_library/locker.h"
#include "thread_library/wait_condition.h"

#include <string>

namespace xicor {
namespace plugins {
    
    class iPluginMonitor: public Observable {
        public:
            virtual void workIsDone(byte id) throw() = 0;
            /**
             * @brief Returns register id. Used only by plugins for
             * registering them in the monitoring.
             */
            virtual byte registerPlugin(iPlugin* plugin) throw() = 0;
            
            virtual xicor::thread::Lock* getLock() = 0;
            virtual xicor::thread::WaitCondition* getWaitCondition() = 0;

            ///@brief Test if the thread may work or it must sleep again.
            ///Sometimes threads may wake up without any signal. To avoid this
            ///plugin threads will check the situation with this method.
            ///Also the monitor thread itself will use it for the same purpose.
            virtual bool legalPluginsWakingUp() throw() = 0;
            
            ///@brief Unlocks all "paused" plugin threads.
            virtual void unlockAllPlugins() throw() = 0;
    };

} //namespace plugins
} //namespace xicor

#endif //_IPLUGIN_MONITOR_H_
