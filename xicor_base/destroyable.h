#ifndef _DESTROYABLE_H_
#define _DESTROYABLE_H_

namespace xicor {
    /**
     * @brief This class provides virtual destructors for its children
     */
    class iDestroyable {
        public:
            virtual ~iDestroyable() {}
    };

} //namespace xicor

#endif //_DESTROYABLE_H_
