#include "thread.h"

// POSIX Threads implementation for Thread

#include <pthread.h>
#include "pthread_impl.h"

#include <unistd.h>

using namespace std;

namespace xicor {
namespace thread {

#define IMPL(x) thread_pth_impl_t * impl = (thread_pth_impl_t *)_impl

    class ThreadAttr
    {
        private:
            pthread_attr_t attr;
            const size_t thread_stack_size;
        
        public:
            ThreadAttr():
                thread_stack_size(262144)
            {
                pthread_attr_init(&attr);
                pthread_attr_setstacksize(&attr, thread_stack_size);
            }

            ~ThreadAttr()
            {
                pthread_attr_destroy(&attr);
            }

            operator const pthread_attr_t * const () const
            {
                return &attr;
            }
    };

    static ThreadAttr thread_attr;
    
    Thread::Thread()
    {
        _impl = new thread_pth_impl_t(this);
    }

    Thread::~Thread()
    {
        IMPL(impl);
        if (is_running())
        {
            pthread_detach(impl->pth);
        }
        delete impl;
    }

    void * start_routine(void * _impl)
    {
        IMPL(impl);
        impl->thread->run();

        impl->is_running = false;

        pthread_exit(0);
    }

    void Thread::start() throw (ThreadLibraryException)
    {
        IMPL(impl);
        if (impl->pth)
        {
            throw ThreadLibraryException("Trying to start thread more than one time");
        }
        impl->is_running = true;
        if (pthread_create(&impl->pth, thread_attr, start_routine, _impl))
        {
            impl->is_running = false;
            impl->pth = 0;
            throw ThreadLibraryException("pthread_create() returned non-zero");   
        }
    }

    void Thread::join()
    {
        IMPL(impl);
        if (!impl->joined)
        {
            impl->joined = true;
            pthread_join(impl->pth, NULL);
        }
    }

    bool Thread::is_running()
    {
        IMPL(impl);
        return impl->pth != 0 && impl->is_running;
    }

    void Thread::stop()
    {
        IMPL(impl);
        impl->stop_flag = true;
    }

    void Thread::abort()
    {
    }

    bool Thread::test_stop()
    {
        IMPL(impl);
        if (is_running() && impl->stop_flag)
        {
            impl->is_running = false;
            abort();
            pthread_exit(0);
        }
        return false;
    }

    void Thread::sleep(int32_t msecs)
    {
        usleep(msecs);
    }
    
    void Thread::yield()
    {
        sched_yield();
    }

#undef IMPL

} //namespace thread
} //namespace xicor
