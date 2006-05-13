#include "configuration_manager.h"
#include "conf_library/param_factory.h"
#include "conf_library/configuration.h"
#include "conf_library/main_conf_param_factory.h"
#include "conf_library/app_list_param_factory.h"
#include "conf_library/plugin_list_param_factory.h"
#include "conf_library/bindings_param_factory.h"
#include "conf_library/param.h"

#include <fstream>
#include <sstream>

using namespace xicor::conf;

namespace xicor {
namespace core {
    
    ConfigurationManager::ConfigurationManager (std::vector<std::string> _filename_array)
    {
        filename_array = _filename_array;
        
        iParamFactory::registerParamFactory(DEFAULT_MAIN_CONF_FILENAME, new MainConfParamFactory);
        iParamFactory::registerParamFactory(DEFAULT_ALLOW_LIST_FILENAME, new AppListParamFactory("Allow"));
        iParamFactory::registerParamFactory(DEFAULT_DENY_LIST_FILENAME, new AppListParamFactory("Deny"));
        iParamFactory::registerParamFactory(DEFAULT_BINDINGS_CONF_FILENAME, new BindingsParamFactory);
        iParamFactory::registerParamFactory(DEFAULT_PLUGINS_CONF_FILENAME, new PluginListParamFactory);
    }
    
    ConfigurationManager::~ConfigurationManager ()
    {
    }
        
    void ConfigurationManager::loadConfiguration (iConfiguration* conf,
                                                    std::string path_to_conf_dir)
                                                        throw (BadConfigurationException)
    {
        iParamFactory* param_factory;
        iParam* param = NULL;

        for (uint32 i = 0; i < filename_array.size(); i++)
        {
            try {
                param_factory = iParamFactory::makeParamFactory(filename_array[i]);
                std::ifstream conf_stream((path_to_conf_dir + filename_array[i]).c_str());
                if (!conf_stream)
                    THROW(BadConfigurationException, std::string("Bad conf filename: ")
                                         + (path_to_conf_dir + filename_array[i]).c_str());
            
                while ( !conf_stream.eof() )
                {
                    std::string buffer_line;
                    getline (conf_stream, buffer_line);
                    if (buffer_line.empty() && !conf_stream.eof())
                        continue;

                    param = param_factory->makeParam(buffer_line);
                    if (param != NULL) {
                        param->fill(conf);
                        delete param;
                    }
                    param = NULL;
                }
            }
            catch (const Exception& ex) {
                throw BadConfigurationException(ex);
            }
            catch (const std::exception& ex) {
                throw BadConfigurationException(ex.what());
            }
        }
    }
    
    void ConfigurationManager::serialize (std::ostream& out) const
                                                        throw (Exception)
    {
    }
    
} //namespace core
} //namespace xicor
