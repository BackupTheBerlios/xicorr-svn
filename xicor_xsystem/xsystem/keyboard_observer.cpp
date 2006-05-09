#include "keyboard_observer.h"
#include "xlib/xkey.h"
#include "plugin_library/com_data_storage.h"
#include <iostream>

namespace xicor {
namespace plugins {
namespace xsystem {

	KeyboardObserver::KeyboardObserver()
		:comdata(NULL)
	{
	}
				
	void KeyboardObserver::init (iComDataStorage* const _comdata)
	{
		comdata = _comdata;
		comdata->set<std::string>("current_input", "");
		comdata->set<KeyBufferMap>("key_buffer_map", KeyBufferMap());
	}
	
	void KeyboardObserver::prepare ()
	{
		comdata->set<std::string>("current_event", "");
		comdata->set<std::string>("current_output", "");
	}
	
	void KeyboardObserver::updateObserved (const xicor::xlib::xEvent* const observed)
												throw (xicor::xlib::XlibException)
	{
		try {
			comdata->get<std::string>("current_event") = "key";
			xicor::xlib::xKey xkey = observed->getKey();
			if (xkey.isChar()) {
				KeyBufferMap& buffers = comdata->get<KeyBufferMap>("key_buffer_map");
				std::string& input = buffers[comdata->get<int>("current_app_id")];
				input += xkey.getChar();
				comdata->get<std::string>("current_input") = input;
			}
		}
		catch (Exception& ex) {
			throw xicor::xlib::XlibException(ex);
		}			
	}

} //namespace xsystem
} //namespace plugins
} //namespace xicor
