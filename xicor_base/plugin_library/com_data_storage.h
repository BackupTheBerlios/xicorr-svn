#ifndef _COM_DATA_STORAGE_H_
#define _COM_DATA_STORAGE_H_

#include "abstract_storage.h"

namespace xicor {
namespace plugins {

    /**
     * @brief This interface provides simple set/get functionality of the storage.
     * This storage is used as communication data container between core and plugin or plugin and plugin.
     */
    class iComDataStorage: public AbstractDataStorage<std::string> {
    };

} //namespace plugins
} //namespace xicor

#endif //_COM_DATA_STORAGE_H_
