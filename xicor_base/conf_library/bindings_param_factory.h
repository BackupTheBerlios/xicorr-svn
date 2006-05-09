#ifndef _BINDINGS_PARAM_FACTORY_H_
#define _BINDINGS_PARAM_FACTORY_H_

#include "param_factory.h"
#include "binding_param.h"

namespace xicor {
namespace conf {

class BindingsParamFactory: public iParamFactory {
    public:
		iParam* makeParam (std::string param_str) const
										throw (ConfLibraryException)
		{
			if (!meaningful(param_str))
    	    	return NULL;
		    
		    return new BindingParam(param_str);
		}
};

} //namespace conf
} //namespace xicor

#endif //_BINDINGS_PARAM_FACTORY_H_
