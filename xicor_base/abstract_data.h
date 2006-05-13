#ifndef _ABSTRACT_DATA_H_
#define _ABSTRACT_DATA_H_

#include "destroyable.h"
#include "serializeable.h"

namespace xicor {

    class iAbstractData: public iSerializeable,
                            public iDestroyable {
    };

    template<class Type>
        class AbstractData: public iAbstractData {
            private:
                Type data;
            public:
                AbstractData (Type _data)
                    :data(_data)
                {}
                
                operator Type ()
                {
                    return data;
                }
                
                operator Type& ()
                {
                    return data;
                }
                
                void serialize (std::ostream& out) const throw (Exception)
                {
                    //TODO: something strange with patterns
                    Type dummy = data;
                    out << dummy;
                }
        };

} //namespace abstract_data

#endif //_ABSTRACT_DATA_H_
