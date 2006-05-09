#ifndef _XCLIENT_H_
#define _XCLIENT_H_

#include "atom_storage.h"
#include "xevent.h"
#include "xfocus.h"
#include "xlib_exception.h"

namespace xicor {
namespace xlib {
	
	class xClient: public ixClient {
	private:
		AtomStorage atom_storage;
		Display* xconnection;
		Screen* xscreen;
		Window root_xwindow;
		int desktop;
		xEvent xevent;
		xFocus xifocus;
	public:
		xClient();
		~xClient() throw(XlibException);
		
		Display* const getConnection() const throw(XlibException);
		Window getRootWindow() const throw(XlibException);
		int getDesktopID() const throw(XlibException);
		bool isAlive() const throw(XlibException);
		void connect(std::string address =
									DEFAULT_XSERVER_ADDRESS ) throw(XlibException);
		void disconnect() throw(XlibException);
		void recieveEvent() throw(XlibException);
		void setMonitoringOn(Window xwindow, long event_type) throw(XlibException);
		void setMonitoringOff(Window xwindow) throw(XlibException);
		
		xEvent* getEvent() throw(XlibException)
		{
			return &xevent;
		}
		
		Window getInputFocus() throw(XlibException);
		bool isFocusMoved() throw(XlibException);
		
		void attachEventObserver(ixEventObserver* observer,
											long type) throw(XlibException);
	
		void detachEventObserver(long type) throw(XlibException);
		
		Atom getAtom(std::string name) throw (XlibException)
		{
			return atom_storage.getAtom(name);
		}
		
		Atom setAtom(std::string name) throw (XlibException)
		{
			return atom_storage.setAtom(name);
		}
		
		std::string getAtomName(Atom atom) throw (XlibException)
		{
			return atom_storage.getAtomName(atom);
		}
	};

	class xClientDecorator: public ixClient {
	private:
		ixClient* decorated;
	protected:
		ixClient* getOrigin() throw(XlibException)
		{
			return decorated;
		}
	public:
		xClientDecorator(ixClient* _decorated)
		{
			decorated = _decorated->getOrigin();
		}
		
		~xClientDecorator() throw(XlibException)
		{}
		
		Display* const getConnection() const throw(XlibException)
		{
			return decorated->getConnection();
		}
		
		Window getRootWindow() const throw(XlibException)
		{
			return decorated->getRootWindow();
		}
		
		xEvent* getEvent() throw(XlibException)
		{
			return decorated->getEvent();
		}
		
		int getDesktopID() const throw(XlibException)
		{
			return decorated->getDesktopID();
		}
		
		bool isAlive() const throw(XlibException)
		{
			return decorated->isAlive();
		}
		
		void connect(std::string address =
									DEFAULT_XSERVER_ADDRESS ) throw(XlibException)
		{}
		
		Window getInputFocus() throw(XlibException)
		{
			return decorated->getInputFocus();
		}
		
		void disconnect() throw(XlibException)
		{}
		
		void recieveEvent() throw(XlibException)
		{
			decorated->recieveEvent();
		}
		
		void setMonitoringOn(Window xwindow, long event_type) throw(XlibException)
		{
			decorated->setMonitoringOn(xwindow,event_type);
		}
		
		void setMonitoringOff(Window xwindow) throw(XlibException)
		{
			decorated->setMonitoringOff(xwindow);
		}
		
		bool isFocusMoved() throw(XlibException)
		{
			return decorated->isFocusMoved();
		}
		
		void attachEventObserver(ixEventObserver* observer,
											long type) throw(XlibException)
		{
			decorated->attachEventObserver(observer, type);
		}
	
		void detachEventObserver(long type) throw(XlibException)
		{
			decorated->detachEventObserver(type);
		}
		
		Atom getAtom(std::string name) throw (XlibException)
		{
			return decorated->getAtom(name);
		}
		
		Atom setAtom(std::string name) throw (XlibException)
		{
			return decorated->setAtom(name);
		}
		
		std::string getAtomName(Atom atom) throw (XlibException)
		{
			return decorated->getAtomName(atom);
		}
	};
	
} //namespace xlib
} //namespace xicor

#endif //_XCLIENT_H_
