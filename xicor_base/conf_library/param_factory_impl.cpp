#include "param_factory.h"
#include "main_conf_param_factory.h"
#include "app_list_param_factory.h"
#include "plugin_list_param_factory.h"
#include "bindings_param_factory.h"
#include "exception.h"

#include <sstream>

namespace xicor {
namespace conf {
	
	static MainConfParamFactory* MainConfParamFactoryInstance = NULL;
	static AppListParamFactory* AppListAllowParamFactoryInstance = NULL;
	static AppListParamFactory* AppListDenyParamFactoryInstance = NULL;
	static PluginListParamFactory* PluginListParamFactoryInstance = NULL;
	static BindingsParamFactory* BindingsParamFactoryInstance = NULL;

} //namespace conf
} //namespace xicor

namespace xicor {
namespace conf {

	bool iParamFactory::meaningful(std::string param_str) const
	{
		std::istringstream str_stream(param_str);
		std::string tmp;
		str_stream >> tmp;
		if (tmp[0] == '#' || tmp.empty()) {
			return false;
		}
		return true;
	}
	
	iParamFactory* iParamFactory::makeParamFactory (std::string filename)
									throw (ConfLibraryException)
	{
		if (filename == "xicor.conf") {
			if (MainConfParamFactoryInstance == NULL)
				MainConfParamFactoryInstance
							 = new MainConfParamFactory;
			return MainConfParamFactoryInstance;
		}
		else
		if (filename == "xicor_allow.list") {
			if (AppListAllowParamFactoryInstance == NULL)
				AppListAllowParamFactoryInstance
							= new AppListParamFactory("Allow");
			return AppListAllowParamFactoryInstance;
	
		}
		else
		if (filename == "xicor_deny.list") {
			if (AppListDenyParamFactoryInstance == NULL)
				AppListDenyParamFactoryInstance
							= new AppListParamFactory("Deny");
			return AppListDenyParamFactoryInstance;
		}
		else
		if (filename == "xicor_bindings.conf") {
			if (BindingsParamFactoryInstance == NULL)
				BindingsParamFactoryInstance
							= new BindingsParamFactory;
			return BindingsParamFactoryInstance;
		}
		if (filename == "xicor_plugins.list") {
			if (PluginListParamFactoryInstance == NULL)
				PluginListParamFactoryInstance
							= new PluginListParamFactory;
			return PluginListParamFactoryInstance;
		}
		
		throw ConfLibraryException("Unknown filename");
		return NULL;
	}

} //namespace conf
} //namespace xicor
