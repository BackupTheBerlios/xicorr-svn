#ifndef _VERBOSE_LEVEL_PARAM_H_
#define _VERBOSE_LEVEL_PARAM_H_

#include "param_impl.h"
#include "configuration.h"

namespace xicor {
namespace conf {
    
    class VerboseLevelParam: public ParamImpl {
        private:
            std::string value;
        public:
            VerboseLevelParam(std::string _value) throw (ConfLibraryException)
            {
                std::string::operator=("VerboseLevel");
                if (_value != "FullDebug" && _value != "LogDebug" 
                    && _value != "NoDebug")
                    THROW(ConfLibraryException, *this
                                                + " can't take "
                                                + _value);
                else
                    value = _value;
            }

            void fill(iConfiguration* conf) throw (ConfLibraryException)
            {
                conf->setString(*this, value);
            }
    };
    
} //namespace conf
} //namespace xicor

#endif //_VERBOSE_LEVEL_PARAM_H_
