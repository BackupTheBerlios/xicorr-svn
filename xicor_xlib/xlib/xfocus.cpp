#include "xfocus.h"

namespace xicor {
namespace xlib {

xFocus::xFocus()
    :out(false)
{}

xFocus::xFocus(Window _owner,int32 _focus_policy, bool _out)
    :owner(_owner),focus_policy(_focus_policy),
    out(_out)
{}

xFocus::~xFocus()
{
}

void xFocus::updateInput(Display* xconnection) throw (XlibException)
{
    Window oldwin = owner;
    bool isSameScreen;
    int32 dummy;
    uint32 dummyU;
    Window rootW = 0, childW = 0;

    if (!xconnection)
        THROW(XlibException, "Bad display");

    XGetInputFocus (xconnection,&owner,&focus_policy);
    if (None == owner)
        THROW(XlibException, "Bad input focus owner");
    
    childW = owner;
    
    if ( focus_policy == RevertToPointerRoot  && oldwin != owner) {

        isSameScreen =
            XQueryPointer (xconnection, childW, &rootW, &childW, &dummy,
                       &dummy, &(dummy), &(dummy), &dummyU);
        if (isSameScreen == true) {
            while (childW != 0) {
                owner = childW;
                isSameScreen =
                    XQueryPointer (xconnection, childW, &rootW,
                                    &childW, &dummy, &dummy, &(dummy),
                                    &(dummy), &dummyU);
            }
        }
    }
    
}

} //namespace xlib
} //namespace xicor
