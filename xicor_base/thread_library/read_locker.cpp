#include "read_locker.h"
#include "rw_lock.h"

namespace xicor {
namespace thread {
    
    ReadLocker::ReadLocker(RWLock * rwlock):
        _rwlock(rwlock)
    {
        if (_rwlock)
            _rwlock->read_lock();
    }

    ReadLocker::~ReadLocker()
    {
        if (_rwlock)
            _rwlock->unlock();
    }

    RWLock * ReadLocker::get_rw_lock() const
    {
        return _rwlock;
    }

} //namespace thread
} //namespace xicor
