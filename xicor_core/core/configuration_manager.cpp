#include "configuration_manager.h"
#include "conf_library/param_factory.h"
#include "conf_library/configuration.h"
#include "conf_library/main_conf_param_factory.h"
#include "conf_library/app_list_param_factory.h"
#include "conf_library/plugin_list_param_factory.h"
#include "conf_library/bindings_param_factory.h"
#include "conf_library/param.h"
#include "conf_library/configuration_impl.h"

#include <fstream>
#include <sstream>

#include <dirent.h>

using namespace xicor::conf;

namespace xicor {
namespace core {
    
    static int32 selector (const struct dirent *file)
    {
        std::string name = file->d_name;
        std::string ext = name.substr(name.rfind(".") + 1, name.size());
        if (ext == "conf" || ext == "list")
            return 1;
        return 0;
    }
    
    List<std::string> ConfigurationManager::getFilenames(const std::string& dir)
    {
        List<std::string> files;
    
        struct dirent **list;
    
        int32 n = scandir (dir.c_str(), &list, selector, alphasort);
        if (n < 0)
            THROW(BadConfigurationException, "Can't list directory: " + dir);
        
        for (int32 i = 0; i < n; i++) 
        {
            files.push_back(list[i]->d_name);
            free(list[i]);
        }
        free(list);
            
        return files;
    }
    
    ConfigurationManager::ConfigurationManager ()
    {
        iParamFactory::registerParamFactory(DEFAULT_MAIN_CONF_FILENAME, new MainConfParamFactory);
        iParamFactory::registerParamFactory(DEFAULT_ALLOW_LIST_FILENAME, new AppListParamFactory("Allow"));
        iParamFactory::registerParamFactory(DEFAULT_DENY_LIST_FILENAME, new AppListParamFactory("Deny"));
        iParamFactory::registerParamFactory(DEFAULT_BINDINGS_CONF_FILENAME, new BindingsParamFactory);
        iParamFactory::registerParamFactory(DEFAULT_PLUGINS_CONF_FILENAME, new PluginListParamFactory);
    }
    
    ConfigurationManager::~ConfigurationManager ()
    {
        iParamFactory::clearFactories();
    }

    List<std::string> ConfigurationManager::getPluginsList (const std::string& path_to_file)
                                                        throw (BadConfigurationException)
    {
        ConfigurationImpl conf;
        
        std::string fname = 
                path_to_file.substr(path_to_file.rfind("/")+1, path_to_file.size());
        iParamFactory* param_factory = iParamFactory::makeParamFactory(fname);
        std::ifstream conf_stream((path_to_file).c_str());
        if (!conf_stream)
            THROW(BadConfigurationException, std::string("Bad conf filename: ")
                                     + (path_to_file).c_str());
        
        while ( !conf_stream.eof() )
        {
            std::string buffer_line;
            getline (conf_stream, buffer_line);
            if (buffer_line.empty() && !conf_stream.eof())
                continue;

            iParam* param = param_factory->makeParam(buffer_line);
            if (param) {
                param->fill(&conf);
                delete param;
            }
            param = NULL;
        }
        return conf.getStringList("PluginName");
    }
    
    void ConfigurationManager::loadConfiguration (iConfiguration* conf,
                                                  const List<std::string>& paths)
                                                        throw (BadConfigurationException)
    {
        try {
            List<std::string>::const_iterator path;
            for (path = paths.begin(); path != paths.end(); path++)
            {   
                iParamFactory* param_factory;
                iParam* param = NULL;
        
                List<std::string> fnames = getFilenames(*path);
                List<std::string>::iterator filename;
                for (filename = fnames.begin(); filename != fnames.end(); filename++)
                {
                    param_factory = iParamFactory::makeParamFactory(*filename);
                    std::ifstream conf_stream((*path + *filename).c_str());
                    if (!conf_stream)
                        THROW(BadConfigurationException, std::string("Bad conf filename: ")
                                                 + (*path + *filename).c_str());
                    
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
            }
        }
        catch (const std::exception& ex) {
            throw BadConfigurationException(ex.what());
        }
    }
    
    void ConfigurationManager::serialize (std::ostream& out) const
                                                        throw (Exception)
    {
    }
    
} //namespace core
} //namespace xicor
