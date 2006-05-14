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
    
    Core::Core () throw (CoreException)
        :exit(false)
    {       
        cfg_manager = new ConfigurationManager;
        pm_manager = new PluginManager;
        cd_storage = new xicor::plugins::iComDataStorage;
        cfg = new ConfigurationImpl;
        
        std::string home = getenv("HOME");
        DEFAULT_CONF_DIR_PATH = home + "/" + DEFAULT_CONF_DIR_PATH;
        DEFAULT_PLUGIN_CONF_DIR_PATH = home + "/" + DEFAULT_PLUGIN_CONF_DIR_PATH;
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
            std::string pname_start = "libxicor_";
            List<std::string> pnames = cfg_manager->getPluginsList(
                                                DEFAULT_PLUGIN_CONF_DIR_PATH + 
                                                DEFAULT_PLUGINS_CONF_FILENAME);
            
            List<std::string> dirnames(DEFAULT_CONF_DIR_PATH);
            List<std::string>::iterator pname;
            for (pname = pnames.begin(); pname != pnames.end(); pname++)
            {
                std::string tmp = *pname;
                tmp.erase(0, 9);
                tmp.erase(tmp.rfind(".so"), 3);
                tmp = DEFAULT_PLUGIN_CONF_DIR_PATH + tmp + "/";
                *pname = tmp + *pname;
                dirnames.push_back(tmp);
            }
            
            std::string tmp;
            std::ostringstream plugins(tmp);
            plugins << pnames;
            pm_manager->loadPlugins(plugins.str());
            
            cfg_manager->loadConfiguration (cfg, dirnames);
            
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
