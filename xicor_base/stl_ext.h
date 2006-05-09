#ifndef _STL_EXT_H_
#define _STL_EXT_H_

#include <list>
#include <map>

namespace xicor {

	template<class Type>
		class List: public std::list<Type> {
			public:
				
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
