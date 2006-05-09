#ifndef _RW_LOCK_H_
#define _RW_LOCK_H_

namespace xicor {
namespace thread {

    /**
     * @brief The RWLock class provides synchronization between threads with 
     * two levels of access
     */

    class RWLock {
        private:
            void * _impl;
            
        public:
            RWLock();
            ~RWLock();

            void read_lock();
            void write_lock();

            bool try_read_lock();
            bool try_write_lock();

            void unlock();
    };
    
} //namespace thread
} //namespace xicor

#endif //_RW_LOCK_H_
