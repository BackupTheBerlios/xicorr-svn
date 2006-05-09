#include "locker.h"
#include "lock.h"

namespace xicor {
namespace thread {
	
    Locker::Locker(Lock * lock):
        _lock(lock)
    {
        if (_lock)
            _lock->lock();
    }

    Locker::~Locker()
    {
        if (_lock)
            _lock->unlock();
    }

    Lock * Locker::get_lock() const
    {
        return _lock;
    }

} //namespace thread
} //namespace xicor
