#include "write_locker.h"
#include "rw_lock.h"

namespace xicor {
namespace thread {

    WriteLocker::WriteLocker(RWLock * rwlock):
        _rwlock(rwlock)
    {
        if (_rwlock)
            _rwlock->write_lock();
    }

    WriteLocker::~WriteLocker()
    {
        if (_rwlock)
            _rwlock->unlock();
    }

    RWLock * WriteLocker::get_rw_lock() const
    {
        return _rwlock;
    }

} //namespace thread
} //namespace xicor
