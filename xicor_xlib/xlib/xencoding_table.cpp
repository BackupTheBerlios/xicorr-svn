#include "xencoding_table.h"

#include <X11/keysym.h>
#include <X11/keysymdef.h>

namespace xicor {
namespace xlib {
    
    static KeySym __ks[] = { XK_quotedbl, XK_apostrophe, XK_bracketleft, XK_bracketright,
            XK_comma, XK_period, XK_colon, XK_semicolon,
            XK_less, XK_greater, XK_braceleft, XK_braceright,
            XK_space, XK_exclam, XK_at, XK_numbersign,
            XK_ssharp, XK_dollar, XK_percent, XK_degree,
            XK_ampersand, XK_asterisk, XK_parenleft, XK_parenright,
            XK_underscore, XK_equal, XK_plus, XK_minus,
            XK_slash, XK_bar, XK_backslash, XK_question
    };
    static char __ch[] = { '"', '\'', '{', '}',
            ',', '.', ':', ';',
            '<', '>', '[', ']',
            ' ', '!', '@', '#', //TODO
            '#', '$', '%', '^',
            '&', '*', '(', ')',
            '_', '=', '+', '-',
            '/', '|', '\\', '?'
    };
        
    xEncodingTable* xEncodingTable::instance = NULL;
    
    xEncodingTable* xEncodingTable::makeObject()
    {
        if (!xEncodingTable::instance) {
            xEncodingTable::instance = new xEncodingTable();
        }
        return xEncodingTable::instance;
    }
    
    xEncodingTable::xEncodingTable()
    {
    }
    
    xEncodingTable::~xEncodingTable()
    {
    }

    //TODO: 
    char xEncodingTable::getSpecialCharFromKeysym(KeySym keysym) throw (XlibException)
    {
        int32 iterator;
        char res = '\0';
    
        for (iterator = 0; iterator < 32; iterator++)
            if (keysym == __ks[iterator]) {
                res = __ch[iterator];
                break;
            }
        return res;
    }
    
    //TODO: 
    KeySym xEncodingTable::getKeysymFromSpecialChar(char c) throw (XlibException)
    {
        int32 iterator;
        KeySym res = None;
    
        for (iterator = 0; iterator < 32; iterator++)
            if (c == __ch[iterator]) {
                res = __ks[iterator];
                break;
            }
        return res;
    }

} //namespace xlib
} //namespace xicor
