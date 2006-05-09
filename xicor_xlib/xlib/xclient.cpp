#include "xicor_xlib.h"
#include "xclient.h"
#include "xevent.h"

namespace xicor {
namespace xlib {
	
	xClient::xClient()
		:xconnection(NULL),xscreen(NULL),root_xwindow(0),desktop(0)
	{
		initLibrary();
	}
	
	xClient::~xClient() throw(XlibException)
	{
		disconnect();
	}
	
	Display* const xClient::getConnection() const throw(XlibException)
	{
		return xconnection;
	}
	
	Window xClient::getRootWindow() const throw(XlibException)
	{
		return root_xwindow;
	}
	
	int xClient::getDesktopID() const throw(XlibException)
	{
		return desktop;
	}
	
	bool xClient::isAlive() const throw(XlibException)
	{
		if (xconnection)
			return true;
		return false;
	}
	
	void xClient::connect(std::string address)
										throw(XlibException)
	{
		xconnection = XOpenDisplay(address.c_str());
		if (!xconnection)
			throw XlibException("Connection to X Server (" + 
												address + ") failed");
		xscreen = DefaultScreenOfDisplay(xconnection);
		desktop = DefaultScreen(xconnection);
		root_xwindow = DefaultRootWindow(xconnection);
		atom_storage.setConnection(xconnection);
	}
	
	void xClient::disconnect() throw(XlibException)
	{
		if (xconnection)
			XCloseDisplay(xconnection);
		xconnection = NULL;
	}
	
	void xClient::recieveEvent() throw(XlibException)
	{
		XEvent event;
		XNextEvent(xconnection, &event);
		xevent.processEvent(&event);
	}
	
	void xClient::setMonitoringOn(Window xwindow, long event_type) throw(XlibException)
	{
		XSelectInput(xconnection, xwindow, event_type);
	}
	
	void xClient::attachEventObserver(ixEventObserver* observer,
											long type) throw(XlibException)
	{
		xevent.attachObserver(observer, type);
	}
	
	void xClient::detachEventObserver(long type) throw(XlibException)
	{
		xevent.detachObserver(type);
	}
	
	void xClient::setMonitoringOff(Window xwindow) throw(XlibException)
	{
		XSelectInput(xconnection, xwindow, None);
	}
	
	Window xClient::getInputFocus() throw(XlibException)
	{
		xifocus.updateInput(xconnection);
		return xifocus.getOwner();
	}
	
	bool xClient::isFocusMoved() throw(XlibException)
	{
		//TODO.DUMMY. To delete
		return false;
	}

} //namespace xlib
} //namespace xicor
