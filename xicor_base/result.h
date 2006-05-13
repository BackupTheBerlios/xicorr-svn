/**
 * @file result.h Contains result classes, used by methods
 * that can't throw exceptions.
 */
 
#ifndef _RESULT_H_
#define _RESULT_H_

#include "exception.h"

namespace xicor {

    /**
     * @brief Base result class. Returned if exceptions can't be used.
     * Inherits Exception interface implementation. If result is successful
     * use empty message Result objects.
     */
    class Result: public Exception {
        protected:
            std::string module() const
            {
                return "Result";
            }
        public:
            Result()
                :Exception()
            {}
            Result(std::string message)
                :Exception(message)
            {}
            Result(std::string message, std::string filename, int32 line_num)
                :Exception(message, filename, line_num)
            {}
            Result (const Exception& ex)
                :Exception(ex)
            {}
            /**
             * Checks if the result is successful or not.
             */
            virtual bool isSuccessful() const
            {
                if (getMessage().empty() )
                    return true;
                return false;
            }
    };
    
} //namespace xicor

#endif //_RESULT_H_
