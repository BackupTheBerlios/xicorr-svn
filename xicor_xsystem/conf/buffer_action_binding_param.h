#ifndef _BUFFER_ACTION_BINDING_PARAM_H_
#define _BUFFER_ACTION_BINDING_PARAM_H_

#include "conf_library/param_impl.h"
#include "stl_ext.h"
#include "conf_library/configuration.h"

#include "xlib/utils.h"

#include <sstream>

namespace xicor {
namespace conf {
    
    typedef Set<KeySym> KeySymSet;
    typedef Set<std::string> StringSet;
    typedef struct __Bind {
        KeySymSet keys;
        KeySymSet modifiers;
        StringSet modes;
        __Bind()
        {}
        __Bind(const KeySymSet& _keys, 
               const KeySymSet& _modifiers, 
               const StringSet& _modes)
            :keys(_keys),modifiers(_modifiers),modes(_modes)
        {}
        bool operator<(const __Bind& b) const
        {
            return keys < b.keys &&
                    modifiers < b.modifiers &&
                    modes < b.modes;
        }
        friend std::ostream& operator<< (std::ostream& out, __Bind& b)
        {
            out << std::endl << b.keys << " " 
                << b.modifiers << " " 
                << b.modes << std::endl;
            return out;
        }
    } Bind;
    typedef Map<std::string, Bind> BindMap;
    
    class BufferActionBindingParam: public ParamImpl {
        private:
            std::string action;
            KeySymSet keys;
            KeySymSet modifiers;
            StringSet modes;
        public:
            BufferActionBindingParam(const std::string& _value)
                                       throw (ConfLibraryException)
            {
                std::string::operator=("BufferActionBinding");
                std::istringstream stream(_value);
                std::string key, modifier, mode;
                KeySym key_ks, modifier_ks;
                    
                stream >> action;
                stream >> key;
                stream >> modifier;
                stream >> mode;

                if (action != "AddSymbol" &&
                    action != "ReplaceSymbol" &&
                    action != "DelCurSymbol" &&
                    action != "DelPrevSymbol" &&
                    action != "ClearBuffer")
                    THROW(ConfLibraryException, "Action param can't get " + action);
                
                if (key == "AllSymbolic")
                    keys = xicor::xlib::getAllSymbolic();
                else if (key == "AllUnbinded")
                    ;
                else
                    try {  
                        key_ks = xicor::xlib::stringToKeysym(key);
                    }
                    catch (const ObjectNotFoundException& ex) {
                        THROW(ConfLibraryException, "Key param can't get " + key);
                    }
                
                if (modifier == "AllModifiers") {
                    modifiers = xicor::xlib::getAllModifiers();
                    modifiers.insert(None);
                }
                else if (modifier == "None")
                    modifiers.insert(None);
                else
                    try {  
                        modifier_ks = xicor::xlib::stringToKeysym(modifier);
                    }
                    catch (const ObjectNotFoundException& ex) {
                        THROW(ConfLibraryException, "Modifier param can't get " + modifier);
                    }
                
                if (mode == "InsertMode")
                    modes.insert("InsertMode");
                else if (mode == "ReplaceMode")
                    modes.insert("ReplaceMode");
                else if (mode == "AllModes") {
                    modes.insert("InsertMode");
                    modes.insert("ReplaceMode");
                }
                else
                    THROW(ConfLibraryException, "Mode param can't get " + mode);
            }

            void fill(iConfiguration* conf) throw (ConfLibraryException)
            {
                Bind bind = Bind(keys, modifiers, modes);
                try {
                    BindMap& binds = conf->get<BindMap>(*this);
                    binds[action] = bind;
                }
                catch (const ObjectNotFoundException& ex) {
                    conf->set<BindMap>(*this, BindMap(action, bind));
                }
                catch (const Exception& ex) {
                    throw ConfLibraryException(ex);
                }
            }
    };
    
} //namespace conf
} //namespace xicor

#endif //_BUFFER_ACTION_BINDING_PARAM_H_
