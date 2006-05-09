#ifndef _PLUGIN_LIST_PARAM_FACTORY_H_
#define _PLUGIN_LIST_PARAM_FACTORY_H_

#include "param_factory.h"
#include "plugin_name_param.h"

#include <sstream>

namespace xicor {
namespace conf {

class PluginListParamFactory: public iParamFactory {
    public:
		iParam* makeParam (std::string param_str) const
										throw (ConfLibraryException)
		{
			if (!meaningful(param_str))
		        return NULL;

	    	return new PluginNameParam(param_str);
		}
};

} //namespace conf
} //namespace xicor

#endif //_PLUGIN_LIST_PARAM_FACTORY_H_
