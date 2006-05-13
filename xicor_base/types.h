#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>

/**
 * @brief Global project namespace. Contains all-in-use classes and types
 * and local namespaces.
 */
namespace xicor {
    /**
     * @brief Local project namespace. Contains interface 
     * and implementation classes of the project configuration
     * library.
     */
    namespace conf {
    }
    /**
     * @brief Local project namespace. Contains interface 
     * and implementation classes of the project meta objects 
     * library.
     */
    namespace meta {
    }
    /**
     * @brief Local project namespace. Contains interface 
     * and implementation classes of the project thread 
     * library.
     */
    namespace thread {
    }
    /**
     * @brief Local project namespace. Contains xlib wrapper
     *  classes.
     */
    namespace xlib {
    }
    /**
     * @brief Local project namespace. Contains core classes.
     */
    namespace core {
    }
    /**
     * @brief Local project namespace. Contains plugin used classes. 
     * And plugins themself.
     */
    namespace plugins {
    }
    
    typedef unsigned char byte;

    typedef int32_t int32;
    typedef uint32_t uint32;

    /**
     * @brief Error location structure.
     */
    struct ELocation {
        /**
         * @brief Name of the file, where error occured.
         */
        std::string filename;
        /**
         * @brief Number of the line in the file, where error occured.
         */
        uint32 line_num;
    };
    
    typedef int32 Lang;
    
    const Lang UNSUPPORTED_LANG = -1;
    const Lang ENGLISH = 0;
    const Lang RUSSIAN = 1;

} //namespace xicor
#endif //_TYPES_H_
