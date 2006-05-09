#ifndef _PLUGIN_MONITOR_IMPL_H_
#define _PLUGIN_MONITOR_IMPL_H_

namespace xicor {
	namespace plugins {
		class iPlugin;
	}
}

#include "plugin_library/plugin.h"
#include "observer.h"

#include <map>

namespace xicor {
namespace core {

	class PluginMonitor: public xicor::plugins::iPluginMonitor,
							public iObserver {
		private:
			std::map<byte,xicor::plugins::iPlugin*> plugin_map;
			std::map<byte,bool> activity_map;
			xicor::thread::Lock lock;
			xicor::thread::Lock activeVarLock;
			xicor::thread::Lock pluginsAreWorkingLock;
			xicor::thread::WaitCondition wCond;
			xicor::thread::WaitCondition pluginsAreWorkingCond;
			byte current_id;
			int numOfPlugins;
			int active;
		public:
			PluginMonitor();
			virtual ~PluginMonitor();
			
			xicor::thread::Lock* getLock()
			{
				return &lock;
			}
			
    		xicor::thread::WaitCondition* getWaitCondition()
    		{
    			return &wCond;
    		}
    		
			void workIsDone(byte id) throw();
    		/**
    		 * @brief Returns register id. Used only by plugins for
    		 * registering them in the monitoring.
    		 */
    		byte registerPlugin(xicor::plugins::iPlugin* plugin) throw();

			bool legalPluginsWakingUp() throw();
			
    		///@brief Unlocks all "paused" plugin threads.
    		void unlockAllPlugins() throw();
    		
    		void updateObserved() throw();
	};

} //namespace core
} //namepace xicor

#endif //_PLUGIN_MONITOR_IMPL_H_
