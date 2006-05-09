#ifndef _APP_LIST_MODE_PARAM_H_
#define _APP_LIST_MODE_PARAM_H_

#include "param_impl.h"
#include "configuration.h"

namespace xicor {
namespace conf {
    
    class AppListModeParam: public ParamImpl {
    	private:
    		std::string value;
        public:
            AppListModeParam(std::string _value) throw (ConfLibraryException)
            {
            	std::string::operator=("AppListMode");
            	if (_value != "Allow" && _value != "Deny")
		            throw ConfLibraryException( *this + " can't take " + _value);
		        else
		            value = _value;
            }

			void fill(iConfiguration* conf) throw (ConfLibraryException)
         	{
         		conf->set<std::string>(*this, value);
         	}
    };
    
} //namespace conf
} //namespace xicor

#endif //_APP_LIST_MODE_PARAM_H_
