#ifndef _KEYBOARD_OBSERVER_H_
#define _KEYBOARD_OBSERVER_H_

namespace xicor {
	namespace plugins {
		class iComDataStorage;
	}
}

#include "xlib/xevent.h"
#include "stl_ext.h"
#include <string>

namespace xicor {
namespace plugins {
namespace xsystem {
	
	typedef Map<int, std::string> KeyBufferMap;
	class KeyboardObserver: public xicor::xlib::ixEventObserver {
		private:
			iComDataStorage* comdata;
		public:
			KeyboardObserver();
			
			void init (iComDataStorage* const _comdata);
			
			void prepare ();
			
			void updateObserved (const xicor::xlib::xEvent* const observed)
													throw (xicor::xlib::XlibException);
	};
	
} //namespace xsystem
} //namespace plugins
} //namespace xicor

#endif //_KEYBOARD_OBSERVER_H_
