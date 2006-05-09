#ifndef _MY_XLIB_H_
#define _MY_XLIB_H_

namespace xicor {
	namespace xlib {
		class ixEventObserver;
		class xEvent;
	}
}

#include "xlib_exception.h"

#include <X11/Xlib.h>
#include <X11/Xmu/Atoms.h>

#include <string>

namespace xicor {
namespace xlib {

	class iAtomStorage {
		public:
			virtual ~iAtomStorage() throw(XlibException) {}
		
			virtual Atom getAtom(std::string name) throw (XlibException) = 0;
			virtual Atom setAtom(std::string name) throw (XlibException) = 0;
			virtual std::string getAtomName(Atom atom) throw (XlibException) = 0;
	};
	
	static const std::string DEFAULT_XSERVER_ADDRESS = ":0";
	
	class ixClient: public iAtomStorage {
		protected:
			friend class xClientDecorator;
			virtual ixClient* getOrigin() throw(XlibException) {return this;}
		public:
			virtual ~ixClient() throw(XlibException) {}
			
			virtual Display* const getConnection() const
									throw(XlibException) = 0;
			virtual xEvent* getEvent() throw(XlibException) = 0;
			virtual Window getRootWindow() const throw(XlibException) = 0;
			virtual int getDesktopID() const throw(XlibException) = 0;
			virtual bool isAlive() const throw(XlibException) = 0;
			virtual void connect(std::string address =
										DEFAULT_XSERVER_ADDRESS )
										throw(XlibException) = 0;
			virtual void disconnect() throw(XlibException) = 0;
			virtual void recieveEvent() throw(XlibException) = 0;
			virtual void setMonitoringOn(Window xwindow, long event_type)
																throw(XlibException) = 0;
			virtual void setMonitoringOff(Window xwindow) throw(XlibException) = 0;
			
			virtual Window getInputFocus() throw(XlibException) = 0;
			virtual bool isFocusMoved() throw(XlibException) = 0;
			
			virtual void attachEventObserver(ixEventObserver* observer,
												long type) throw(XlibException) = 0;
	
			virtual void detachEventObserver(long type) throw(XlibException) = 0;
	};
	
} //namespace xlib
} //namespace xicor

#endif //_MY_XLIB_H_
