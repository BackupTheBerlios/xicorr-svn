#include "configuration_manager.h"
#include "conf_library/param_factory.h"
#include "conf_library/configuration.h"
#include "conf_library/param.h"

#include <fstream>
#include <sstream>

using namespace xicor::conf;

namespace xicor {
namespace core {
    
    ConfigurationManager::ConfigurationManager (std::vector<std::string> _filename_array)
    {
    	filename_array = _filename_array;
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

		for (unsigned int i = 0; i < filename_array.size(); i++)
		{
			try {
				param_factory = iParamFactory::makeParamFactory(filename_array[i]);
		        std::ifstream conf_stream((path_to_conf_dir + filename_array[i]).c_str());
		        if (!conf_stream)
		            throw BadConfigurationException(std::string("Bad conf filename: ")
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
