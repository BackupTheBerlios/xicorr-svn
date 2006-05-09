#include "plugin_manager.h"
#include "plugin_library/plugin.h"
#include "plugin_library/system_plugin.h"

#include <dlfcn.h>
#include <sstream>

using namespace xicor::thread;
using namespace xicor::plugins;
using namespace xicor::conf;

namespace xicor {
namespace core {

	PluginManager::PluginManager(std::string _path)
		:path(_path), system_plugin(NULL), process_plugin_monitor(NULL)
	{}

	PluginManager::~PluginManager()
	{
		std::list<void*>::const_iterator itr;
		for(itr = library_list.begin();
			itr != library_list.end();
			itr++)
			dlclose(*itr);
	}
	
	void PluginManager::loadPlugins(std::string filenames)
													throw (BadPluginException)
	{
		std::istringstream filenames_stream(filenames);
		std::string filename;
		while (!filenames_stream.eof())
		{
			filename.erase();
			filenames_stream >> filename;
			if (filename.empty())
				break;
			void* lhandler = dlopen((path + filename).c_str(), RTLD_LAZY);
			if (lhandler) {
				library_list.push_back(lhandler);
				iPlugin* (*PluginFactoryMethod)();
				dlerror();// Clear any existing dl error
                *(void **) (&PluginFactoryMethod) = dlsym(lhandler, "makePlugin");
                if ( dlerror() ) {
                	iSystemPlugin* (*SystemPluginFactoryMethod)();
                	*(void **) (&SystemPluginFactoryMethod) = dlsym(lhandler, "makeSystemPlugin");
                	if ( dlerror() )
                		throw BadPluginException("Plugin file " + filename +
                									 " : Undefined factory method");
                	else
                		system_plugin = SystemPluginFactoryMethod();
                }
                else {
	                iPlugin* plugin = PluginFactoryMethod();
	                if ( plugin->getType() == "process")
	                	process_plugin_list.push_back(plugin);
	                else
	                	throw BadPluginException(filename + ": Unsupported plugin type");
               }	
			}
			else
				throw BadPluginException("Plugin file " + filename
											+ " can't be loaded: " + dlerror());
		}
	}

	void PluginManager::initPlugins(
					iConfiguration* conf,
					iComDataStorage* comdata) throw (BadPluginException)
	{
		process_plugin_monitor = new PluginMonitor;
		PluginResult res = system_plugin->init(conf,comdata);
		if (!res.isSuccessful())
				throw BadPluginException(res);
		
		std::list<iPlugin*>::const_iterator itr;
		for(itr = process_plugin_list.begin();
			itr != process_plugin_list.end();
			itr++)
		{
			(*itr)->_set_monitoring_on(process_plugin_monitor);
			PluginResult res = (*itr)->init(conf,comdata);
			(*itr)->start();
			if (!res.isSuccessful())
				throw BadPluginException(res);
		}
	}
	
	void PluginManager::deinitPlugins() const throw ()
	{
		if(system_plugin)
			system_plugin->deinit();
		std::list<iPlugin*>::const_iterator itr;
		for(itr = process_plugin_list.begin();
			itr != process_plugin_list.end();
			itr++)
		{
			if( (*itr)->is_running() ) {
				(*itr)->stop();
				(*itr)->join();
			}
			(*itr)->deinit();
		}
		if (process_plugin_monitor)
			delete process_plugin_monitor;
	}
	
	void PluginManager::runSystem() throw (PluginRuntimeException)
	{
		try {
			
			system_plugin->attachObserver(process_plugin_monitor);
		
			while (1) {
				system_plugin->runOnInput();
				system_plugin->runOnOutput();
			}
		}
		catch (Exception& ex) {
			throw PluginRuntimeException(ex);
		}
		catch (std::exception& ex) {
			throw PluginRuntimeException(ex.what());
		}
		catch (...) {
			throw PluginRuntimeException("UnhandledException");
		}
	}

} //namespace core
} //namespace xicor
