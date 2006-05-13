#ifndef _PLUGIN_RESULT_H_
#define _PLUGIN_RESULT_H_

#include "result.h"

namespace xicor {
namespace plugins {

    /**
     * @brief Result class. Returned by plugin methods.
     */
    class PluginResult: public Result {
        protected:
            std::string module() const
            {
                return "Plugin";
            }
        public:
            PluginResult()
                :Result()
            {}
            PluginResult(std::string message)
                :Result(message)
            {}
            PluginResult(std::string message, std::string filename, int32 line_num)
                :Result(message, filename, line_num)
            {}
            PluginResult (const Exception& ex)
                :Result(ex)
            {}
    };

} //namespace plugins
} //namespace xicor

#endif //_PLUGIN_RESULT_H_
