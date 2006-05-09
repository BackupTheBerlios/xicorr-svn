#include "configuration_manager.h"
#include "plugin_library/com_data_storage.h"
#include "plugin_manager.h"
#include "conf_library/configuration_impl.h"
#include "stl_ext.h"
#include "core.h"

#include <sstream>

using namespace xicor::conf;

namespace xicor {
namespace core {

    static std::string DEFAULT_CONF_DIR_PATH = ".xicor/";

    static const std::string DEFAULT_MAIN_CONF_FILENAME = "xicor.conf";
    static const std::string DEFAULT_PLUGINS_CONF_FILENAME = "xicor_plugins.list";
    static const std::string DEFAULT_BINDINGS_CONF_FILENAME = "xicor_bindings.conf";

    static const std::string DEFAULT_DENY_LIST_FILENAME = "xicor_deny.list";
    static const std::string DEFAULT_ALLOW_LIST_FILENAME = "xicor_allow.list";
    
    Core::Core () throw (CoreException)
    	:exit(false)
    {
    	std::vector<std::string> filename_array;
    	std::string home = getenv("HOME");
    	DEFAULT_CONF_DIR_PATH = home + "/" + DEFAULT_CONF_DIR_PATH;
    	
    	filename_array.push_back(DEFAULT_MAIN_CONF_FILENAME);
		filename_array.push_back(DEFAULT_PLUGINS_CONF_FILENAME);
		filename_array.push_back(DEFAULT_BINDINGS_CONF_FILENAME);
		filename_array.push_back(DEFAULT_DENY_LIST_FILENAME);
		filename_array.push_back(DEFAULT_ALLOW_LIST_FILENAME);
    		
        cfg_manager = new ConfigurationManager(filename_array);
        pm_manager = new PluginManager(DEFAULT_CONF_DIR_PATH + "plugins/");
        cd_storage = new xicor::plugins::iComDataStorage;
        cfg = new ConfigurationImpl;
    }
    
    Core::~Core ()
    {
        pm_manager->deinitPlugins();
        if (cfg_manager)
            delete cfg_manager;
        if (cd_storage)
            delete cd_storage;
        if (cfg)
            delete cfg;
    }

    void Core::init () throw (CoreException)
    {
        try {
            cfg_manager->loadConfiguration (cfg, DEFAULT_CONF_DIR_PATH);
            
            std::string tmp;
            std::ostringstream plugins(tmp);
            List<std::string> names = cfg->get< List<std::string> >("PluginName");
            plugins << names;
            pm_manager->loadPlugins(plugins.str());
            pm_manager->initPlugins(cfg,cd_storage);
        }
        catch (const Exception& ex) {
            throw CoreException(ex);
        }
        catch (const std::exception& ex) {
            throw CoreException(ex.what());
        }
    }
    
    void Core::start () throw (CoreException)
    {
    	try {
    		pm_manager->runSystem();
    	}
    	catch (Exception& ex) {
    		throw CoreException(ex);
    	}
    }
        
    void Core::stop () throw (CoreException)
    {
    	exit = true;
    }
    
    void Core::restart () throw (CoreException)
    {
    }
        
    void Core::serialize (std::ostream& out) const throw (Exception)
    {
        cfg->serialize(out);
    }

} //namespace core
} //namespace xicor
