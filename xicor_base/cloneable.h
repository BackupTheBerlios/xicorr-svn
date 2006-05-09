#ifndef _ICLONEABLE_H_
#define _ICLONEABLE_H_

#include "destroyable.h"
#include "exception.h"

namespace xicor {
    /**
     * @brief This class provides ability to its children to be cloned by themselves.
     */
    class iCloneable: public iDestroyable {
        public:
            /// @brief Returns pointer to the newly constructed and initialized 
            /// object of the same as owner of this method type
            virtual iCloneable* clone() const throw (Exception) = 0;
    };

} //namespace xicor

#endif //_ICLONEABLE_H_
