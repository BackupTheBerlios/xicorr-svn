#ifndef _XENCODING_TABLE_H_
#define _XENCODING_TABLE_H_

#include <X11/Xlib.h>
#include <map>

#include "xlib_exception.h"

namespace xicor {
namespace xlib {

    typedef std::map<KeySym,KeySym> DecodingTable;
    
    class xEncodingTable {
    private:
        static xEncodingTable* instance;
    protected:      
        xEncodingTable();
        virtual ~xEncodingTable();
    public:
        static xEncodingTable* makeObject();
        
        char getSpecialCharFromKeysym(KeySym keysym) throw (XlibException);
        KeySym getKeysymFromSpecialChar(char c) throw (XlibException);
    };
    
} //namespace xlib
} //namespace xicor

#endif //_XENCODING_TABLE_H_
