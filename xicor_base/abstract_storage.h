#ifndef _STORAGE_H_
#define _STORAGE_H_

#include "abstract_data.h"

#include "stl_ext.h"

#include <map>

namespace xicor {
	
	template <class Key_Type>
	class AbstractDataStorage: public iDestroyable,
								public iSerializeable {
		protected:
			std::map<Key_Type, iAbstractData*> data_map;
		public:
			AbstractDataStorage()
			{
			}
			
			~AbstractDataStorage()
			{
				typename std::map<Key_Type, iAbstractData*>::iterator itr;
				for (itr = data_map.begin(); itr != data_map.end(); itr++)
					if(itr->second)
						delete itr->second;
			}

			void serialize (std::ostream& out) const throw (Exception)
			{
				typename std::map<Key_Type, iAbstractData*>::const_iterator itr;
				for (itr = data_map.begin(); itr != data_map.end(); itr++)
				{
					itr->second->serialize(out);
					out << "; ";
				}
				out << std::endl;
			}
			
			template<class Type>
				void set(Key_Type data_key,Type value)
				{
					iAbstractData* data = data_map[data_key];
					if(!data)
						data_map[data_key] = new AbstractData<Type> (value);
					else {
						AbstractData<Type>* res = dynamic_cast< AbstractData<Type>* > (data);
						if (res == NULL)
							throw Exception("Bad cast");
						*res = value;
					}
				}

			template<class Type>
				Type& get(Key_Type data_key) const
				{
					iAbstractData* idata = data_map.find(data_key)->second;
					if (!idata)
						throw Exception("Invalid data key");

					AbstractData<Type>* res = dynamic_cast< AbstractData<Type>* > (idata);
					if (res == NULL)
						throw Exception("Bad cast");
					return *res;
				}
	};

} //namespace xicor

#endif //_STORAGE_H_
