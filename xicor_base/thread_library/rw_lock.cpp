#include "rw_lock.h"

#include <pthread.h>
#include "pthread_impl.h"
#include "thread_library_exception.h"

// POSIX Threads implementation for RWLock

namespace xicor {
namespace thread {

#define IMPL(x) rwlock_pth_impl_t * x = (rwlock_pth_impl_t *)_impl

    RWLock::RWLock()
    {
        rwlock_pth_impl_t * impl = new rwlock_pth_impl_t();
        _impl = impl;

        if (pthread_rwlock_init(&impl->rwlock, NULL))
        {
            throw ThreadLibraryException("pthread_rwlock_init returned non-zero");
        }
    }

    RWLock::~RWLock()
    {
        IMPL(impl);
        pthread_rwlock_destroy(&impl->rwlock);

        delete impl;
    }

    void RWLock::read_lock()
    {
        IMPL(impl);
        if (pthread_rwlock_rdlock(&impl->rwlock))
        {
            throw ThreadLibraryException("pthread_rwlock_rdlock returned non-zero");
        }
    }

    void RWLock::write_lock()
    {
        IMPL(impl);
        if (pthread_rwlock_wrlock(&impl->rwlock))
        {
            throw ThreadLibraryException("pthread_rwlock_wrlock returned non-zero");
        }
    }

    bool RWLock::try_read_lock()
    {
        IMPL(impl);
        if (pthread_rwlock_tryrdlock(&impl->rwlock) == 0)
            return true;
        return false;
    }

    bool RWLock::try_write_lock()
    {
        IMPL(impl);
        if (pthread_rwlock_trywrlock(&impl->rwlock) == 0)
            return true;
        return false;
    }

    void RWLock::unlock()
    {
        IMPL(impl);
        if (pthread_rwlock_unlock(&impl->rwlock))
        {
            throw ThreadLibraryException("pthread_rwlock_unlock returned non-zero");
        }
   }

#undef IMPL

} //namespace thread
} //namespace xicor
