#include "wait_condition.h"
#include "lock.h"

#include <pthread.h>
#include "pthread_impl.h"

// POSIX Threads implementation for WaitCondition

namespace xicor {
namespace thread {

#define IMPL(x) cond_pth_impl_t * x = (cond_pth_impl_t *)_impl;
    
    WaitCondition::WaitCondition()
    {
        cond_pth_impl_t * impl = new cond_pth_impl_t();
        _impl = impl;

        pthread_cond_init(&impl->cond, 0);
    }

    WaitCondition::~WaitCondition()
    {
        IMPL(impl);
        pthread_cond_destroy(&impl->cond);

        delete impl;
    }

    void WaitCondition::wait( Lock * lock )
    {
        IMPL(impl);
        pthread_cond_wait(&impl->cond, &(((lock_pth_impl_t*)lock->_impl)->mutex));
    }

    void WaitCondition::wake_one()
    {
        IMPL(impl);
        pthread_cond_signal(&impl->cond);
    }

    void WaitCondition::wake_all()
    {
        IMPL(impl);
        pthread_cond_broadcast(&impl->cond);
    }

} //namespace thread
} //namespace xicor
