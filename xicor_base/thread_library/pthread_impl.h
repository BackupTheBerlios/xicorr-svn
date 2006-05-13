#ifndef _PTHREAD_IMPL_H_
#define _PTHREAD_IMPL_H_

namespace xicor {
    namespace thread {
        class Thread;
        class Lock;
        class WaitCondition;
        class RWLock;
    }
}

#include <pthread.h>

namespace xicor {
namespace thread {
    
    struct lock_pth_impl_t {
        pthread_mutex_t mutex;
    };
    
    struct thread_pth_impl_t {
        Thread * thread;
        pthread_t pth;

        bool stop_flag;
        bool is_running;
        bool joined;

        thread_pth_impl_t(Thread * _thread)
            :thread(_thread),
             pth(0),
             stop_flag(false),
             is_running(false),
             joined(false)
        {}      
    };

    struct cond_pth_impl_t {
        pthread_cond_t cond;  
    };
    
    struct rwlock_pth_impl_t {
        pthread_rwlock_t rwlock;
    };

} //namespace thread
} //namespace xicor

#endif //_PTHREAD_IMPL_H_
