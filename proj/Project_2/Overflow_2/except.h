/*
 * File:   except.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Create a C# like exception class and define common exceptions
 * Created on November 21, 2016
 */

#ifndef EXCEPT_H
#define EXCEPT_H

//System Libraries
#include <string> //Strings
#include <sstream> //String streams
#include <iomanip> //I/O Formatting

//User Libraries
#include "macros.h" //nameof() macro

/**
 * A namespace containing objects for basic Exception handling
 */
namespace Error{

    /**
     * A container namespace for preset exception error codes. All codes (except NONE) end with the
     * byte 0x01 (0000 0001). This is because POSIX systems (Linux/Cygwin) only return 8-bit error codes
     * (Windows will return the full 32-bit code). Codes end in 0x01 to ensure that returning an exception is
     * always understood as a failed run.
     */
    namespace ErrorCode{
        /**
         * Represents the absence of an error. Equivalent to 0x00
         */
        const unsigned int NONE = 0x00000000,
                /**
                 * Represents a generic exception. Equivalent to 0x01
                 */
                EXCEPTION = 0x00000001,
                /**
                 * Represents an exception caused by an invalid input argument
                 */
                ARGUMENT_EXCEPTION = 0x00000101,
                /**
                 * Represents an exception caused by a null reference
                 */
                NULL_EXCEPTION = 0x00000201,
                /**
                 * Represents an exception caused by a math error (such as a division by 0)
                 */
                MATH_EXCEPTION = 0x00000301,
                /**
                 * Represents an exception caused by a File stream
                 */
                FILE_EXCEPTION = 0x00000401;
    }

    /**
     * A base class designed to be inherited by various types of Exception. Differs from std::exception in that it
     * behaves more like System.Exception in C#
     */
    class Exception{
    private:
    protected:
        /**
         * The underlying message value of the Exception
         */
        std::string _msg;

        /**
         * The underlying error code of the Exception
         */
        unsigned int _code;
    public:
        Exception(const std::string& = nameof(ErrorCode::EXCEPTION), unsigned int = ErrorCode::EXCEPTION);
        virtual std::string message() const;
        virtual void message(const std::string&);
        virtual unsigned int errorCode() const;
        virtual void errorCode(unsigned int);
        virtual std::string toString() const;
    };

    /**
     * Defines an exception generated by an improper input argument
     */
    class ArgumentException : public Exception{
    private:
    public:

        ArgumentException(const std::string &msg = nameof(ErrorCode::ARGUMENT_EXCEPTION),
                          unsigned int code = ErrorCode::ARGUMENT_EXCEPTION){
            _msg = msg;
            _code = code;
        }
    };

    class FileException : public Exception{
    private:
    public:

        FileException(const std::string &msg = nameof(ErrorCode::FILE_EXCEPTION),
                      unsigned int code = ErrorCode::FILE_EXCEPTION){
            _msg = msg;
            _code = code;
        }
    };
}


#endif /* EXCEPT_H */

