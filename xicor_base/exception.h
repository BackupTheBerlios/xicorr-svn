#ifndef _EXCEPTION_IMPL_H_
#define _EXCEPTION_IMPL_H_

#include "types.h"

#include <stdexcept>
#include <string>

namespace xicor {

    /**
     * @brief Base exception implementation. Module name is set to "UnknownModule". If you need
     * to change it, overload getModuleName method.
     * In purpose of catching by base class it inherits std::exception
     */
    class Exception: public std::exception {
        private:
            std::string message;
            ELocation location;
            std::string previous;
        protected:
        	/// Returns "".
            virtual std::string module() const
            {
                return "";
            }
        public:
            /// Constructor with no params. Exception location and exception message are set to default values
            Exception ();
            /// Copy constructor. Used for rethrow exceptions with saving previous info.
            Exception (const Exception& previous);
            /// Constructor with message param. Exception location is set to default values
            Exception (std::string message);
            /// Constructor with all params.
            Exception (std::string message, std::string fname, unsigned int lnum);
            virtual ~Exception () throw ();
            /// Returns exception message with module name at the beginning
            std::string getMessage () const;
            /// Returns name of file where exception was thrown
            std::string getLocationFilename() const;
            /// Returns number of line in file where exception was thrown
            unsigned int getLocationLineNumber () const;
            /// Returns path of modules, exception has passed.
            virtual std::string getModuleName() const;
            
            const char* what() const throw();

    };

} //namespace xicor

#endif //_EXCEPTION_IMPL_H_
