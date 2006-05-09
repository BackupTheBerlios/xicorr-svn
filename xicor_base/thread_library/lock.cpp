#include "pthread_impl.h"
#include "thread_library_exception.h"
#include "lock.h"

// POSIX Threads implementation for Lock

namespace xicor {
namespace thread {

#define IMPL(x) lock_pth_impl_t * x = (lock_pth_impl_t *)_impl
    
    class LockAttr {
        private:
            pthread_mutexattr_t attr;
        public:
            LockAttr()
            {
                pthread_mutexattr_init(&attr);
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
            }

            ~LockAttr()
            {
                pthread_mutexattr_destroy(&attr);
            }

            operator const pthread_mutexattr_t * const () const
            {
                return &attr;
            }
    };

    static LockAttr lock_attr;
    
    Lock::Lock()
    {
        lock_pth_impl_t * impl = new lock_pth_impl_t();
        _impl = impl;

        if (pthread_mutex_init(&impl->mutex, lock_attr))
            throw ThreadLibraryException("pthread_mutex_init returned non-zero");
    }

    Lock::~Lock()
    {
        IMPL(impl);
        pthread_mutex_destroy(&impl->mutex);

        delete impl;
    }

    void Lock::lock()
    {
        IMPL(impl);
        if (pthread_mutex_lock(&impl->mutex))
        {
            throw ThreadLibraryException("pthread_mutex_lock returned non-zero");
        }
    }

    void Lock::unlock()
    {
        IMPL(impl);
        if (pthread_mutex_unlock(&impl->mutex))
        {
            throw ThreadLibraryException("pthread_mutex_unlock returned non-zero");
        }
    }

    bool Lock::try_lock()
    {
        IMPL(impl);
        if (pthread_mutex_trylock(&impl->mutex) == 0)
            return true;
        return false;
    }

#undef IMPL

} //namespace thread
} //namespace xicor
