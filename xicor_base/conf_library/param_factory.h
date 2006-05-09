#ifndef _PARAM_FACTORY_H_
#define _PARAM_FACTORY_H_

namespace xicor {
	namespace conf {
		class iParam;
	}
}

#include "destroyable.h"
#include "conf_library_exception.h"

#include <string>

namespace xicor {
namespace conf {
	/**
	 * @brief Param creating singltone class.
	 */
	class iParamFactory: public iDestroyable {
		public:
			/* @brief Checks if string must be interpretated.
	 		*/
    		bool meaningful(std::string param_str) const;
    		/* @brief Makes new param object by its name.
	 		*/
			virtual iParam * makeParam (std::string name) const
								throw (ConfLibraryException)= 0;
			/* @brief Makes new singletone param factory object by the
			 * filename it will process.
	 		*/
			static iParamFactory* makeParamFactory (std::string filename)
								throw (ConfLibraryException);
	};
	
} //namespace conf
} //namespace xicor

#endif //_PARAM_FACTORY_H_
