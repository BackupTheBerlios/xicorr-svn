#include "atom_storage.h"

#include <sstream>

namespace xicor {
namespace xlib {

    AtomStorage::AtomStorage()
        :xconnection(0)
    {}
    
    AtomStorage::~AtomStorage() throw(XlibException)
    {}
    
    void AtomStorage::setConnection(Display* const _xconnection)
                                                    throw (XlibException)
    {
        if (!_xconnection)
            THROW(XlibException, "Invalid connection");
        xconnection = _xconnection;
    }
    
    Atom AtomStorage::getAtom(std::string name) throw (XlibException)
    {
        Atom res = atoms_cache[name];
        if(!res) {
            res = XInternAtom(xconnection, name.c_str(), true);
            if (!res)
                THROW(XlibException, "Atom with the name '" + name
                                                     + "' doesn't exist");
            cacheAtomInfo(res, name);
        }
        return res;
    }
    
    Atom AtomStorage::setAtom(std::string name) throw (XlibException)
    {
        Atom res = atoms_cache[name];
        if(!res) {
            res = XInternAtom(xconnection, name.c_str(), true);
            if (!res)
                THROW(XlibException, "Atom with the name '" + name
                                                     + "' already exist");
            res = XInternAtom(xconnection, name.c_str(), false);
            if (!res)
                THROW(XlibException, "Atom with the name '" + name 
                                                + "' registration failed");
            cacheAtomInfo(res, name);
        }
        else {
            THROW(XlibException, "Atom with the name '" + name
                                                     + "' already exist");
        }       
        return res;
    }
    
    std::string AtomStorage::getAtomName(Atom atom) throw (XlibException)
    {
        std::string name = names_cache[atom];
        if(name.empty()) {
            name = XGetAtomName(xconnection, atom);
            if (name.empty()) {
                std::string str;
                std::ostringstream stream(str);
                stream << atom;
                THROW(XlibException, "No existing atom with ID=" + stream.str());
            }
            else 
                cacheAtomInfo(atom,name);
        }
        return name;
    }
    
    void AtomStorage::synchronizeCache() throw(XlibException)
    {
        char** names_list;
        Atom* atoms_list;
        uint32 atoms_num = atoms_cache.size();
        
        names_list = new char* [atoms_num];
        atoms_list = new Atom [atoms_num];
        
        XInternAtoms(xconnection, names_list, atoms_num, false, atoms_list);
        
        for(uint32 i = 0; i < atoms_num; i++)
            cacheAtomInfo(atoms_list[i], names_list[i]);
        
        delete [] atoms_list;
        delete [] names_list;
        
    }

} //namespace xlib
} //namespace xicor
