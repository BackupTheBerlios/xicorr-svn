#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include "abstract_storage.h"

namespace xicor {
namespace conf {
    
    /**
     * @brief Simple serializeable configuration
     * interface class
     */
    class iConfiguration: public AbstractDataStorage<std::string> {
    };
    
} //namespace conf
} //namespace xicor

#endif //_CONFIGURATION_H_
