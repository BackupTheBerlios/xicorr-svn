#include "xkey.h"
#include "xencoding_table.h"

#include <X11/Xutil.h>

#include <iostream>

namespace xicor {
namespace xlib {

    void xLatin1Key::toLowerCaseIfUpper()
    {
        KeySym lowks, upks;
        XConvertCase(key, &lowks, &upks);
        if (key == upks && upks != lowks) {
            key = lowks;
            modifier = XK_Shift_R;
        }
    }
    
    xLatin1Key::xLatin1Key()
        :encoding_table(xEncodingTable::makeObject())
    {
    }
    
    xLatin1Key::xLatin1Key(char _latinChar)
        :latinChar(_latinChar),
        modifier(None),
        encoding_table(xEncodingTable::makeObject())
    {
        char str[] = {latinChar, '\0'};
        key = XStringToKeysym(str);
        //TODO: encoding_table is suxx
        if (key == None)
            key = encoding_table->getKeysymFromSpecialChar(latinChar);
        
        toLowerCaseIfUpper();
    }
    
    xLatin1Key::xLatin1Key(KeySym _key, KeySym _modifier) throw(XlibException)
        :key(_key),
        modifier(_modifier),
        encoding_table(xEncodingTable::makeObject())
    {
        toLowerCaseIfUpper();
    }
    
    xLatin1Key::xLatin1Key(XEvent* event) throw(XlibException)
        :latinChar('\0'),
        key(None),
        modifier(None),
        encoding_table(xEncodingTable::makeObject())
    {
        //get latin-1 keysym
        //TODO: is latin-1 index always 0?
        key = XLookupKeysym(&(event->xkey), 0);
        
        if (key == XK_Shift_R || key == XK_Shift_L ||
            key == XK_Control_R || key == XK_Control_L) {
            key = None;
            return;
        }
            
        //get modifiers
        if ((event->xkey.state) & ControlMask)
            modifier = XK_Control_R;
        if ((event->xkey.state) & ShiftMask)
            modifier = XK_Shift_R;
        
        //convert case if needed
        KeySym lowks, upks;
        XConvertCase(key, &lowks, &upks);
        
        //convert latin-1 keysym to latin-1 char
        //TODO: encoding_table is suxx
        if (lowks != upks) {
            char *strPtr = NULL;
            if (modifier == XK_Shift_R)
                strPtr = XKeysymToString (upks);
            else
                strPtr = XKeysymToString (lowks);

            if (strPtr)
                latinChar = strPtr[0];
            else
                THROW(XlibException, "Unknown keysym convert error");
        }
        else
            latinChar = encoding_table->getSpecialCharFromKeysym(key);
    }
    
    bool xLatin1Key::isChar() throw(XlibException)
    {
        return latinChar?true:false;
    }
    
    bool xLatin1Key::isModified() throw(XlibException)
    {
        if (modifier != None)
            return true;
        return false;
    }
        
    char xLatin1Key::getChar() throw(XlibException)
    {
        return latinChar;
    }
    
    KeySym xLatin1Key::getKey() throw(XlibException)
    {
        return key;
    }
    
    KeySym xLatin1Key::getModifier() throw(XlibException)
    {
        return modifier;
    }

} //namespace xlib
} //namespace xicor
