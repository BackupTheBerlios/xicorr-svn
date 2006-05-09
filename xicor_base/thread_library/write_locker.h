#ifndef _WRITE_LOCKER_H_
#define _WRITE_LOCKER_H_

namespace xicor {
	namespace thread {
		class RWLock;
	}
}

namespace xicor {
namespace thread {

    class WriteLocker
    {
        private:
            RWLock * _rwlock;
        public:
            WriteLocker(RWLock * rwlock);
            ~WriteLocker();

            RWLock * get_rw_lock() const;
    };

} //namespace thread
} //namespace xicor

#endif //_WRITE_LOCKER_H_
