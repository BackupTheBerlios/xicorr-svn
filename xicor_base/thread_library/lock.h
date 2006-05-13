#ifndef _LOCK_H_
#define _LOCK_H_

namespace xicor {
    namespace thread {
        class WaitCondition;
    }
}

namespace xicor {
namespace thread {
    /// @brief The Lock class provides access serialization between threads
    ///
    /// The purpose of a Lock is to protect an object, data structure or section of code so that
    /// only one thread can access it at a time.<br>
    /// Example:
    /// <pre>
    /// Lock lock;
    /// int32 number = 6;
    ///
    /// void thread1()
    /// {
    ///     lock->lock();
    ///     number += 3;
    ///     number *= 2;
    ///     lock->unlock();
    /// }
    /// 
    /// void thread2()
    /// {
    ///     lock->lock();
    ///     number *= 2;
    ///     number += 3;
    ///     lock->unlock();
    /// }
    /// </pre>
    /// Only one thread can modify number at any given time.
    class Lock {
        friend class WaitCondition;
        
        private:
            void * _impl;
        public:
            Lock();
            ~Lock();

            /// @brief Attempts to lock the Lock object. If another thread has
            /// locked this object then this call will block until that 
            /// thread has unlocked it.
            void lock();

            /// @brief Unlocks the mutex. Attempting to unlock a mutex in a
            /// different thread to the one that locked it results in an error.
            /// Unlocking a mutex that is not locked results in undefined behaviour.
            void unlock();

            /// @brief Attempts to lock the Lock object. If the lock was 
            /// obtained the function returns true. If another thread has 
            /// locked the mutex, it returns false instead of blocking.
            bool try_lock();
    };
    
} //namespace thread
} //namespace xicor

#endif //_LOCK_H_
