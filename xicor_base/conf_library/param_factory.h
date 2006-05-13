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
#include "stl_ext.h"

namespace xicor {
namespace conf {
    class iParamFactory;
    typedef Map<std::string, iParamFactory*> FactoriesMap;
    /**
     * @brief Param creating singltone class.
     */
    class iParamFactory: public iDestroyable {
        private:
            static FactoriesMap factories;
        public:
            
            /* @brief Checks if string must be interpretated.
            */
            bool meaningful(std::string param_str) const;
            /* @brief Makes new param object by its name.
            */
            virtual iParam * makeParam (const std::string& name) const
                                throw (ConfLibraryException) = 0;
            
            /* @brief Bind new factory to the new filename. If already binded
             * exception is thrown.
             */
            static void registerParamFactory(const std::string& filename, 
                                        iParamFactory* const newParam) 
                                                    throw (AlreadyExistsException);
            /* @brief Makes new singletone param factory object by the
             * filename it will process.
             */
            static iParamFactory* const makeParamFactory (const std::string& filename)
                                throw (ConfLibraryException);
            /* @brief Delete all registered factories and clear storage
             */
            static void clearFactories() throw (ConfLibraryException);
    };
    
} //namespace conf
} //namespace xicor

#endif //_PARAM_FACTORY_H_
