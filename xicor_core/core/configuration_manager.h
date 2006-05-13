#ifndef _CONFIGURATION_MANAGER_H_
#define _CONFIGURATION_MANAGER_H_

namespace xicor {
    namespace conf {
        class iConfiguration;
    }
}

#include "serializeable.h"
#include "destroyable.h"
#include "bad_configuration_exception.h"

#include <string>
#include <vector>

namespace xicor {
namespace core {
    
    
    static std::string DEFAULT_CONF_DIR_PATH = ".xicor/";
    static std::string DEFAULT_PLUGIN_CONF_DIR_PATH = ".xicor/plugins";

    static const std::string DEFAULT_MAIN_CONF_FILENAME = "xicor.conf";
    static const std::string DEFAULT_PLUGINS_CONF_FILENAME = "xicor_plugins.list";
    static const std::string DEFAULT_BINDINGS_CONF_FILENAME = "xicor_bindings.conf";

    static const std::string DEFAULT_DENY_LIST_FILENAME = "xicor_deny.list";
    static const std::string DEFAULT_ALLOW_LIST_FILENAME = "xicor_allow.list";
    
    /**
     * @brief This class is core part, that is responsible for opening, parsing and filling in 
     * configuration from all xicor configuration files
     */
    class ConfigurationManager: public iSerializeable, public iDestroyable {
        private:
            std::vector<std::string> filename_array;
        public:
            ConfigurationManager (std::vector<std::string> filename_array);
            ~ConfigurationManager ();
            /**
             * @brief Loads configuration from conf files to conf structures
             * @param conf defines pointer to config structure to load configuration data
             * @param path_to_conf_dir defines path to xicor configuration files directory. Default value is "~/.xicor/"
             */
            void loadConfiguration (xicor::conf::iConfiguration* conf,
                                    std::string path_to_conf_dir)
                                            throw (BadConfigurationException);
            
            void serialize (std::ostream& out) const throw (xicor::Exception);
    };
    
} //namespace core
} //namespace xicor

#endif //_CONFIGURATION_MANAGER_H_
