#include "default_mode_param.h"
#include "app_list_mode_param.h"
#include "verbose_level_param.h"
#include "main_conf_param_factory.h"

#include <sstream>

namespace xicor {
namespace conf {

iParam* MainConfParamFactory::makeParam (std::string param_str) const
										throw (ConfLibraryException)
{
	if (!meaningful(param_str))
        return NULL;
        
    std::istringstream param_stream(param_str);
    std::string name;
    
    param_stream >> name;
    param_str.erase(0, name.size() + 1);
    
    if (name == "DefaultMode")
        return new DefaultModeParam(param_str);
    else
    if (name == "AppListMode")
        return new AppListModeParam(param_str);
    else
    if (name == "VerboseLevel")
        return new VerboseLevelParam(param_str);
        
    throw ConfLibraryException("Unknown param: " + name);
    
    return NULL;
}

} //namespace conf
} //namespace xicor
