#ifndef _THREAD_H_
#define _THREAD_H_

#include "thread_library_exception.h"

namespace xicor {
namespace thread {

	/// @brief Parent class for thread-working child classes.
    class Thread {
        private:
            void * _impl;
        protected:
			/// @brief Tests stop flag. If it is true calls abort(),
			/// then stops thread execution.
            bool test_stop();
            
			/// @brief This method is to be reimplemeted in subclasses.
			/// It is called to deinitialize Thread object.
            virtual void abort();
           
			/// @brief Creates new Thread object
			/// NOTE: Only for calling from custom subclass constructors.
            Thread();

        public:
            virtual ~Thread();

			/// @brief Begins execution of the thread by calling run() method.
            void start() throw (ThreadLibraryException);

			/// @brief Caller blocks until the thread associated with this
			/// Thread object finishes execution.
            void join();

			/// @brief Returns true is thread is not started or running.
            bool is_running();

			/// @brief Set the stop flag.
            void stop();

			/// @brief Blocks the calling thread for msecs milliseconds.
            static void sleep(int msecs);

			/// @brief Relinquish the processor.
            static void yield();

  			/// @brief This method is to be implemented in subclasses
			/// to describe thread behavior.
            virtual void run() throw () = 0;
/*
			/// @brief Detach thread. Detached thread cleans resources and
			/// destroys thread object by itself when finishes
            void detach();
*/            
    };
    
} //namespace thread
} //namespace xicor

#endif //_THREAD_H_
