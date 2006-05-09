#include "xicor_xlib.h"

#include "xlib/xlib_exception.h"

#include <iostream>
#include <sstream>

namespace xicor {
namespace xlib {

	static std::string xlib_message;
	static bool xlib_error = false;
	
	int handleXErrors (Display* xconnection, XErrorEvent * err_event)
	{
		xlib_error = true;
		char message[256];
		message[255] = 0;
		XGetErrorText(err_event->display, err_event->error_code, message, 255);
		std::string str;
		std::ostringstream stream(str);
		stream << "Request Code: " << (int)err_event->request_code << '\n'
			<< "Error Code: " << (int)err_event->error_code << '\n'
			<< "Minor Code: " << (int)err_event->minor_code << '\n'
			<< "Error Message: " << message << std::endl;
		xlib_message = stream.str();
		
		std::cout << "Xlib Routine Error:" << std::endl
			<< xlib_message << std::endl;
		//throw XlibException("Xlib:\n " + xlib_message);
		
		return False;
	}
	
	void initLibrary()
	{
		XSetErrorHandler(handleXErrors);
	}

	bool haveLibraryError()
	{
		bool res = xlib_error;
		xlib_error = false;
		return res;
	}
	
	std::string getLibraryError()
	{
		std::string res = xlib_message;
		xlib_message = "";
		return res;
	}
	
} //namespace xlib
} //namespace xicor
