#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "stl_ext.h"

#include "xlib/xclient.h"
#include "xlib/xwindow.h"

#include <set>

namespace xicor {
namespace plugins {
namespace xsystem {

	typedef struct _WinInfo {
		std::string name;
		int ID;
		_WinInfo()
			:ID(0)
		{
		}
		
		_WinInfo(std::string _name, int _ID)
			:name(_name),ID(_ID)
		{
		}
	} WinInfo;

	class WindowManager {
		private:
			std::set<Window> windows;
			bool allow_mode;
			List<std::string> app_names_list;
			xicor::xlib::xClient* xclient;
			long client_mask;
			long traveller_mask;
			Window current_traveller;
			xlib::xWindow* current_window;
			
			bool test_name(std::string& name) throw();
		public:
			WindowManager();
			
			void init(xicor::xlib::xClient* _xclient,
						std::string mode, 
						List<std::string> app_names) throw (Exception);
			
			void initTraveller(xicor::xlib::xWindow* traveller) throw (Exception);
			
			WinInfo addNewClient(xicor::xlib::xWindow* new_client) throw (Exception);
			
			xlib::xWindow* getCurrentWindow()
			{
				return current_window;
			}
			
			virtual ~WindowManager();
	};

} //namespace xsystem
} //namespace plugins
} //namespace xicor

#endif //_WINDOW_MANAGER_H_
