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
            Exception (std::string message, std::string fname, uint32 lnum);
            virtual ~Exception () throw ();
            /// Returns exception message with module name at the beginning
            std::string getMessage () const;
            /// Returns location (fileName, lineNumber) where exception was thrown
            const ELocation& getLocation() const;
            /// Returns path of modules, exception has passed.
            virtual std::string getModuleName() const;
            
            const char* what() const throw();

    };
    
    class TypeCastingFailedException: public Exception {
        public:
            TypeCastingFailedException ();
            
            TypeCastingFailedException (std::string str);

            TypeCastingFailedException (std::string message, 
                                        std::string fname, 
                                        uint32 lnum);

            TypeCastingFailedException (const Exception& ex);
    };
    
    class ObjectNotFoundException: public Exception {
        public:
            ObjectNotFoundException ();
            
            ObjectNotFoundException (std::string str);
            
            ObjectNotFoundException (std::string message, 
                                     std::string fname, 
                                     uint32 lnum);

            ObjectNotFoundException (const Exception& ex);
    };
    
    class AlreadyExistsException: public Exception {
        public:
            AlreadyExistsException ();
            
            AlreadyExistsException (std::string str);
            
            AlreadyExistsException (std::string message, 
                                    std::string fname, 
                                    uint32 lnum);

            AlreadyExistsException (const Exception& ex);
    };

} //namespace xicor

#define THROW_EMPTY(exception) throw exception("", __FILE__, __LINE__)
#define THROW(exception, message) throw exception(message, __FILE__, __LINE__)

#endif //_EXCEPTION_IMPL_H_
