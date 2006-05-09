#include "plugin_library/plugin.h"
#include "plugin_library/com_data_storage.h"

using namespace xicor::conf;

namespace xicor {
namespace plugins {
	
	class XicorDictProcessPlugin: public iPlugin {
		private:
			// key for data in the storage we'll use
			std::string input_data_key;
			std::string output_data_key;
			iComDataStorage* comdata;
			iConfiguration* conf;
		public:
			XicorDictProcessPlugin()
				:input_data_key("current_input"),
				 output_data_key("current_output"),
				 comdata(NULL)
			{}
			
			/********* register plugin type *******/
			const std::string getType() const throw()
			{
				return "process";
			}
			
			/********* init plugin *******/
        	PluginResult init(iConfiguration* _conf,
        						iComDataStorage* _comdata) throw()
        	{
        		if (_comdata)
	        		comdata = _comdata;
	        	else
	        		return PluginResult("Bad iComDataStorage ptr");
	        	if (_conf)
	        		conf = _conf;
	        	else
	        		return PluginResult("Bad iConfiguration ptr");
        		return PluginResult();
        	}
        	
			/********* deinit plugin *******/
        	void deinit() throw()
        	{
        		if (!comdata)
        			return;
        	}
			
			/********* work plugin method *******/
			PluginResult work() const throw()
        	{
        		try {
        			std::string input_string = 
        					comdata->get<std::string>(input_data_key);
        			if(!input_string.empty())
	      				comdata->set<std::string>(output_data_key, input_string);
        		}
        		catch (Exception& ex) {
        			return PluginResult(ex);
        		}
        		
        		return PluginResult(); 
        	}
	};

	SET_FACTORY_FOR_PLUGIN(XicorDictProcessPlugin);
		
} //namespace plugins
} //namespace xicor
