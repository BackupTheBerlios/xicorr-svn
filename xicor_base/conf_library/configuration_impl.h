#ifndef _CONFIGURATION_IMPL_H_
#define _CONFIGURATION_IMPL_H_

#include "configuration.h"
#include "destroyable.h"
#include "serializeable.h"
#include "types.h"

#include <map>

namespace xicor {
namespace conf {
    
    /**
     * @brief This is iConfiguration interface implementation as a simple
     * map of std::string and MetaObject.
     */
    class ConfigurationImpl: public iConfiguration {
        public:
             void serialize (std::ostream& out) const throw (Exception);
    };
    
} //namespace conf
} //namespace xicor

#endif //_CONFIGURATION_IMPL_H_
