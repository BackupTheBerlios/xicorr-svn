#ifndef _XICOR_XLIB_H_
#define _XICOR_XLIB_H_

#include <X11/Xlib.h>
#include <string>

namespace xicor {
namespace xlib {

	int handleXErrors (Display* xconnection, XErrorEvent * err_event);

	void initLibrary();
	
	bool haveLibraryError();
	
	std::string getLibraryError();
	
} //namespace xlib
} //namespace xicor

#endif //_XICOR_XLIB_H_
