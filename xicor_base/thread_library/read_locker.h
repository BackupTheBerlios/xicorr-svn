#ifndef _READ_LOCKER_H_
#define _READ_LOCKER_H_

namespace xicor {
	namespace thread {
		class RWLock;
	}
}

namespace xicor {
namespace thread {

    class ReadLocker {
        private:
            RWLock * _rwlock;
        public:
            ReadLocker(RWLock * rwlock);
            ~ReadLocker();

            RWLock * get_rw_lock() const;
    };

} //namespace thread
} //namespace xicor

#endif //_READ_LOCKER_H_
