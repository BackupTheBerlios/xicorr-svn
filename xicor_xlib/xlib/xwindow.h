#ifndef _XWINDOW_H_
#define _XWINDOW_H_

#include "xclient.h"

namespace xicor {
namespace xlib {
    
    typedef struct __Point2D{
        int32 x;
        int32 y;
        
        __Point2D(int32 _x = 0, int32 _y = 0)
            :x(_x),y(_y)
        {}
    } Point2D;
    
    typedef struct __WindowGeometry{
        Point2D position;
        uint32 width;
        uint32 height;
        uint32 border_width;
        
        __WindowGeometry(Point2D _position = Point2D(),
                        uint32 _width = 1, uint32 _height = 1,
                        uint32 _border_width = 0)
            :position(_position),width(_width),height(_height),
            border_width(_border_width)
        {}
    } WindowGeometry;
    
    class xWindow {
    protected:
        ixClient* xclient;
    private:
        Window xwindow;
        std::string name;
        WindowGeometry geometry;
        unsigned long border;
        unsigned long background;
    protected:
        virtual void initICCCM() throw(XlibException);
        Window findChildByAtom (Window xwindow, Atom atom)
                                                throw (XlibException);
    public:
        xWindow();
        xWindow(ixClient* xclient);
        xWindow(Window xwindow, ixClient* xclient);
        virtual ~xWindow();
        
        void createWindow(std::string name) throw (XlibException);
        void destroyWindow() throw(XlibException);
        
        ixClient* getClient() const
        {
            return xclient;
        }
        Window getID() const
        {
            return xwindow;
        }
        xWindow* getGroupRootWindow() throw (XlibException);
        xWindow* findChildByAtom (Atom atom) throw (XlibException);
        xWindow* findChildByAtom (std::string atom_name)
                                                throw (XlibException);
        
        std::string getClass() const throw(XlibException);
        std::string getName() const throw(XlibException);
        
        bool hasLocallyActiveFocusModel() throw(XlibException);
    };

} //namespace xlib
} //namespace xicor

#endif //_XWINDOW_H_
