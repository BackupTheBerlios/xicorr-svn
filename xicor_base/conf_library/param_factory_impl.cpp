#include "param_factory.h"
#include "exception.h"

#include <sstream>

namespace xicor {
namespace conf {
    
    FactoriesMap iParamFactory::factories = FactoriesMap();

    bool iParamFactory::meaningful(std::string param_str) const
    {
        std::istringstream str_stream(param_str);
        std::string tmp;
        str_stream >> tmp;
        if (tmp[0] == '#' || tmp.empty()) {
            return false;
        }
        return true;
    }
    
    void iParamFactory::registerParamFactory(const std::string& filename, 
                                        iParamFactory* const newParam) 
                                                    throw (AlreadyExistsException)
    {
        factories.addNewValue(filename, newParam);
    }
    
    iParamFactory* const iParamFactory::makeParamFactory (const std::string& filename)
                                    throw (ConfLibraryException)
    {
        try {
            return factories.tryKey(filename);
        }
        catch (const ObjectNotFoundException& ex) {
            throw ConfLibraryException(ex);
        }
    }
    
    void iParamFactory::clearFactories() throw (ConfLibraryException)
    {
        FactoriesMap::iterator itr;
        for (itr = factories.begin(); itr != factories.end(); itr++)
            delete itr->second;
        factories.clear();
    }

} //namespace conf
} //namespace xicor
