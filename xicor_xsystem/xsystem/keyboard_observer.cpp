#include "keyboard_observer.h"
#include "xlib/xkey.h"
#include "plugin_library/com_data_storage.h"
#include "../conf/buffer_action_binding_param.h"
#include "conf_library/binding_param.h"
#include <iostream>

using namespace xicor::conf;

namespace xicor {
namespace plugins {
namespace xsystem {

    KeyboardObserver::KeyboardObserver()
        :comdata(NULL),
        conf(NULL),
        mode("InsertMode")
    {
    }
                
    void KeyboardObserver::init (iComDataStorage* const _comdata,
                                 iConfiguration* const _conf)
    {
        comdata = _comdata;
        conf = _conf;
        comdata->setString("current_input", "");
        comdata->set<KeyBufferMap>("key_buffer_map", KeyBufferMap());
    }
    
    void KeyboardObserver::prepare ()
    {
        comdata->setString("current_binded_action", "");
        comdata->setString("current_event", "");
        comdata->setString("current_output", "");
        comdata->set<bool>("output_enable", false);
    }
    
    void KeyboardObserver::updateObserved (const xicor::xlib::xEvent* const observed)
                                                throw (Exception,
                                                        xicor::xlib::XlibException)
    {
        xicor::xlib::xLatin1Key xkey = observed->getKey();
        try {
            BasicBindMap& generalActions = conf->get<BasicBindMap>("BindingActions");
            
            if (xkey.getKey() == XK_Insert && 
                xkey.getModifier() == None) {
                if (mode == "InsertMode")
                    mode = "ReplaceMode";
                else
                    mode = "InsertMode";
                std::cout << "xsystem: new key input mode: " << mode << std::endl;
            }
            
            const std::string& gAction = 
                    generalActions.tryKey(BasicBind(xkey.getKey(), xkey.getModifier()));
            comdata->setString("current_binded_action", gAction);
            comdata->setString("current_event", "bind");
        }
        catch (const ObjectNotFoundException& ex) {
            comdata->getString("current_event") = "key";
            KeyBufferMap& buffers = comdata->get<KeyBufferMap>("key_buffer_map");
            std::string& input = buffers[comdata->getInt32("current_app_id")];
            BindMap& actions = conf->get<BindMap>("buffer_action_binding");
            
            Bind bind(xkey.getKey(), xkey.getModifier(), mode);
            
            try {
                keyBuffer.processAction(actions.tryKey(bind), xkey.getChar(), input);
            }
            catch (const Exception& ex) {
                Bind unbounded(None, xkey.getModifier(), mode);
                keyBuffer.processAction(actions.tryKey(unbounded), xkey.getChar(), input);
            }
            
            if (xkey.isChar()) {
                comdata->get<bool>("output_enable") = true;
                comdata->getString("current_input") = input;
            }
        }
        catch (const std::exception& ex) {
            throw Exception(ex.what());
        }        
    }

} //namespace xsystem
} //namespace plugins
} //namespace xicor
