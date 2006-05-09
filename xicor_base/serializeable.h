#ifndef _ISERIALIZEABLE_H_
#define _ISERIALIZEABLE_H_

#include "exception.h"

#include <ostream>

namespace xicor {

    /**
     * @brief This class provides to its children an ability of formated outputting to the given output stream
     */
    class iSerializeable {
        public:
            virtual void serialize (std::ostream& out) const throw (Exception) = 0;
    };
    
} //namespace xicor

#endif //_ISERIALIZEABLE_H_
