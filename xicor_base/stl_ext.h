#ifndef _STL_EXT_H_
#define _STL_EXT_H_

#include <list>
#include <map>
#include <set>

#include "exception.h"
#include <sstream>

namespace xicor {

    template<class From, class To>
        To convert (const From& f)
        {
            std::string str;
            To res;
            std::stringstream convertor(str);
            convertor << f;
            convertor >> res;
            return res;
        }
    template<class From>        
        std::string toString(const From& f)
        {
            return convert<From, std::string>(f);
        }
        
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
                
                Map()
                {
                }
                
                Map(const KeyType& key, const ValueType& value)
                {
                    (*this)[key] = value;
                }
                
                ValueType& tryKey(const KeyType& key) throw (std::exception,
                                                                ObjectNotFoundException)
                {
                    typename Map::iterator itr;
                    if ( (itr = find(key)) == this->end() )
                        THROW(ObjectNotFoundException, toString<KeyType>(key) + 
                                                            ": No such key found");
                        
                    return itr->second;
                }
                
                const ValueType& tryKey(const KeyType& key) const 
                                                         throw (std::exception,
                                                                ObjectNotFoundException)
                {
                    typename Map::const_iterator itr;
                    if ( (itr = find(key)) == this->end() )
                        THROW(ObjectNotFoundException, toString<KeyType>(key) + 
                                                            ": No such key found");
                        
                    return itr->second;
                }
                
                void addNewValue(const KeyType& key, const ValueType& value) 
                                                                throw ( std::exception,
                                                                        AlreadyExistsException)
                {
                    if ( std::map<KeyType, ValueType>::find(key) != 
                                        std::map<KeyType, ValueType>::end() )
                        THROW(AlreadyExistsException, toString<KeyType>(key) + 
                                                        ": Element already exist");
                        
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
    
    template<class KeyType, class ValueType>
        class Pair: public std::pair<KeyType, ValueType> {
            public:
                Pair()
                {
                }
                
                Pair(const KeyType& key, const ValueType& value)
                {
                    this->first = key;
                    this->second = value;
                }
                
                friend std::ostream& operator<< (std::ostream& out, const Pair& p)
                {
                        out << p.first << ":" << p.second << " ";
                    return out;
                }
        };
        
    template<class ValueType>
        class Set: public std::set<ValueType> {
            public:
                Set()
                {
                }
                
                Set(const ValueType& value)
                {
                    this->insert(value);
                }
                
                friend std::ostream& operator<< (std::ostream& out, const Set& s)
                {
                    typename Set::iterator itr;
                    for(itr = s.begin(); itr != s.end(); itr++)
                        out << *itr << " ";
                    return out;
                }
        };
} //namespace xicor

#endif //_STL_EXT_H_
