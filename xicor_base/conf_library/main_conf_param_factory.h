#ifndef _MAIN_CONF_PARAM_FACTORY_H_
#define _MAIN_CONF_PARAM_FACTORY_H_

#include "param_factory.h"

namespace xicor {
namespace conf {

class MainConfParamFactory: public iParamFactory {
    public:
       iParam* makeParam (std::string param_str) const
       								throw (ConfLibraryException);
};

} //namespace conf
} //namespace xicor

#endif //_MAIN_CONF_PARAM_FACTORY_H_
