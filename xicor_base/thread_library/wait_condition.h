#ifndef _WAIT_CONDITION_H_
#define _WAIT_CONDITION_H_

namespace xicor {
    namespace thread {
        class Lock;
    }
}

namespace xicor {
namespace thread {

    class WaitCondition {
        private:
            void * _impl;
        public:
            WaitCondition();
            ~WaitCondition();

            void wait( Lock * lock );
            void wake_one();
            void wake_all();
    };

} //namespace thread
} //namespace xicor

#endif //_WAIT_CONDITION_H_

