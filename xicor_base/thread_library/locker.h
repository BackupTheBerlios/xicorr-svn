#ifndef _LOCKER_H_
#define _LOCKER_H_

namespace xicor {
	namespace thread {
		class Lock;
	}
}

namespace xicor {
namespace thread {

    /// @brief Locker class simplifies locking and unlocking Locks
    ///
    /// The purpose of Locker is to simplify Lock locking and unlocking.<br>
    /// Instead of:
    /// <pre>
    /// Lock * lock = new Lock();
    /// int function()
    /// {
    ///     lock->lock();
    ///     switch (flag)
    ///     {
    ///         case 0:
    ///             lock->unlock();
    ///             return .... just something ....
    ///         case 1:
    ///             lock->unlock();
    ///             return .... something else ....
    ///         .....
    ///     }
    ///     lock->unlock();
    ///     return 0;
    /// }
    /// </pre>
    /// We write:
    /// <pre>
    /// Lock * lock = new Lock();
    /// void function()
    /// {
    ///     Locker locker(lock);
    ///     switch (flag)
    ///     {
    ///         case 0:
    ///             return ....
    ///         case 1:
    ///             return ....
    ///     }
    ///     return 0;
    /// }
    /// </pre>
    class Locker {
        private:
            Lock * _lock;
        public:
            /// @brief Constructs a Locker and locks the specified <i>lock</i>.
            /// The lock will be unlocked when the Locker is destroyed
            Locker(Lock * lock);

            /// @brief Destroys the Locker and unlocks the lock which
            /// was locked in the constructor
            ~Locker();

            /// @brief Returns a pointer to the lock which was locked in
            /// the constructor
            Lock * get_lock() const;
    };
} //namespace thread
} //namespace xicor

#endif //_LOCKER_H_
