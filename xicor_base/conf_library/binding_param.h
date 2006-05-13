#ifndef _BINDING_PARAM_H_
#define _BINDING_PARAM_H_

#include "param_impl.h"
#include "configuration.h"

#include <sstream>

namespace xicor {
namespace conf {
    
    class BindingParam: public ParamImpl {
        private:
            std::string action;
            std::string key;
            std::string modifier;
        public:
            BindingParam(std::string _value) throw (ConfLibraryException)
            {
                std::string::operator=("BindingParam");
                
                std::istringstream value_stream(_value);
                value_stream >> action >> key >> modifier;
                if (action != "WordChange" && action != "LineChange"
                    && action != "SelectionChange" && action != "ModeSwitch")
                    THROW(ConfLibraryException, "Binding action can't be " + action);
                if (key != "Pause/Break" && key != "ScrollLock" && key != "PtrScr/SysRq")
                    THROW(ConfLibraryException, "Binding key can't be " + key);
                if (modifier != "Ctrl" && modifier != "None")
                    THROW(ConfLibraryException, "Binding modifier can't be " + modifier);
            }
            
            void fill(iConfiguration* conf) throw (ConfLibraryException)
            {
                std::string value = action + " " + key + " " + modifier + " ";
                try {
                    List<std::string>& bindings_list = 
                                    conf->getStringList(*this);
                    bindings_list.push_back(value);
                }
                catch (const ObjectNotFoundException& ex) {
                    conf->setStringList(*this, List<std::string>(value));
                }
                catch (const Exception& ex) {
                    throw ConfLibraryException(ex);
                }
            }
    };
    
} //namespace conf
} //namespace xicor

#endif //_BINDING_PARAM_H_
