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
                            THROW(TypeCastingFailedException, "Dynamic cast failed");
                        *res = value;
                    }
                }

            template<class Type>
                Type& get(Key_Type data_key) const
                {
                    iAbstractData* idata = data_map.find(data_key)->second;
                    if (!idata)
                        THROW(ObjectNotFoundException, "Invalid data key");

                    AbstractData<Type>* res = dynamic_cast< AbstractData<Type>* > (idata);
                    if (res == NULL)
                        THROW(TypeCastingFailedException, "Dynamic cast failed");
                    return *res;
                }
             
            //set method decorators
            void setChar(Key_Type data_key,const char value)
            {
                set<char>(data_key, value);
            }
            
            void setInt32(Key_Type data_key,const int32 value)
            {
                set<int32>(data_key, value);
            }
            
            void setUInt32(Key_Type data_key,const uint32 value)
            {
                set<uint32>(data_key, value);
            }

            void setString(Key_Type data_key,const std::string& value)
            {
                set<std::string>(data_key, value);
            }

            void setStringList(Key_Type data_key,const List<std::string>& value)
            {
                set<List<std::string> >(data_key, value);
            }
            
            //get method decorators
            char& getChar(Key_Type data_key)
            {
                return get<char>(data_key);
            }
            
            int32& getInt32(Key_Type data_key)
            {
                return get<int32>(data_key);
            }
            
            uint32& getUInt32(Key_Type data_key)
            {
                return get<uint32>(data_key);
            }

            std::string& getString(Key_Type data_key)
            {
                return get<std::string>(data_key);
            }

            List<std::string>& getStringList(Key_Type data_key)
            {
                return get<List<std::string> >(data_key);
            }
    };

} //namespace xicor

#endif //_STORAGE_H_
