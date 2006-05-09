#ifndef _PARAM_IMPL_H_
#define _PARAM_IMPL_H_

#include "param.h"

namespace xicor {
namespace conf {
    
    class ParamImpl: public iParam, public std::string {
    };
    
} //namespace conf
} //namespace xicor

#endif //_PARAM_IMPL_H_
