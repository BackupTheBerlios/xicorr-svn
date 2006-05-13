#ifndef _XKEY_H_
#define _XKEY_H_

namespace xicor {
    namespace xlib {
        class xEncodingTable;
    }
}

#include "xlib_exception.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <string>

namespace xicor {
namespace xlib {
    
    class xLatin1Key {
    private:
        char latinChar;
        KeySym key;
        KeySym modifier;
        xEncodingTable* encoding_table;
    protected:
        void toLowerCaseIfUpper();
    public:
        xLatin1Key();
        xLatin1Key(char latinChar);
        xLatin1Key(KeySym key, KeySym modifier) throw(XlibException);
        xLatin1Key(XEvent* event) throw(XlibException);
        
        bool isChar() throw(XlibException);
        bool isModified() throw(XlibException);
        
        char getChar() throw(XlibException);
        KeySym getKeysym() throw(XlibException);
        
        KeySym getModifier() throw(XlibException);
        
        friend std::ostream& operator<< (std::ostream& out, xLatin1Key& l)
        {
            return out;
        }
    };
    
} //namespace xlib
} //namespace xicor

#endif //_XKEY_H_
