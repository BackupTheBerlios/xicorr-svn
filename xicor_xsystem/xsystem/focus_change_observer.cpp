#include "focus_change_observer.h"

#include "plugin_library/com_data_storage.h"

#include "xlib/xclient.h"
#include "xlib/xwindow.h"
#include "window_manager.h"
#include <iostream>

namespace xicor {
namespace plugins {
namespace xsystem {
    
    FocusChangeObserver::FocusChangeObserver()
        :xclient(NULL),
        win_manager(NULL),
        comdata(NULL)
    {}
            
    void FocusChangeObserver::init(xicor::xlib::xClient* const _xclient,
                WindowManager* const _win_manager,
                iComDataStorage* const _comdata)
    {
        xclient = _xclient;
        win_manager = _win_manager;
        comdata = _comdata;
    }
    
    void FocusChangeObserver::prepare ()
    {
        comdata->setString("current_event", "");
    }
            
    void FocusChangeObserver::updateObserved (const xicor::xlib::xEvent* const observed)
                                                throw (xicor::xlib::XlibException)
    {
        try {
            comdata->setString("current_event", "focus");
    
            if (observed->getFocus().isOut()) {
                xicor::xlib::xWindow* app = new xicor::xlib::xWindow(xclient->getInputFocus(), 
                                                            new xicor::xlib::xClientDecorator(xclient));
                if(app->getID() == xclient->getRootWindow())
                    return;
    
                WinInfo info = win_manager->addNewClient(app);
    
                comdata->setString("current_app_name", info.name);
                comdata->setInt32("current_app_id", info.ID);
            }
        }
        catch (Exception& ex) {
            throw xicor::xlib::XlibException(ex);
        }
    }
    
} //namespace xsystem
} //namespace plugins
} //namespace xicor
