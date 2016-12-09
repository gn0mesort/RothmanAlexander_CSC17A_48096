/*
 * File:   macros.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define common use macros and helper functions
 * Created on November 30, 2016
 */

#ifndef MACROS_H
#define MACROS_H

//System Libraries
#include <string> //Strings

#ifndef null
/**
 * Defines null as 0. The same as NULL
 */
#define null (0)
#endif

#ifndef byte
/**
 * Defines a byte macro that is equivalent to the Byte::Byte<unsigned char>
 */
#define byte Byte::Byte<unsigned char>
#endif

#ifndef stringify
/**
 * Preform simple stringification. Equivalent to wrapping a value in double quotes
 */
#define stringify(x) (#x)
#endif

#ifndef nameof
/**
 * Gets the name of an assignable value. Otherwise generate compiler errors
 */
#define nameof(x) (nameof_check(#x, x))
#endif

#ifndef to_int
/**
 *  Convert a value to an int
 */
#define to_int(x) (static_cast<int>(x))
#endif

#ifndef to_uint
/**
 * Convert a value to an unsigned int
 */
#define to_uint(x) (static_cast<unsigned int>(x))
#endif

#ifndef to_bin
/**
 * Convert a value to binary data
 */
#define to_bin(x) (reinterpret_cast<char*>(&x))
#endif

/**
 * Causes a compiler error if nameof() is used on a value that can't be assigned
 * @param str The stringified input of nameof()
 * @param value The input of nameof()
 * @return the input string str
 */
template<typename T>
std::string nameof_check(const std::string &str, T value){
    return str;
}

#endif /* MACROS_H */

