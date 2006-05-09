#ifndef _XEVENT_H_
#define _XEVENT_H_

namespace xicor {
	namespace xlib {
		class xEvent;
		class xWindow;
	}
}

#include "xencoding_table.h"
#include <X11/Xlib.h>

#include "xkey.h"
#include "xfocus.h"
#include "observer.h"
#include "abstract_storage.h"

namespace xicor {
namespace xlib {
	
	static const long KEYBOARD_EVENT = KeyReleaseMask;
	static const long FOCUS_CHANGE_EVENT = FocusChangeMask;
	
	class ixEventObserver {
		public:
			virtual void updateObserved (const xEvent* const observed) 
															throw (XlibException) = 0;
	};
	
	class xEvent {
		private:
			std::map<long,ixEventObserver*> observers;
			AbstractDataStorage<long> observers_data;
			std::map<long,long> xlib_event2mask;
		public:
			xEvent();
			~xEvent();
			
			void processEvent(XEvent* event);
			const xKey& getKey() const throw(XlibException);
			const xFocus& getFocus() const throw(XlibException);
			
			void send(xWindow* xwin, xKey* xkey);
			
			void attachObserver(ixEventObserver* observer, long type) 
													throw(XlibException);
			void detachObserver(long type) throw(XlibException);
	};
	
} //namespace xlib
} //namespace xicor

#endif //_XEVENT_H_
