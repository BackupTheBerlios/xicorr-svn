#ifndef _UTILS_H_
#define _UTILS_H_

#include "X11/Xlib.h"
#include "stl_ext.h"
#include <string>

namespace xicor {
namespace xlib {
    
    KeySym stringToKeysym(const std::string& str);
    const Set<KeySym>& getAllSymbolic();
    const Set<KeySym>& getAllModifiers();
    bool isSymbolic(KeySym);
    bool isModifier(KeySym);

} //namespace xlib
} //namespace xicor

#endif //_UTILS_H_
