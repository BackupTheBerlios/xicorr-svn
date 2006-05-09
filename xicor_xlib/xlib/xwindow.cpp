#include "xwindow.h"
#include <iostream>

namespace xicor {
namespace xlib {

	xWindow::xWindow()
		:xclient(NULL),xwindow(0),
		border(0),background(0)
	{
		xclient = new xClient;
		xclient->connect();
	}
	
	xWindow::xWindow(ixClient* _xclient)
		:xclient(_xclient),xwindow(0),
		border(0),background(0)
	{}
	
	xWindow::xWindow(Window _xwindow, ixClient* _xclient)
		:xclient(_xclient),xwindow(_xwindow),
		border(0),background(0)
	{}
	
	xWindow::~xWindow()
	{
		delete xclient;
	}
	
	void xWindow::initICCCM() throw(XlibException)
	{
	}
	
	void xWindow::createWindow(std::string _name) throw(XlibException)
	{
		name = _name;
		if(!xclient->isAlive())
			xclient->connect();
		xwindow = XCreateSimpleWindow(xclient->getConnection(),
										xclient->getRootWindow(),
										geometry.position.x, geometry.position.y,
										geometry.width, geometry.height,
										geometry.border_width,
										border, background);
		if (xwindow <= 0)
			throw XlibException("Window creation failed");
		initICCCM();
	}
	
	void xWindow::destroyWindow() throw(XlibException)
	{
		if(xwindow > 0)
			XDestroyWindow(xclient->getConnection(), xwindow);
		xwindow = 0;
	}
	
	xWindow* xWindow::getGroupRootWindow() throw (XlibException)
	{
		Window child_window = xwindow, root_window, parent_window;
		Window window = xwindow;
		if(window <= 0)
			throw XlibException("Window has no parents: it is not created");
		Window *children_window_list;
		unsigned int nchildren;

		while (1) {
			if (!XQueryTree(xclient->getConnection(), window, &root_window,
			     &parent_window, &children_window_list, &nchildren))
				throw XlibException("Window parent's query failed");
			if (children_window_list)
				XFree (children_window_list);
			if (parent_window == root_window)
				break;
			else {
				child_window = window;
				window = parent_window;
			}
		}
		return new xWindow(child_window, new xClientDecorator(xclient));
	}
	
	Window xWindow::findChildByAtom (Window xWindow, Atom atom)
													throw (XlibException)
	{
		Atom type = None;
		int format;
		unsigned long nitems, after;
		unsigned char *data = NULL;
		Window tmp_window = 0, root_window, parent_window;
		Window *children_window_list;
		unsigned int nchildren;
		unsigned int i;
	
		if (xWindow <= 0)
			throw XlibException("Bad window");
	
		if (!XQueryTree (xclient->getConnection(), xWindow, &root_window,
					&parent_window, &children_window_list, &nchildren))
			throw XlibException("Children query failed");
		
		XGetWindowProperty (xclient->getConnection(),
							xWindow, atom,
							0, 0, False, AnyPropertyType, &type,
							&format, &nitems, &after, &data);
		if (data)
			XFree (data);
	
		if (type != None)
			return xWindow;

		for (i = 0; !tmp_window && (i < nchildren); i++) {
			data = NULL;
	
			XGetWindowProperty (xclient->getConnection(),
								children_window_list[i], atom,
								0, 0, False, AnyPropertyType, &type,
								&format, &nitems, &after, &data);
			if (data)
				XFree (data);
	
			if (type != None)
				tmp_window = children_window_list[i];
		}
	
		for (i = 0; !tmp_window && (i < nchildren); i++)
			tmp_window = findChildByAtom (children_window_list[i], atom);
	
		if (children_window_list)
			XFree (children_window_list);
	
		return tmp_window;
	}
	
	xWindow* xWindow::findChildByAtom (Atom atom) throw (XlibException)
	{
		Window res = 0;
		res = findChildByAtom(xwindow, atom);
		if (res <= 0)
			throw XlibException("No child window with such atom");
		return new xWindow(res,new xClientDecorator(xclient));
	}
	
	xWindow* xWindow::findChildByAtom (std::string atom_name)
												throw (XlibException)
	{
		Window res = 0;
		Atom atom = xclient->getAtom(atom_name);
		res = findChildByAtom (xwindow, atom);
		if (res <= 0)
			throw XlibException("No child window with atom name: " + atom_name);
		return new xWindow(res,new xClientDecorator(xclient));
	}
	
	std::string xWindow::getClass() const throw(XlibException)
	{
		XClassHint* wm_class = NULL;
		wm_class = XAllocClassHint ();
		if(!wm_class)
			throw XlibException("XClassHint allocation failed");

		if (!XGetClassHint (xclient->getConnection(), xwindow, wm_class)) {
			XFree (wm_class->res_class);
			XFree (wm_class->res_name);
			XFree (wm_class);
			throw XlibException("ClassHint query failed");
		}
		std::string res = wm_class->res_class;
		XFree (wm_class->res_class);
		XFree (wm_class->res_name);
		XFree (wm_class);
		return res;
	}
	
	std::string xWindow::getName() const throw(XlibException)
	{
		
		XClassHint* wm_class = NULL;
		wm_class = XAllocClassHint ();
		if(!wm_class)
			throw XlibException("XClassHint allocation failed");
		
		if (!XGetClassHint (xclient->getConnection(), xwindow, wm_class)) {
			XFree (wm_class->res_class);
			XFree (wm_class->res_name);
			XFree (wm_class);
			throw XlibException("ClassHint query failed");
		}
		std::string res = wm_class->res_name;
		XFree (wm_class->res_class);
		XFree (wm_class->res_name);
		XFree (wm_class);
		return res;
	}
	
	bool xWindow::hasLocallyActiveFocusModel() throw(XlibException)
	{
		bool res = false;
		XWMHints* wm_hints = NULL;
		
		wm_hints = XGetWMHints(xclient->getConnection(), xwindow);
		if (wm_hints) {
			res = wm_hints->input;
			XFree(wm_hints);
		}
		else
			throw XlibException("ClassHint query failed");
		return res;
	}
	
} //namespace xlib
} //namespace xicor
