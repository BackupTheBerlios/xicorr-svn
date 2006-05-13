#ifndef _STL_EXT_H_
#define _STL_EXT_H_

#include <list>
#include <map>

#include "exception.h"

namespace xicor {

    template<class Type>
        class List: public std::list<Type> {
            public:
                List()
                {
                }
                List(const Type& elem)
                {
                    push_back(elem);
                }
                
                friend std::ostream& operator<< (std::ostream& out, List& l)
                {
                    typename List::iterator itr;
                    for(itr = l.begin(); itr != l.end(); itr++)
                        out << *itr << " ";
                    return out;
                }
        };
        
    template<class KeyType, class ValueType>
        class Map: public std::map<KeyType, ValueType> {
            public:
                ValueType& getValue(const KeyType& key) throw (std::exception,
                                                                ObjectNotFoundException)
                {
                    typename Map::iterator itr;
                    if ( (itr = find(key)) == this->end() )
                        THROW(ObjectNotFoundException, "No such key found");
                        
                    return itr->second;
                }
                
                void addNewValue(const KeyType& key, const ValueType& value) 
                                                                throw ( std::exception,
                                                                        AlreadyExistsException)
                {
                    if ( find(key) != this->end() )
                        THROW(AlreadyExistsException, "element already exist");
                        
                    (*this)[key] = value;
                }
                
                friend std::ostream& operator<< (std::ostream& out, Map& m)
                {
                    typename Map::iterator itr;
                    for(itr = m.begin(); itr != m.end(); itr++)
                        out << itr->first << ":" << itr->second << " ";
                    return out;
                }
        };
    
} //namespace xicor

#endif //_STL_EXT_H_
