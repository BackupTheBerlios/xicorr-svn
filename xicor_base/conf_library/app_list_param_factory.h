#ifndef _APPLIST_PARAM_FACTORY_H_
#define _APPLIST_PARAM_FACTORY_H_

#include "param_factory.h"
#include "app_name_param.h"

namespace xicor {
namespace conf {

class AppListParamFactory: public iParamFactory {
	private:
		std::string mode;
    public:
		AppListParamFactory(std::string _mode)
		{
			mode = _mode;
		}
		
		iParam* makeParam (std::string param_str) const
										throw (ConfLibraryException)
		{
			if (!meaningful(param_str))
    	    	return NULL;
        
		    return new AppNameParam(param_str, mode);
		}
};

} //namespace conf
} //namespace xicor

#endif //_APPLIST_PARAM_FACTORY_H_
