#ifndef _STORAGE_H_
#define _STORAGE_H_

#include "abstract_data.h"

#include <iostream>

#include "stl_ext.h"

namespace xicor {
    
    template <class Key_Type>
    class AbstractDataStorage: public iDestroyable,
                                public iSerializeable {
        protected:
            Map<Key_Type, iAbstractData*> data_map;
        public:
            AbstractDataStorage()
            {
            }
            
            ~AbstractDataStorage()
            {
                typename Map<Key_Type, iAbstractData*>::iterator itr;
                for (itr = data_map.begin(); itr != data_map.end(); itr++)
                    if(itr->second)
                        delete itr->second;
            }

            void serialize (std::ostream& out) const throw (Exception)
            {
                typename Map<Key_Type, iAbstractData*>::const_iterator itr;
                for (itr = data_map.begin(); itr != data_map.end(); itr++)
                {
                    itr->second->serialize(out);
                    out << "; ";
                }
                out << std::endl;
            }
            
            template<class Type>
                void set(const Key_Type& data_key, const Type& value)
                {
                    iAbstractData* data = NULL;
                    try {
                        data = data_map.tryKey(data_key);
                    }
                    catch (const ObjectNotFoundException& ex) {
                        data_map[data_key] = new AbstractData<Type> (value);
                        return;
                    }
                    
                    AbstractData<Type >* res = dynamic_cast< AbstractData<Type >* > (data);
                    if (res == NULL)
                        THROW(TypeCastingFailedException, "Dynamic cast failed");
                    *res = value;
                }

            template<class Type>
                Type& get(const Key_Type& data_key)
                {
                    iAbstractData* idata = data_map.tryKey(data_key);
                    AbstractData<Type >* res = dynamic_cast< AbstractData< Type >* > (idata);
                    if (res == NULL)
                        THROW(TypeCastingFailedException, "Dynamic cast failed");

                    return *res;
                }
            
            template<class Type>
                const Type& get(const Key_Type& data_key) const
                {
                    iAbstractData* idata = data_map.tryKey(data_key);
                    AbstractData<Type >* res = dynamic_cast< AbstractData<Type >* > (idata);
                    if (res == NULL)
                        THROW(TypeCastingFailedException, "Dynamic cast failed");
                    return *res;
                }
             
            //set method decorators
            void setChar(const Key_Type& data_key, const char value)
            {
                set<char>(data_key, value);
            }
            
            void setInt32(const Key_Type& data_key, const int32 value)
            {
                set<int32>(data_key, value);
            }
            
            void setUInt32(const Key_Type& data_key, const uint32 value)
            {
                set<uint32>(data_key, value);
            }

            void setString(const Key_Type& data_key, const std::string& value)
            {
                set<std::string>(data_key, value);
            }

            void setStringList(const Key_Type& data_key, const List<std::string>& value)
            {
                set<List<std::string> >(data_key, value);
            }
            
            //get method decorators
            char& getChar(const Key_Type& data_key)
            {
                return get<char>(data_key);
            }
            
            int32& getInt32(const Key_Type& data_key)
            {
                return get<int32>(data_key);
            }
            
            uint32& getUInt32(const Key_Type& data_key)
            {
                return get<uint32>(data_key);
            }

            std::string& getString(const Key_Type& data_key)
            {
                return get<std::string>(data_key);
            }

            List<std::string>& getStringList(const Key_Type& data_key)
            {
                return get<List<std::string> >(data_key);
            }
    };

} //namespace xicor

#endif //_STORAGE_H_
