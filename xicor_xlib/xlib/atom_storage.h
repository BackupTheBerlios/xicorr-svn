#ifndef _ATOM_STORAGE_H_
#define _ATOM_STORAGE_H_

#include "xlib.h"
#include <map>
#include <string>

namespace xicor {
namespace xlib {
    
    class AtomStorage: public iAtomStorage {
    private:
        Display* xconnection;
        std::map<std::string, Atom> atoms_cache;
        std::map<Atom, std::string> names_cache;
    public:
        AtomStorage();
        virtual ~AtomStorage() throw(XlibException);
        
        Atom getAtom(std::string name) throw (XlibException);
        Atom setAtom(std::string name) throw (XlibException);
        std::string getAtomName(Atom atom) throw (XlibException);
        
        void synchronizeCache() throw(XlibException);
        
        void cacheAtomInfo(Atom atom, std::string name) throw(XlibException)
        {
            atoms_cache[name] = atom;
            names_cache[atom] = name;
        }
        void setConnection(Display* const xconnection) throw (XlibException);
    };

} //namespace xlib
} //namespace xicor

#endif //_ATOM_STORAGE_H_
