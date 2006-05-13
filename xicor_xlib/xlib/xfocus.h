#ifndef _XINPUT_FOCUS_H_
#define _XINPUT_FOCUS_H_

#include <X11/Xlib.h>
#include "xlib_exception.h"

namespace xicor {
namespace xlib {

    class xFocus {
    private:
        Window owner;
        int32 focus_policy;
        bool out;
    public:
        xFocus();
        xFocus(Window owner,int32 focus_policy, bool out);
        virtual ~xFocus();
        
        Window getOwner() const
        {
            return owner;
        }
        
        bool isOut() const
        {
            return out;
        }
        
        void updateInput(Display* xconnection) throw(XlibException);
        
        friend std::ostream& operator<< (std::ostream& out, xFocus& l)
        {
            return out;
        }
    };

} //namespace xlib
} //namespace xicor

#endif //_XINPUT_FOCUS_H_
