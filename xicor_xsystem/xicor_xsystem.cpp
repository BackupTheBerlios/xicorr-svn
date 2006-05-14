#include "plugin_library/system_plugin.h"
#include "xsystem/keyboard_observer.h"
#include "xsystem/focus_change_observer.h"
#include "xsystem/window_manager.h"
#include "conf_library/configuration.h"
#include "conf/buffer_action_bindings_param_factory.h"

//TODO: rm
#include "plugin_library/com_data_storage.h"

using namespace xicor::conf;
using namespace xicor::xlib;

namespace xicor {
namespace plugins {
    
    class XicorXSystemPlugin: public iSystemPlugin {
        private:
            iComDataStorage* comdata;
            iConfiguration* conf;
            xClient* xclient;
            bool init_needed;
            xsystem::FocusChangeObserver* focus_observer;
            xsystem::KeyboardObserver* key_observer;
            xsystem::WindowManager* win_manager;
        public:
            XicorXSystemPlugin()
                :comdata(NULL),conf(NULL),
                xclient(NULL),
                init_needed(true),
                focus_observer(NULL),
                key_observer(NULL),
                win_manager(NULL)
            {
                win_manager = new xsystem::WindowManager;
                key_observer = new xsystem::KeyboardObserver;
                focus_observer = new xsystem::FocusChangeObserver;
                xclient = new xClient;
                
                xicor::conf::iParamFactory::registerParamFactory("buffer_action_bindings.list", 
                                                            new BufferActionBindingsParamFactory);
            }
            
            ~XicorXSystemPlugin()
            {
                if(focus_observer)
                    delete focus_observer;
                if(key_observer)
                    delete key_observer;
                if(win_manager)
                    delete win_manager;
                if(xclient)
                    delete xclient;
            }
            /**
             * @brief Init method.
             */
            PluginResult init(iConfiguration* _conf,
                                iComDataStorage* _comdata) throw()
            {
                if(_comdata)
                    comdata = _comdata;
                else
                    return PluginResult("Bad ComDataStorage ptr");
                
                if(_conf)
                    conf = _conf;
                else
                    return PluginResult("Bad Configuration ptr");
                
                try {
                    xclient->connect();
                    
                    std::string mode = conf->getString("AppListMode");
                    win_manager->init(xclient, 
                                    mode, conf->getStringList("AppName" + mode) );
                    key_observer->init(comdata);
                    focus_observer->init(xclient, win_manager, comdata);
                    
                    xclient->attachEventObserver(key_observer, KEYBOARD_EVENT);
                    xclient->attachEventObserver(focus_observer, FOCUS_CHANGE_EVENT);
                }
                catch(Exception& ex) {
                    return PluginResult(ex);
                }
                return PluginResult();
            }
            /**
             * @brief Deinit method.
             */
            void deinit() const throw()
            {   
            }   
            /**
             * @brief Process method.
             */
            void workOnInput() throw(Exception)
            {
                if (init_needed) {
                    xWindow* first_win = new xWindow(xclient->getInputFocus(), 
                                                    new xClientDecorator(xclient));
                    
                    xsystem::WinInfo info = win_manager->addNewClient(first_win);
                    
                    comdata->setString("current_app_name", info.name);
                    comdata->setInt32("current_app_id", info.ID);

                    init_needed = false;
                }
                try {
                    key_observer->prepare();
                    focus_observer->prepare();
                    //std::cout << "Waiting event..." << std::endl;
                    xclient->recieveEvent();
                    //std::cout << comdata->getString("current_event") 
                    //        << " event has been proccessed" << std::endl;
                }
                catch (XlibException& ex) {
//                  init_needed = true;
                    throw Exception(ex);
                }
            }

            void workOnOutput() throw(Exception)
            {
                std::string str = comdata->getString("current_output");
                std::string event = comdata->getString("current_event");
                bool output_enable = comdata->get<bool>("output_enable");
                if (output_enable && event == "key" && !str.empty()) {
                    xlib::xLatin1Key delkey(XK_BackSpace, None);
                    for (uint32 i = 0; i < str.size(); i++)
                        xclient->getEvent()->send(win_manager->getCurrentWindow(), &delkey);

                    for (uint32 i = 0; i < str.size(); i++)
                    {
                        xlib::xLatin1Key meankey(str[i]);
                        xclient->getEvent()->send(win_manager->getCurrentWindow(), &meankey);
                    }
                }
            }
    };

    SET_FACTORY_FOR_SYSTEM_PLUGIN(XicorXSystemPlugin)
        
} //namespace plugins
} //namespace xicor

