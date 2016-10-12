/* 
 * File:   Byte.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Create a simple type for handling binary data directly and converting it to a writable array easily
 * Created on October 11, 2016
 */

#ifndef BYTE_H
#define BYTE_H

#include <string>
#include <iostream>
#include <fstream>

//Byte
//Contains Byte type and helper functions/types
namespace Byte {

    //ByteUnion
    //Templated Union to provide direct access to the type T as both signed and unsigned characters
    template<class T>
    union ByteUnion {
        T value; //The actual underlying union value
        unsigned char bytes[sizeof (T)]; //Standard unsigned bytes for handling in a program
        char sbytes[sizeof (T)]; //Signed bytes for I/O using read and write functions
    };

    //Byte
    //Templated class that allows the treatment of the type T as a series of bytes rather than only as the value
    template<class T>
    class Byte {
    public:

        //Byte
        //Instantiate a new Byte object with a value set to the default value of the type
        Byte() {
            data.value = {}; //Only valid in C++11
        }

        //Byte
        //Instantiate a new Byte object with the given value
        //Input:
        //value
        //The value to assign the underlying data to
        Byte(const T value) {
            data.value = value;
        }

        //Byte
        //Instantiate a new Byte object that is a copy of the input object
        //Input:
        //other
        //The Byte object to copy from
        Byte(const Byte &other) {
            data.value = other.get();
        }

        //Get
        //Return the underlying value of the Byte
        //Output:
        //The value of the underlying data union
        T get() const {
            return data.value;
        }

        //Get Bytes
        //Return the underlying value of the Byte as an array of unsigned characters
        //Output:
        //A pointer to the underlying array of unsigned characters
        unsigned char* getBytes() {
            return data.bytes;
        }

        //Get Signed Bytes
        //Return the underlying value of the Byte as an array of characters
        //Output:
        //A pointer to the underlying array of characters
        char* getSBytes() {
            return data.sbytes;
        }

        //Set
        //Sets the underlying value of the Byte to the input value
        //Input:
        //value
        //A value of the type T to set the underlying data to
        void set(const T value) {
            data.value = value;
        }

        //Size
        //Returns the size of the underlying data in bytes
        //Output:
        //The size of the underlying data structure in bytes. Stored in a 64-bit value to ensure valid returns for all
        //input types
        unsigned long size() const {
            return sizeof (data);
        }

        //Size Bits
        //Returns the size of the underlying data in bytes. Equivalent to size() * 8
        //Output:
        //The size of the underlying data structure in bits. Stored in a 64-bit value to ensure valid returns for all
        //input types
        unsigned long sizeBits() const {
            return sizeof (data) * 8;
        }

        //Get Bit
        //Get the bit at the given index in the underlying data.
        //Input:
        //index
        //The 0 based index of the bit to get the value of
        //Output:
        //A boolean value representing the bit at the given index
        bool getBit(const unsigned long index) const {
            if (index < sizeBits()) {
                unsigned char pos = index / 8; //Calculate the position
                //This is a bit fancy
                //Returns whether or not the value of the byte at pos AND 2^(index - pos * 8) is 0
                return (data.bytes[pos] & (1 << (index - pos * 8))) != 0; 
            }
            return 0;
        }

        //Set Bit
        //Sets a bit at the given index in the underlying data. Toggles the bit in question. If the bit is 1 it becomes 0
        //and 0 becomes 1
        //Input:
        //index
        //The 0 based index of the bit to set the value of
        void setBit(const unsigned long index) {
            if (index <= sizeBits() && index >= 0) {
                unsigned char pos = index / 8; //Calculate the position
                data.bytes[pos] ^= (1 << (index - pos * 8)); //Returns the value of the byte at pos XOR 2^(index - pos * 8)
            }
        }

        //To String
        //Return a string representing binary data underlying the current value
        //Output:
        //A string representing the underlying data as a binary value 
        std::string toString() {
            std::string r = ""; //The return string

            for (int i = sizeBits() - 1; i >= 0; --i) { //Little Endian
                r += getBit(i) ? '1' : '0'; //If the bit is on concatinate 1 to the string otherwise 0
            }
//            for(int i = 0; i < sizeBits(); ++i){ //Big Endian
//                r += getBit(i) ? '1' : '0'; //If the bit is on concatinate 1 to the string otherwise 0
//            }

            return r;
        }

        //To String
        //Return a string representing binary data underlying the current value. If a true parameter is passed in then
        //the output will be broken up every four bits
        //Output:
        //A string representing the underlying data as a binary value
        std::string toString(bool frmt) {
            std::string r = toString(); //Set the return string to the return of the default toString function

            if (frmt) { //If formatting is on
                for (int i = 0; i < r.size(); ++i) { //For every byte in the value
                    if ((i + 1) % 5 == 0) { //If i + 1 is divisible by 5
                        r.insert(i, " "); //Insert a space in the string
                    }
                }
            }

            return r;
        }

        //Copy Assignment
        //Copy one Byte object to another
        //Input:
        //rhs
        //The value on the right hand side of the operator
        //Output:
        //A reference to this object after assignment
        Byte& operator=(const Byte &rhs) {
            if (this != &rhs && data.value != rhs.get()) { //If this isn't equal to the input
                data.value = rhs.get(); //Set the value to the value of rhs
            }

            return *this; //Return this object
        }

        //Standard Assignment
        //Assign the value on the right of the operator to this object
        //Input:
        //rhs
        //The value on the right hand side of the operator
        //Output:
        //A reference to this object after assignment
        Byte& operator=(const T rhs) {
            if (data.value != rhs) { //If this isn't equal to the input
                data.value = rhs; //Set the value to the input
            }

            return *this; //Return this object
        }

        //Index Operator
        //Allow the Byte object to be indexed into like it was the underlying unsigned character array
        //Input:
        //index
        //The 0 based index of the value to access
        //Output:
        //A reference to the underlying unsigned character value at the input index
        unsigned char& operator[](const unsigned int index) {
            return data.bytes[index]; //Wrap the index operator for the bytes array
        }
    private:
        ByteUnion<T> data; //A ByteUnion representing the underlying data of the this byte
    };
    
    //Unary +
    template<class T>
    Byte<T> operator+(const Byte<T> &rhs){
        return Byte<T>(+rhs.get());
    }
    
    //Unary -
    template<class T>
    Byte<T> operator-(const Byte<T> &rhs){
        return Byte<T>(-rhs.get());
    }
    
    //+
    template<class T>
    Byte<T> operator+(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() + rhs.get());
    }
    
    template<class T>
    Byte<T> operator+(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs + rhs.get());
    }
    
    template<class T>
    Byte<T> operator+(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() + rhs);
    }
    
    //-
    template<class T>
    Byte<T> operator-(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() - rhs.get());
    }
    
    template<class T>
    Byte<T> operator-(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() - rhs);
    }
    
    template<class T>
    Byte<T> operator-(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs - rhs.get());
    }
    
    //*
    template<class T>
    Byte<T> operator*(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() * rhs.get());
    }
    
    template<class T>
    Byte<T> operator*(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() * rhs);
    }
    
    template<class T>
    Byte<T> operator*(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs * rhs.get());
    }
    
    // /
    template<class T>
    Byte<T> operator/(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() / rhs.get());
    }
    
    template<class T>
    Byte<T> operator/(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() / rhs);
    }
    
    template<class T>
    Byte<T> operator/(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs / rhs.get());
    }
    
    //%
    template<class T>
    Byte<T> operator%(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() % rhs.get());
    }
    
    template<class T>
    Byte<T> operator%(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() % rhs);
    }
    
    template<class T>
    Byte<T> operator%(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs % rhs.get());
    }
    
    //~
    template<class T>
    Byte<T> operator~(const Byte<T> &rhs){
        return Byte<T>(~rhs.get());
    }
    
    //&
    template<class T>
    Byte<T> operator&(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() & rhs.get());
    }
    
    template<class T>
    Byte<T> operator&(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() & rhs);
    }
    
    template<class T>
    Byte<T> operator&(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs & rhs.get());
    }
    
    // |
    template<class T>
    Byte<T> operator|(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() | rhs.get());
    }
    
    template<class T>
    Byte<T> operator|(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() | rhs);
    }
    
    template<class T>
    Byte<T> operator|(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs | rhs.get());
    }
    
    //^
    template<class T>
    Byte<T> operator^(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() ^ rhs.get());
    }
    
    template<class T>
    Byte<T> operator^(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() ^ rhs);
    }
    
    template<class T>
    Byte<T> operator^(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs ^ rhs.get());
    }
    
    //<<
    template<class T>
    Byte<T> operator<<(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() << rhs.get());
    }
    
    template<class T>
    Byte<T> operator<<(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() << rhs);
    }
    
    template<class T>
    Byte<T> operator<<(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs << rhs.get());
    }
    
    //>>
    template<class T>
    Byte<T> operator>>(const Byte<T> &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs.get() >> rhs.get());
    }
    
    template<class T>
    Byte<T> operator>>(const Byte<T> &lhs, const T &rhs){
        return Byte<T>(lhs.get() >> rhs);
    }
    
    template<class T>
    Byte<T> operator>>(const T &lhs, const Byte<T> &rhs){
        return Byte<T>(lhs >> rhs.get());
    }
    
    //++
    template<class T>
    Byte<T>& operator++(Byte<T>& rhs){
        rhs.set(rhs.get() + 1);
        return rhs;
    }
    
    template<class T>
    Byte<T> operator++(Byte<T>& rhs, int i){
        Byte<T> r(rhs);
        rhs.set(rhs.get() + 1);
        return r;
    }
    
    //--
    template<class T>
    Byte<T>& operator--(Byte<T>& rhs){
        rhs.set(rhs.get() - 1);
        return rhs;
    }
    
    template<class T>
    Byte<T> operator--(Byte<T>& rhs, int i){
        Byte<T> r(rhs);
        rhs.set(rhs.get() - 1);
        return r;
    }
    
    //!
    template<class T>
    bool operator!(const Byte<T> &rhs){
        return !rhs.get();
    }
    
    //&&
    template<class T>
    bool operator&&(const Byte<T> &lhs, const Byte<T> &rhs){
        return lhs.get() && rhs.get();
    }
    
    template<class T>
    bool operator&&(const Byte<T> &lhs, const T &rhs){
        return lhs.get() && rhs;
    }
    
    template<class T>
    bool operator&&(const T &lhs, const Byte<T> &rhs){
        return lhs && rhs.get();
    }
    
    //||
    template<class T>
    bool operator||(const Byte<T> &lhs, const Byte<T> &rhs){
        return lhs.get() || rhs.get();
    }
    
    template<class T>
    bool operator||(const Byte<T> &lhs, const T &rhs){
        return lhs.get() || rhs;
    }
    
    template<class T>
    bool operator||(const T &lhs, const Byte<T> &rhs){
        return lhs || rhs.get();
    }
    
    //==
    template<class T>
    bool operator==(const Byte<T> &lhs, const Byte<T> &rhs){
        return lhs.get() == rhs.get();
    }
    
    template<class T>
    bool operator==(const Byte<T> &lhs, const T &rhs){
        return lhs.get() == rhs;
    }
    
    template<class T>
    bool operator==(const T &lhs, const Byte<T> &rhs){
        return lhs == rhs.get();
    }
    
    //!=
    template<class T>
    bool operator!=(const Byte<T> &lhs, const Byte<T> &rhs){
        return lhs.get() != rhs.get();
    }
    
    template<class T>
    bool operator!=(const Byte<T> &lhs, const T &rhs){
        return lhs.get() != rhs;
    }

    template<class T>
    bool operator!=(const T &lhs, const Byte<T> &rhs){
        return lhs != rhs.get();
    }
    
    //<
    template<class T>
    bool operator<(const Byte<T> &lhs, const Byte<T> &rhs){
        return lhs.get() < rhs.get();
    }
    
    template<class T>
    bool operator<(const Byte<T> &lhs, const T &rhs){
        return lhs.get() < rhs;
    }
    
    template<class T>
    bool operator<(const T &lhs, const Byte<T> &rhs){
        return lhs < rhs.get();
    }
    
    //<=
    template<class T>
    bool operator<=(const Byte<T> &lhs, const Byte<T> &rhs){
        return lhs.get() <= rhs.get();
    }
    
    template<class T>
    bool operator<=(const Byte<T> &lhs, const T &rhs){
        return lhs.get() <= rhs;
    }
    
    template<class T>
    bool operator<=(const T &lhs, const Byte<T> &rhs){
        return lhs <= rhs.get();
    }
    
    //>
    template<class T>
    bool operator>(const Byte<T> &lhs, const Byte<T> &rhs){
        return lhs.get() > rhs.get();
    }
    
    template<class T>
    bool operator>(const Byte<T> &lhs, const T &rhs){
        return lhs.get() > rhs;
    }
    
    template<class T>
    bool operator>(const T &lhs, const Byte<T> &rhs){
        return lhs > rhs.get();
    }
    
    //>=
    template<class T>
    bool operator>=(const Byte<T> &lhs, const Byte<T> &rhs){
        return lhs.get() >= rhs.get();
    }
    
    template<class T>
    bool operator>=(const Byte<T> &lhs, const T &rhs){
        return lhs.get() >= rhs;
    }
    
    template<class T>
    bool operator>=(const T &lhs, const Byte<T> &rhs){
        return lhs >= rhs.get();
    }
    
    //+=
    template<class T>
    Byte<T>& operator+=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() + rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator+=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() + rhs);
        
        return lhs;
    }
    
    //-=
    template<class T>
    Byte<T>& operator-=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() - rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator-=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() - rhs);
        
        return lhs;
    }
    
    //*=
    template<class T>
    Byte<T>& operator*=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() * rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator*=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() * rhs);
        
        return lhs;
    }
    
    // /=
    template<class T>
    Byte<T>& operator/=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() / rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator/=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() / rhs);
        
        return lhs;
    }
    
    //%=
    template<class T>
    Byte<T>& operator%=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() % rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator%=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() % rhs);
        
        return lhs;
    }
    
    //&=
    template<class T>
    Byte<T>& operator&=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() & rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator&=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() & rhs);
        
        return lhs;
    }
    
    //|=
    template<class T>
    Byte<T>& operator|=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() | rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator|=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() | rhs);
        
        return lhs;
    }
    
    //^=
    template<class T>
    Byte<T>& operator^=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() ^ rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator^=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() ^ rhs);
        
        return lhs;
    }
    
    //<<=
    template<class T>
    Byte<T>& operator<<=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() << rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator<<=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() << rhs);
        
        return lhs;
    }
    
    //>>=
    template<class T>
    Byte<T>& operator>>=(Byte<T> &lhs, const Byte<T> &rhs){
        lhs.set(lhs.get() >> rhs.get());
        
        return lhs;
    }
    
    template<class T>
    Byte<T>& operator>>=(Byte<T> &lhs, const T &rhs){
        lhs.set(lhs.get() >> rhs);
        
        return lhs;
    }
    
    //Stream Operators
    template<class T>
    std::ostream& operator<<(std::ostream &lhs, Byte<T> &rhs) {
        lhs << rhs.get();
        return lhs;
    }

    template<class T>
    std::istream& operator>>(std::istream &lhs, Byte<T> &rhs) {
        T value;
        lhs >> value;
        rhs.set(value);
        return lhs;
    }

    template<class T>
    std::ofstream& operator<<(std::ofstream &lhs, Byte<T> &rhs) {
        lhs << rhs.get();
        return lhs;
    }

    template<class T>
    std::ifstream& operator>>(std::ifstream &lhs, Byte<T> &rhs) {
        T value;
        lhs >> value;
        rhs.set(value);
        return lhs;
    }
    
}

#endif /* BYTE_H */

