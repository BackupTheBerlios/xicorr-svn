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
	
	typedef struct _LowLevelKeyInfo {
		int keycode;
		long state;
		_LowLevelKeyInfo()
			:keycode(0),state(0)
		{
		}
		_LowLevelKeyInfo (int _keycode, long _state)
			:keycode(_keycode), state(_state)
		{
		}
	} LowLevelKeyInfo;
	
	class xKey {
	private:
		char latinChar;
		KeySym key;
		KeySym modifier;
		xEncodingTable* encoding_table;
	public:
		xKey();
		xKey(KeySym key);
		xKey(KeySym key, KeySym modifier) throw(XlibException);
		
		bool isChar() throw(XlibException);
		bool isModified() throw(XlibException);
		
		char getChar() throw(XlibException);
		KeySym getKeysym() throw(XlibException);
		
		std::string getModifier() throw(XlibException);
		
		friend std::ostream& operator<< (std::ostream& out, xKey& l)
		{
			return out;
		}
	};
	
} //namespace xlib
} //namespace xicor

#endif //_XKEY_H_
