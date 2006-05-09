#include "configuration_impl.h"

namespace xicor {
namespace conf {
    
    void ConfigurationImpl::serialize (std::ostream& out) const throw (Exception)
    {
        out << "Configuration serialization:" << std::endl;
		AbstractDataStorage<std::string>::serialize(out);
        out << "Serialization end" << std::endl;
    }
    
} //namespace conf
} //namespace xicor
