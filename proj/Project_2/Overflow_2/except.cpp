/*
 * File:   except.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for except.h
 * Created on December 1, 2016
 */

#include "except.h"

/**
 * The default constructor for an Exception.
 * @param msg An error message indicating the nature of the exception. Defaults to "ErrorCode::EXCEPTION"
 * @param code An integer error code indicating the nature of the exception. Defaults to ErrorCode::EXCEPTION
 * @see ErrorCode
 */
Error::Exception::Exception(const std::string &msg, unsigned int code){
    _msg = msg;
    _code = code;
}

/**
 * Get an error message for this Exception
 * @return The error message for this Exception
 */
std::string Error::Exception::message() const{
    return _msg;
}

/**
 * Set the error message for this Exception
 * @param msg The error message for this Exception
 */
void Error::Exception::message(const std::string &msg){
    _msg = msg;
}

/**
 * Get an error code for this Exception
 * @return The ErrorCode for this exception
 */
unsigned int Error::Exception::errorCode() const{
    return _code;
}

/**
 * Set the error code for this Exception
 * @param code The ErrorCode for this exception
 */
void Error::Exception::errorCode(unsigned int code){
    _code = code;
}

/**
 * Generate a string representation of this object
 * @return A string of the format "message : errorCode"
 */
std::string Error::Exception::toString() const{
    std::stringstream r;
    r << _msg << " : 0x" << std::hex << std::setfill('0') << std::setw(8) << _code; //Not using show base cause it messes up the fill
    return r.str();
}