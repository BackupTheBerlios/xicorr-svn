#include "plugin_monitor_impl.h"

using namespace xicor::thread;

namespace xicor {
namespace core {

    PluginMonitor::PluginMonitor()
        :current_id(0),numOfPlugins(0),active(0)
    {
    }
    
    PluginMonitor::~PluginMonitor()
    {}

    //sometimes threads may wake up without any signal. To avoid this
    //plugin threads will check the situation with this method.
    //also the monitor thread itself will use it for the same purpose
    bool PluginMonitor::legalPluginsWakingUp() throw()
    {
        //active var reading-writing must be synchronized.
        Locker activeVarLocker(&activeVarLock);
        if (active > 0)
            return true;
        return false;
    }
    
    void PluginMonitor::workIsDone(byte id) throw()
    {
        //active var reading-writing must be synchronized and 
        //as quick as possible.
        activeVarLock.lock();
        active--;
        //all plugins have done their work and are sleeping now
        if (!active) {
            //unlock active var before waking up monitor thread
            activeVarLock.unlock();
            //wake up monitor thread
            xicor::thread::Locker locker(&pluginsAreWorkingLock);
            pluginsAreWorkingCond.wake_all();
        }
        //first time after registration all plugins got to sleep. 
        //Now we are ready to work.
        else if (active == -numOfPlugins) {
            active = 0;
            activeVarLock.unlock();
        }
        else
            activeVarLock.unlock();
    }

    byte PluginMonitor::registerPlugin(xicor::plugins::iPlugin* plugin) throw()
    {
        //add new plugin to the storage
        plugin_map[current_id] = plugin;
        //inc the registered plugins counter
        numOfPlugins++;
        //inc the next id counter
        return current_id++;
    }

            
    void PluginMonitor::unlockAllPlugins() throw()
    {
        //if for some reason (just after registration or unknown error) there 
        //are plugins that haven't done the work - let's wait for them.
        //Yeah, there are other ways to wait without hard CPU loading. But this
        //is the most simple and now I have no time.
        //TODO:
        while(active)
            Thread::yield();

        Locker locker(&lock);
        //set the active plugin counter
        active = numOfPlugins;
        //wake the plugins up
        wCond.wake_all();
    }

    void PluginMonitor::updateObserved() throw()
    {
        //just block every possible plugin try to wake up the main thread 
        //before waking up plugin threads
        Locker locker(&pluginsAreWorkingLock);
        //wake the plugins up
        unlockAllPlugins();
        //wait for all plugins work is done
        do
            pluginsAreWorkingCond.wait(&pluginsAreWorkingLock);
        while (legalPluginsWakingUp());
    }
    
} //namespace core
} //namespace xicor
