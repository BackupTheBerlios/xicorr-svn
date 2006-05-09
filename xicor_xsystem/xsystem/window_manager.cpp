#include "window_manager.h"
#include <algorithm>
#include <iostream>

namespace xicor {
namespace plugins {
namespace xsystem {

	bool WindowManager::test_name(std::string& name) throw()
	{
		bool res = false;
		if (allow_mode) {
			if (std::find(app_names_list.begin(),
							app_names_list.end(),
							name) != app_names_list.end() )
				res = true;
		}
		else {
			if (std::find(app_names_list.begin(),
							app_names_list.end(),
							name) != app_names_list.end() )
				res = false;
		}
		return res;
			
	}

	WindowManager::WindowManager()
		:xclient(NULL),
		client_mask(xicor::xlib::FOCUS_CHANGE_EVENT|xicor::xlib::KEYBOARD_EVENT),
		traveller_mask(xicor::xlib::FOCUS_CHANGE_EVENT),
		current_traveller(0),
		current_window(NULL)
	{
	}
	
	WindowManager::~WindowManager()
	{
		if (current_window)
			delete current_window;
	}
	
	void WindowManager::init(xicor::xlib::xClient* _xclient,
							std::string str_mode,
							List<std::string> app_names) throw (Exception)
	{
		if (_xclient && _xclient->isAlive())
			xclient = _xclient;
		else
			throw Exception("Bad xclient");

		if (str_mode == "Allow")
			allow_mode = true;
		else
			allow_mode = false;
	
		app_names_list = app_names;
	}

	void WindowManager::initTraveller(xicor::xlib::xWindow* traveller)
															throw (Exception)
	{
		if (current_traveller)
			xclient->setMonitoringOff(current_traveller);
		current_traveller = traveller->getID();
		xclient->setMonitoringOn(current_traveller, traveller_mask);
	}
	
	WinInfo WindowManager::addNewClient(xicor::xlib::xWindow* new_client) 
														throw (Exception)
	{
		WinInfo res;
		if (current_window)
			delete current_window;
		current_window = new_client;
			
		try {
			std::auto_ptr<xicor::xlib::xWindow> app_root(new_client->getGroupRootWindow());
			std::auto_ptr<xicor::xlib::xWindow> has_class(app_root->findChildByAtom("WM_NAME"));
			std::string name = has_class->getClass();
				
			if(windows.find(new_client->getID()) == windows.end()) {
				if (test_name(name) && app_root->hasLocallyActiveFocusModel()) {
					std::cout << "get New Client: " + name << std::endl;
					windows.insert(new_client->getID());
					xclient->setMonitoringOn(new_client->getID(),client_mask);
					xclient->setMonitoringOn(has_class->getID(),client_mask);
					res.name = name;
					res.ID = has_class->getID();
				}
				else {
					std::cout << "get New Traveller: " + name << std::endl;
					initTraveller(has_class.get());
				}
			}
			else {
				res.name = name;
				res.ID = has_class->getID();
			}
		}
		catch(const Exception& ex) {
			std::cout << "hope it's New Traveller" << std::endl;
			std::auto_ptr<xicor::xlib::xWindow> app_root(new_client->getGroupRootWindow());
			initTraveller(app_root.get());
			throw Exception(ex);
		}
		
		return res;
	}


} //namespace xsystem
} //namespace plugins
} //namespace xicor
