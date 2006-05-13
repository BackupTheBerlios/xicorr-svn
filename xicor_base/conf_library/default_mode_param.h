#ifndef _DEFAULT_MODE_PARAM_H_
#define _DEFAULT_MODE_PARAM_H_

#include "param_impl.h"
#include "configuration.h"

namespace xicor {
namespace conf {
    
    class DefaultModeParam: public ParamImpl {
        private:
            std::string value;
        public:
            DefaultModeParam(std::string _value) throw (ConfLibraryException)
            {
                std::string::operator=("DefaultMode");
                if (_value != "Manual" && _value != "Auto")
                    THROW(ConfLibraryException, *this + " can't take " + _value);
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

#endif //_DEFAULT_MODE_PARAM_H_
