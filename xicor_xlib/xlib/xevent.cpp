#include "xevent.h"
#include "xwindow.h"
#include "xclient.h"

#include <X11/Xutil.h>
#include <X11/keysym.h>

namespace xicor {
namespace xlib {
    
    xEvent::xEvent()
    {
        xlib_event2mask[KeyRelease] = KEYBOARD_EVENT;
        xlib_event2mask[KeyPress] = KEYBOARD_EVENT;
        xlib_event2mask[FocusIn] = FOCUS_CHANGE_EVENT;
        xlib_event2mask[FocusOut] = FOCUS_CHANGE_EVENT;
        
        observers_data.set<xLatin1Key>(KEYBOARD_EVENT, xLatin1Key());
        observers_data.set<xFocus>(FOCUS_CHANGE_EVENT, xFocus());
    }
    
    xEvent::~xEvent()
    {
    }
    
    bool xEvent::processEvent(XEvent* event)
    {
        //TODO
        switch (xlib_event2mask[event->type])
        {
            case KEYBOARD_EVENT:
                if (event->xkey.send_event == False) {
                    observers_data.set<xLatin1Key>(KEYBOARD_EVENT, 
                                            xLatin1Key(event) );
                }
                else
                    return false;
            break;
            case FOCUS_CHANGE_EVENT:
                bool out = false;
                if (event->type == FocusOut)
                    out = true;
                observers_data.set<xFocus>(FOCUS_CHANGE_EVENT, 
                                            xFocus(event->xfocus.window,
                                                    event->xfocus.mode,out) );
            break;
        }
        observers[xlib_event2mask[event->type]]->updateObserved(this);
        return true;
    }
    
    void xEvent::send(xWindow* xwin, xLatin1Key* xkey)
    {
        Status err;
        ixClient* client = xwin->getClient();
        if (!client)
            THROW(XlibException, "Bad client");
    
        XEvent event;
        event.type = KeyPress;
        event.xkey.type = KeyPress;
        event.xkey.window = xwin->getID();
        event.xkey.root = client->getRootWindow();
        event.xkey.subwindow = None;
        event.xkey.same_screen = True;
        event.xkey.send_event = True;
        event.xkey.display = client->getConnection();
        if (xkey->getModifier() == XK_Shift_R)
            event.xkey.state = ShiftMask;
        else
            event.xkey.state = 0;
        event.xkey.keycode = XKeysymToKeycode(event.xkey.display, xkey->getKeysym());
        event.xkey.time = CurrentTime;
    
        err = XSendEvent (event.xkey.display, event.xkey.window,
                  true, KeyPressMask, &event);
        if (err) {
            event.type = KeyRelease;
            event.xkey.type = KeyRelease;
    
            err = XSendEvent (event.xkey.display, event.xkey.window, 
                                true, KeyReleaseMask, &event);
        }
        else
            THROW(XlibException, "XKeyEvent sending failed");
    }
    
    const xLatin1Key& xEvent::getKey() const throw(XlibException)
    {
        return observers_data.get<xLatin1Key>(KEYBOARD_EVENT);
    }
    
    const xFocus& xEvent::getFocus() const throw(XlibException)
    {
        return observers_data.get<xFocus>(FOCUS_CHANGE_EVENT);
    }
            
    void xEvent::attachObserver(ixEventObserver* observer, long type)
                                                    throw(XlibException)
    {
        if (!observer)
            THROW(XlibException, "Bad event observer ptr");
        observers[type] = observer;
    }
    
    void xEvent::detachObserver(long type) throw(XlibException)
    {
        observers[type] = NULL;
    }
    
} //namespace xlib
} //namespace xicor
