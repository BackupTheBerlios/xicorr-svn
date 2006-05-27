#ifndef _BINDING_PARAM_H_
#define _BINDING_PARAM_H_

#include "param_impl.h"
#include "configuration.h"

#include "xlib/utils.h"

#include <sstream>

namespace xicor {
namespace conf {
    
    typedef struct BasicBind {
        KeySym key;
        KeySym modifier;
        BasicBind()
            :key(None),modifier(None)
        {}
        BasicBind(const KeySym& _key, 
                const KeySym& _modifier)
            :key(_key),modifier(_modifier)
        {}

        bool operator<(const BasicBind& b) const
        {
            return (key < b.key) ||
                   (key == b.key && modifier < b.modifier);
        }
        
        friend std::ostream& operator<< (std::ostream& out, const BasicBind& b)
        {
            out << std::endl << b.key << " " 
                << b.modifier << std::endl;
            return out;
        }
    };
    
    typedef Map<BasicBind, std::string> BasicBindMap;
    
    class BindingParam: public ParamImpl {
        private:
            std::string action;
            BasicBind bind;
        public:
            BindingParam(std::string _value) throw (ConfLibraryException)
            {
                std::string::operator=("BindingActions");
                
                std::istringstream value_stream(_value);
                std::string key, modifier;
                value_stream >> action >> key >> modifier;
                if (action != "WordChange" && action != "LineChange"
                    && action != "SelectionChange" && action != "ModeSwitch")
                    THROW(ConfLibraryException, "Binding action can't be " + action);
                
                try {  
                    bind.key = xicor::xlib::stringToKeysym(key);
                }
                catch (const ObjectNotFoundException& ex) {
                    THROW(ConfLibraryException, "Key param can't get " + key);
                }
                
                if (modifier == "None")
                    bind.modifier = None;
                else
                    try {  
                        bind.modifier = xicor::xlib::stringToKeysym(modifier);
                    }
                    catch (const ObjectNotFoundException& ex) {
                        THROW(ConfLibraryException, "Modifier param can't get " + modifier);
                    }
            }
            
            void fill(iConfiguration* conf) throw (ConfLibraryException)
            {
                try {
                    BasicBindMap& actions = 
                                    conf->get<BasicBindMap>(*this);
                    actions[bind] = action;
                }
                catch (const ObjectNotFoundException& ex) {
                    conf->set<BasicBindMap>(*this, BasicBindMap(bind, action));
                }
                catch (const Exception& ex) {
                    throw ConfLibraryException(ex);
                }
            }
    };
    
} //namespace conf
} //namespace xicor

#endif //_BINDING_PARAM_H_
