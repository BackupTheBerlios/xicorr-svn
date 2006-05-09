#ifndef _FOCUS_CHANGE_OBSERVER_H_
#define _FOCUS_CHANGE_OBSERVER_H_

#include "xlib/xevent.h"

namespace xicor {
	namespace plugins {
		class iComDataStorage;
		
		namespace xsystem {
			class WindowManager;
		}
	}
	namespace xlib {
		class xClient;
	}
}

namespace xicor {
namespace plugins {
namespace xsystem {

	class FocusChangeObserver: public xicor::xlib::ixEventObserver {
		private:
			xicor::xlib::xClient* xclient;
			WindowManager* win_manager;
			iComDataStorage* comdata;
		public:
			FocusChangeObserver();
			
			void init(xicor::xlib::xClient* const _xclient,
						WindowManager* const _win_manager,
						iComDataStorage* const _comdata);
			
			void prepare ();
			
			void updateObserved (const xicor::xlib::xEvent* const observed)
												throw (xicor::xlib::XlibException);
	};

} //namespace xsystem
} //namespace plugins
} //namespace xicor

#endif //_FOCUS_CHANGE_OBSERVER_H_
