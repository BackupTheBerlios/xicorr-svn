#include "keyboard_observer.h"
#include "xlib/xkey.h"
#include "plugin_library/com_data_storage.h"
#include <iostream>

namespace xicor {
namespace plugins {
namespace xsystem {

    KeyboardObserver::KeyboardObserver()
        :comdata(NULL)
    {
    }
                
    void KeyboardObserver::init (iComDataStorage* const _comdata)
    {
        comdata = _comdata;
        comdata->setString("current_input", "");
        comdata->set<KeyBufferMap>("key_buffer_map", KeyBufferMap());
    }
    
    void KeyboardObserver::prepare ()
    {
        comdata->setString("current_event", "");
        comdata->setString("current_output", "");
        comdata->set<bool>("output_enable", false);
    }
    
    void KeyboardObserver::updateObserved (const xicor::xlib::xEvent* const observed)
                                                throw (xicor::xlib::XlibException)
    {
        try {
            comdata->getString("current_event") = "key";
            xicor::xlib::xLatin1Key xkey = observed->getKey();
            if (xkey.isChar()) {
                KeyBufferMap& buffers = comdata->get<KeyBufferMap>("key_buffer_map");
                std::string& input = buffers[comdata->getInt32("current_app_id")];
                input += xkey.getChar();
                comdata->getString("current_input") = input;
                comdata->get<bool>("output_enable") = true;
            }   
        }
        catch (Exception& ex) {
            throw xicor::xlib::XlibException(ex);
        }           
    }

} //namespace xsystem
} //namespace plugins
} //namespace xicor
