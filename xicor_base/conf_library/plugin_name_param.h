#ifndef _PLUGIN_NAME_PARAM_H_
#define _PLUGIN_NAME_PARAM_H_

#include "param_impl.h"
#include "stl_ext.h"
#include "configuration.h"
#include <iostream>

namespace xicor {
namespace conf {
    
    class PluginNameParam: public ParamImpl {
    	private:
    		std::string value;
        public:
            PluginNameParam(std::string _value) throw (ConfLibraryException)
            {
            	std::string::operator=("PluginName");
            	value = _value;
            }

			void fill(iConfiguration* conf) throw (ConfLibraryException)
         	{
         		try {
         			List<std::string> names_list;
         			try {
			     		names_list = conf->get<List<std::string> >(*this);
         			}
         			catch (Exception& ex) {
         			}
		     		names_list.push_back(value);
		     		conf->set<List<std::string> >(*this, names_list);
         		}
         		catch (Exception& ex) {
         			throw ConfLibraryException(ex);
         		}
         	}
    };
    
} //namespace conf
} //namespace xicor

#endif //_PLUGIN_NAME_PARAM_H_