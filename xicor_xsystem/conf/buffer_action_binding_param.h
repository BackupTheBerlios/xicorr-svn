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
    
    typedef struct Bind {
        const KeySym key;
        const KeySym modifier;
        const std::string mode;
        Bind()
            :key(None),modifier(None),mode("")
        {}
        Bind(const KeySym& _key, 
             const KeySym& _modifier, 
             const std::string& _mode)
            :key(_key),modifier(_modifier),mode(_mode)
        {}

        bool operator<(const Bind& b) const
        {
            return (key < b.key) ||
                   (key == b.key && modifier < b.modifier) ||
                   (key == b.key && modifier == b.modifier && mode < b.mode);
        }
        friend std::ostream& operator<< (std::ostream& out, const Bind& b)
        {
            out << std::endl << b.key << " " 
                << b.modifier << " " 
                << b.mode << std::endl;
            return out;
        }
    };
    typedef Map<Bind, std::string> BindMap;
    
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
                std::string::operator=("buffer_action_binding");
                std::istringstream stream(_value);
                std::string key, modifier, mode;;
                    
                stream >> action;
                stream >> key;
                stream >> modifier;
                stream >> mode;

                if (action != "AddSymbol" &&
                    action != "ReplaceSymbol" &&
                    action != "DelCurSymbol" &&
                    action != "DelPrevSymbol" &&
                    action != "ClearWord" &&
                    action != "ClearBuffer" &&
                    action != "NavLeft" &&
                    action != "NavRight")
                    THROW(ConfLibraryException, "Action param can't get " + action);
                
                if (key == "AllSymbolic")
                    keys = xicor::xlib::getAllSymbolic();
                else if (key == "AllUnbinded")
                    keys.insert(None);
                else
                    try {  
                        keys.insert(xicor::xlib::stringToKeysym(key));
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
                        modifiers.insert(xicor::xlib::stringToKeysym(modifier));
                    }
                    catch (const ObjectNotFoundException& ex) {
                        THROW(ConfLibraryException, "Modifier param can't get " + modifier);
                    }
                
                if (mode == "InsertMode" || mode == "ReplaceMode")
                    modes.insert(mode);
                else if (mode == "AllModes") {
                    modes.insert("InsertMode");
                    modes.insert("ReplaceMode");
                }
                else
                    THROW(ConfLibraryException, "Mode param can't get " + mode);
            }

            void fill(iConfiguration* conf) throw (ConfLibraryException)
            {
                KeySymSet::iterator key;
                for (key = keys.begin(); key != keys.end(); key++)
                {
                    KeySymSet::iterator modifier;
                    for (modifier = modifiers.begin(); 
                        modifier != modifiers.end(); modifier++)
                    {
                        StringSet::iterator mode;
                        for (mode = modes.begin(); mode != modes.end(); mode++)
                        {
                            Bind bind(*key, *modifier, *mode);
                            try {
                                BindMap& actions = conf->get<BindMap>(*this);
                                actions[bind] = action;
                            }
                            catch (const ObjectNotFoundException& ex) {
                                conf->set<BindMap>(*this, BindMap(bind, action));
                            }
                            catch (const Exception& ex) {
                                throw ConfLibraryException(ex);
                            }
                        }
                    }
                }
            }
    };
    
} //namespace conf
} //namespace xicor

#endif //_BUFFER_ACTION_BINDING_PARAM_H_
