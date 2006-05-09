#ifndef _BINDING_PARAM_H_
#define _BINDING_PARAM_H_

#include "param_impl.h"
#include "configuration.h"

#include <sstream>

namespace xicor {
namespace conf {
    
    class BindingParam: public ParamImpl {
    	private:
    		std::string action;
    		std::string key;
    		std::string modifier;
        public:
            BindingParam(std::string _value) throw (ConfLibraryException)
            {
            	std::string::operator=("BindingParam");
            	
		   		std::istringstream value_stream(_value);
		    	value_stream >> action >> key >> modifier;
		        if (action != "WordChange" && action != "LineChange"
		        	&& action != "SelectionChange" && action != "ModeSwitch")
		            throw ConfLibraryException("Binding action can't be " + action);
		        if (key != "Pause/Break" && key != "ScrollLock" && key != "PtrScr/SysRq")
		            throw ConfLibraryException("Binding key can't be " + key);
		        if (modifier != "Ctrl" && modifier != "None")
		        	throw ConfLibraryException("Binding modifier can't be " + modifier);
            }
			
			void fill(iConfiguration* conf) throw (ConfLibraryException)
         	{
         		try {
	         		List<std::string> bindings_list;
	         		try {
	         			bindings_list = conf->get<List<std::string> >(*this);
	         		}
	         		catch (Exception& ex) {
	         		}
	         		bindings_list.push_back(action + " " + key + " " + modifier + " " );
	         		conf->set<List<std::string> >(*this, bindings_list);
         		}
         		catch (Exception& ex) {
         			throw ConfLibraryException(ex);
         		}
         	}
    };
    
} //namespace conf
} //namespace xicor

#endif //_BINDING_PARAM_H_
