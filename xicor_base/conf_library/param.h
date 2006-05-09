#ifndef _PARAM_H_
#define _PARAM_H_

namespace xicor {
	namespace conf {
		class iConfiguration;
	}
}

#include "destroyable.h"
#include "conf_library_exception.h"

namespace xicor {
namespace conf {
    
    /**
     * @brief This class provides interface to configuration parameter.
     * It consists of:
     * name - string that specified parameter name
     * value - data of any type that specified current value of parameter
     */
    class iParam: public iDestroyable {
        public:
            virtual void fill(iConfiguration* conf) 
            							throw (ConfLibraryException) = 0;
    };
    
} //namespace conf
} //namespace xicor

#endif //_PARAM_H_
