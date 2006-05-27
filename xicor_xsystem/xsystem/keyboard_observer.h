#ifndef _KEYBOARD_OBSERVER_H_
#define _KEYBOARD_OBSERVER_H_

namespace xicor {
    namespace plugins {
        class iComDataStorage;
    }
    namespace conf {
        class iConfiguration;
    }
}

#include "xlib/xevent.h"
#include "key_buffer.h"
#include <string>

namespace xicor {
namespace plugins {
namespace xsystem {
    
    typedef Map<int, std::string> KeyBufferMap;
    class KeyboardObserver: public xicor::xlib::ixEventObserver {
        private:
            iComDataStorage* comdata;
            xicor::conf::iConfiguration* conf;
            KeyBuffer keyBuffer;
            std::string mode;
        public:
            KeyboardObserver();
            
            void init (iComDataStorage* const _comdata,
                        xicor::conf::iConfiguration* const _conf);
            
            void prepare ();
            
            void updateObserved (const xicor::xlib::xEvent* const observed)
                                                    throw (Exception,
                                                            xicor::xlib::XlibException);
    };
    
} //namespace xsystem
} //namespace plugins
} //namespace xicor

#endif //_KEYBOARD_OBSERVER_H_
