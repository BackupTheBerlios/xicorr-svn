#ifndef _BUFFER_ACTION_BINDINGS_PARAM_FACTORY_H_
#define _BUFFER_ACTION_BINDINGS_PARAM_FACTORY_H_

#include "conf_library/param_factory.h"
#include "buffer_action_binding_param.h"

namespace xicor {
namespace conf {

class BufferActionBindingsParamFactory: public iParamFactory {
    private:
    public:
        BufferActionBindingsParamFactory()
        {}
        
        iParam* makeParam (const std::string& param_str) const
                                        throw (ConfLibraryException)
        {
            if (!meaningful(param_str))
                return NULL;
        
            return new BufferActionBindingParam(param_str);
        }
};

} //namespace conf
} //namespace xicor

#endif //_BUFFER_ACTION_BINDINGS_PARAM_FACTORY_H_
