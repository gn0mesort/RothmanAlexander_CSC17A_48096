/*
 * File:   collections.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define various data structures
 * Created on November 22, 2016
 */

#ifndef COLLECTIONS_H
#define COLLECTIONS_H

//System Libraries
#include <sstream> //Stringstreams
#include <vector> //Vectors
#include <utility> //std::swap
#include <string> //Strings

//User Libraries
#include "except.h" //Error::Exceptions

/**
 * Defines various data structures
 */
namespace Collections{

    /**
     * Defines a single node in a LinkedList. Contains two links as well as the node data
     */
    template<typename T>
    class ListNode{
    private:
    protected:
        /**
         * The previous node in the list that contains this node or 0 if this node is the first node
         */
        ListNode<T> *_head;

        /**
         * The next node in the list that contains this node or 0 if this node is the last node
         */
        ListNode<T> *_tail;

        /**
         * The data for this ListNode
         */
        T _data;
    public:
        ListNode();
        ListNode(T);
        ListNode<T>* head() const;
        void head(ListNode<T>*);
        ListNode<T>* tail() const;
        void tail(ListNode<T>*);
        T data() const;
        void data(T);
        T& dataref();
    };

    /**
     * Default constructor for a ListNode. Doesn't link the node to anything.
     */
    template<typename T>
    ListNode<T>::ListNode(){
        _head = 0;
        _tail = 0;
        _data;
    }

    /**
     * Parameterized constructor for a ListNode. Doesn't link the node to anything. Set _data to the input value
     * @param data The value of this node
     */
    template<typename T>
    ListNode<T>::ListNode(T data){
        _head = 0;
        _tail = 0;
        _data = data;
    }

    /**
     * Get a pointer to the previous ListNode from this ListNode
     * @return A pointer to this ListNode's head node
     */
    template<typename T>
    ListNode<T>* ListNode<T>::head() const{
        return _head;
    }

    /**
     * Sets the head pointer for this ListNode
     * @param ref A pointer to the ListNode that exists ahead of this node
     */
    template<typename T>
    void ListNode<T>::head(ListNode<T>* ref){
        _head = ref;
    }

    /**
     * Gets a pointer to the next ListNode from this ListNode
     * @return A pointer to this ListNode's tail node
     */
    template<typename T>
    ListNode<T>* ListNode<T>::tail() const{
        return _tail;
    }

    /**
     * Sets the tail pointer for this ListNode
     * @param ref A pointer to the ListNode that exists after this node
     */
    template<typename T>
    void ListNode<T>::tail(ListNode<T>* ref){
        _tail = ref;
    }

    /**
     * Return the value of this ListNode
     * @return The current value of this ListNode
     */
    template<typename T>
    T ListNode<T>::data() const{
        return _data;
    }

    /**
     * Set the value of this ListNode
     * @param val The value to set this node's value to
     */
    template<typename T>
    void ListNode<T>::data(T val){
        _data = val;
    }

    /**
     * Get the value of this node by reference
     * @return A reference to the data value of this node
     */
    template<typename T>
    T& ListNode<T>::dataref(){
        return _data;
    }

    /******************************************************************************************************************/
    /******************************************************************************************************************/
    /******************************************************************************************************************/

    /**
     * Defines a doubly linked list class. Almost certainly not better than std::list. Provides basic functionality like
     * indexing, adding to the front or back of the list, removing nodes, copy construction, and toString. This class
     * forms the basis for the other structures in this namespace
     */
    template<typename T>
    class LinkedList{
    private:
        /**
         * The head node of this list. If the list is empty it should point to 0 (NULL)
         */
        ListNode<T> *_head;

        /**
         * The tail node of this list. If the list is empty it should point to 0 (NULL)
         */
        ListNode<T> *_tail;

        /**
         * The size of this list. Can support huge list sizes
         */
        unsigned int _size;
    public:
        LinkedList();
        LinkedList(unsigned int);
        LinkedList(const LinkedList<T> &);
        LinkedList(const T[], unsigned int);
        LinkedList(const std::vector<T>&);
        LinkedList(std::initializer_list<T>);
        ~LinkedList();
        unsigned int size() const;
        void addBack(T);
        void addFront(T);
        void remove(unsigned int);
        ListNode<T>* head() const;
        ListNode<T>* tail() const;
        std::string toString(int = 10);
        bool contains(T);
        static void swap(LinkedList<T>&, LinkedList<T>&);
        T& operator[](unsigned int);
        T operator[](unsigned int)const;
        LinkedList<T>& operator=(const LinkedList<T>&);
    };

    /**
     * Constructs a default LinkedList. The default list will be empty
     */
    template<typename T>
    LinkedList<T>::LinkedList(){
        _head = 0;
        _tail = 0;
        _size = 0;
    }

    /**
     * Constructs a LinkedList of the given size.
     * This requires C++11 or higher
     * @param size The initial size of the list
     */
    template<typename T>
    LinkedList<T>::LinkedList(unsigned int size){
        _head = 0;
        _tail = 0;
        _size = 0;

        T value = {}; //Set value to its default regardless of type
        for(unsigned int i = 0; i < size; ++i){
            addBack(value); //Add default valued list elements
        }
    }

    /**
     * Constructs a LinkedList as a copy of another list
     * @param other The list to copy
     */
    template<typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& other){
        _head = 0;
        _tail = 0;
        _size = 0;

        for(unsigned int i = 0; i < other.size(); ++i){
            addBack(other[i]);
        }
    }

    /**
     * Constructs a LinkedList from an array
     * @param arr The array to copy into the list
     * @param size The size of the input array
     */
    template<typename T>
    LinkedList<T>::LinkedList(const T arr[], unsigned int size){
        _head = 0;
        _tail = 0;
        _size = 0;

        for(unsigned int i = 0; i < size; ++i){
            addBack(arr[i]);
        }
    }

    /**
     * Constructs a LinkedList from a vector
     * @param data The vector to copy
     */
    template<typename T>
    LinkedList<T>::LinkedList(const std::vector<T>& data){
        _head = 0;
        _tail = 0;
        _size = 0;

        for(unsigned int i = 0; i < data.size(); ++i){
            addBack(data[i]);
        }
    }

    template<typename T>
    LinkedList<T>::LinkedList(std::initializer_list<T> list){
        _head = 0;
        _tail = 0;
        _size = 0;
        for(T val : list){
            addBack(val);
        }
    }

    /**
     * Destroys a LinkedList. Checks for empty lists.
     */
    template<typename T>
    LinkedList<T>::~LinkedList(){
        if(_head != 0){
            ListNode<T> *node = _head;
            ListNode<T> *tmp = 0;
            while(node != 0){
                tmp = node;
                node = node->tail();

                delete tmp;
                tmp = 0;
            }
        }
    }

    /**
     * Gets the size of the list
     * @return The size of the LinkedList
     */
    template<typename T>
    unsigned int LinkedList<T>::size() const{
        return _size;
    }

    /**
     * Adds a new list element after the tail element
     * @param value The value to add
     */
    template<typename T>
    void LinkedList<T>::addBack(T value){
        ListNode<T> *node = new ListNode<T>(value);

        if(_head == 0){ //If the list is empty
            _head = node;
            _tail = node;
        }
        else{
            node->head(_tail);
            _tail->tail(node);
            _tail = node;
        }
        ++_size;
    }

    /**
     * Adds a new list element before the head element
     * @param value The value to add
     */
    template<typename T>
    void LinkedList<T>::addFront(T value){
        ListNode<T> *node = new ListNode<T>(value);

        if(_head == 0){
            _head = node;
            _tail = node;
        }
        else{
            node->tail(_head);
            _head->head(node);
            _head = node;
        }
        ++_size;
    }

    /**
     * Removes the element at the given index from the list
     * @param index The index to remove from the list
     */
    template<typename T>
    void LinkedList<T>::remove(unsigned int index){
        if(_head != 0 && index < _size){ //If the list is not empty and the index is not out of bounds
            unsigned int count = 0; //The number of nodes deep in the list that the function has gone
            ListNode<T> *node = _head, //The current node
                    *head = 0, //The last node
                    *tail = 0; //The next node
            while(node != 0 && count < index){ //While not at the end of the list and not at the selected node
                node = node->tail(); //The current node is the next node
                ++count; //increment the count
            }
            head = node->head(); //Store the last node
            tail = node->tail(); //Store the next node
            if(tail != 0){ //If this node isn't the end of the list
                node->tail()->head(head); //The next node's head is the last node
            }
            else{ //Otherwise
                _tail = node->head(); //The end of the list is the last node
            }
            if(head != 0){ //If this node isn't the beginning of the list
                node->head()->tail(tail); //The last node's tail is the next node
            }
            else{ //Otherwise
                _head = node->tail(); //The beginning of the list is the next node
            }
            --_size; //Reduce the size

            delete node; //Release the removed node
            node = 0; //Clear the pointer
        }
        else if(_size > 0){ //If the index is out of bounds
            throw Error::ArgumentException("Index was out of bounds", Error::ErrorCode::ARGUMENT_EXCEPTION);
        }
    }

    /**
     * Get the head node of this list
     * @return The fist node in the list
     */
    template<typename T>
    ListNode<T>* LinkedList<T>::head() const{
        return _head;
    }

    /**
     * Get the tail node of this list
     * @return The last node in the list
     */
    template<typename T>
    ListNode<T>* LinkedList<T>::tail() const{
        return _tail;
    }

    template<typename T>
    bool LinkedList<T>::contains(T key){
        bool r = false;

        ListNode<T> *node = _head;
        for(int i = 0; i < size() && !r; ++i){
            if(node->data() == key){
                r = true;
            }
            node = node->tail();
        }

        return r;
    }

    /**
     * Convert this list into a string
     * @param perLine The number of elements to print per line
     * @return A string representing this list
     */
    template<typename T>
    std::string LinkedList<T>::toString(int perLine){
        std::stringstream r;
        for(unsigned long i = 0; i < _size; ++i){
            r << (*this)[i] << " ";
            if((i + 1) % perLine == 0){
                r << std::endl;
            }
        }

        return r.str();
    }

    /**
     * Swap the values of two LinkedLists
     * @param a The first list
     * @param b The second list
     */
    template<typename T>
    void LinkedList<T>::swap(LinkedList<T> &a, LinkedList<T> &b){
        std::swap(a._head, b._head);
        std::swap(a._tail, b._tail);
        std::swap(a._size, b._size);
    }

    /**
     * Gets the list element at the given index and returns it by reference
     * @param index The index of the element to get
     * @return A reference to the given element
     */
    template<typename T>
    T& LinkedList<T>::operator[](unsigned int index){
        if(_head != 0){
            unsigned long count = 0;
            ListNode<T> *node = _head;

            while(node != 0){
                if(count == index){
                    return node->dataref();
                }
                node = node->tail();
                ++count;
            }
        }
        throw Error::ArgumentException("Index was out of bounds", Error::ErrorCode::ARGUMENT_EXCEPTION);
    }

    /**
     * Get the list element at the given index and returns it by value
     * @param index The index of the element to get
     * @return The value of the given element
     */
    template<typename T>
    T LinkedList<T>::operator[](unsigned int index)const{
        if(_head != 0){
            unsigned long count = 0;
            ListNode<T> *node = _head;

            while(node != 0){
                if(count == index){
                    return node->data();
                }
                node = node->tail();
                ++count;
            }
        }
        throw Error::ArgumentException("Index was out of bounds", Error::ErrorCode::ARGUMENT_EXCEPTION);
    }

    /**
     * Copy one list to another using the assignment operator
     * @param rhs The list on the right hand side of the operator
     * @return A reference to this list
     */
    template<typename T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs){
        LinkedList<T> cpy(rhs);
        swap(*this, cpy);

        return *this;
    }

    /******************************************************************************************************************/
    /******************************************************************************************************************/
    /******************************************************************************************************************/

    /**
     * Defines a basic stack based on the LinkedList class
     */
    template<typename T>
    class Stack{
    private:
        /**
         * A data list that backs the Stack structure
         */
        LinkedList<T> _data;
    public:
        void push(T);
        T pop();
        unsigned int size() const;
    };

    /**
     * Push a value onto the Stack
     * @param value The value to push onto the Stack
     */
    template<typename T>
    void Stack<T>::push(T value){
        _data.addFront(value);
    }

    /**
     * Pop a value off the Stack
     * @return The last value pushed onto the stack
     */
    template<typename T>
    T Stack<T>::pop(){
        T r = _data[0];

        _data.remove(0);

        return r;
    }

    /**
     * Get the size of the Stack
     * @return The size of this Stack in number of elements
     */
    template<typename T>
    unsigned int Stack<T>::size() const{
        return _data.size();
    }

    /******************************************************************************************************************/
    /******************************************************************************************************************/
    /******************************************************************************************************************/

    /**
     * Defines a basic queue based on the LinkedList class
     */
    template<typename T>
    class Queue{
    private:
        /**
         * A data list that backs the Queue structure
         */
        LinkedList<T> _data;
    public:
        void enqueue(T);
        T dequeue();
        unsigned int size() const;
    };

    /**
     * Enqueue a value in the Queue
     * @param value The value to be enqueued
     */
    template<typename T>
    void Queue<T>::enqueue(T value){
        _data.addBack(value);
    }

    /**
     * Dequeue a value from the Queue
     * @return The first value in the Queue
     */
    template<typename T>
    T Queue<T>::dequeue(){
        T r = _data[0];

        _data.remove(0);

        return r;
    }

    /**
     * Get the size of the Queue
     * @return The size of this Queue in number of elements
     */
    template<typename T>
    unsigned int Queue<T>::size() const{
        return _data.size();
    }

    /******************************************************************************************************************/
    /******************************************************************************************************************/
    /******************************************************************************************************************/

    /**
     * Defines a pair of a key and a value. Reduces the amount of data required to store a dictionary, and reduces
     * the amount of operations to preform a look up on a dictionary
     */
    template<typename TKey, typename TValue>
    class KeyValuePair{
    private:
        /**
         * The key for a  KeyValuePair
         */
        TKey _key;

        /**
         * The value for a KeyValuePair
         */
        TValue _value;
    public:
        KeyValuePair();
        KeyValuePair(TKey, TValue);
        TKey key() const;
        void key(TKey);
        TValue value() const;
        void value(TValue);
        TValue& valueref();
    };

    /**
     * Default KeyValuePair constructor
     */
    template<typename TKey, typename TValue>
    KeyValuePair<TKey, TValue>::KeyValuePair(){ }

    /**
     * Parameterized KeyValuePair constructor
     * @param key The key for this pair
     * @param value The value for this pair
     */
    template<typename TKey, typename TValue>
    KeyValuePair<TKey, TValue>::KeyValuePair(TKey key, TValue value){
        _key = key;
        _value = value;
    }

    /**
     * Get the key for this KeyValuePair
     * @return The current key for this pair
     */
    template<typename TKey, typename TValue>
    TKey KeyValuePair<TKey, TValue>::key() const{
        return _key;
    }

    /**
     * Set the key for this KeyValuePair
     * @param nKey The new key for this pair
     */
    template<typename TKey, typename TValue>
    void KeyValuePair<TKey, TValue>::key(TKey nKey){
        _key = nKey;
    }

    /**
     * Get the value for this KeyValuePair
     * @return The current value for this pair
     */
    template<typename TKey, typename TValue>
    TValue KeyValuePair<TKey, TValue>::value() const{
        return _value;
    }

    /**
     * Set the value for this KeyValuePair
     * @param nValue The new value for this pair
     */
    template<typename TKey, typename TValue>
    void KeyValuePair<TKey, TValue>::value(TValue nValue){
        _value = nValue;
    }

    /**
     * Get the value for this KeyValuePair
     * @return A reference to the value of this pair
     */
    template<typename TKey, typename TValue>
    TValue& KeyValuePair<TKey, TValue>::valueref(){
        return _value;
    }

    /******************************************************************************************************************/
    /******************************************************************************************************************/
    /******************************************************************************************************************/

    /**
     * Defines a Dictionary. A Dictionary is collection of KeyValuePair objects indexed by their keys. Depends directly
     * on LinkedList
     */
    template<typename TKey, typename TValue>
    class Dictionary{
    private:
        /**
         * A data list that backs the Dictionary structure
         */
        LinkedList<KeyValuePair<TKey, TValue>> _data;
    public:
        Dictionary();
        void addFront(TKey, TValue);
        void addBack(TKey, TValue);
        void remove(TKey);
        LinkedList<TKey> keys();
        LinkedList<TValue> values();
        unsigned int size();
        TValue& operator[](TKey);
        TValue operator[](TKey key) const;
    };

    /**
     * Default Dictionary Constructor
     */
    template<typename TKey, typename TValue>
    Dictionary<TKey, TValue>::Dictionary(){ }

    /**
     * Add an element to the beginning of the Dictionary. If the key already exists set the value to value.
     * @param key The key for this element
     * @param value The value for this element
     */
    template<typename TKey, typename TValue>
    void Dictionary<TKey, TValue>::addFront(TKey key, TValue value){
        if(keys().contains(key)){
            (*this)[key] = value;
        }
        else{
            _data.addFront(KeyValuePair<TKey, TValue>(key, value));
        }
    }

    /**
     * Add an element to the end of the Dictionary. If the key already exists set the value to value.
     * @param key The key for this element
     * @param value The value for this element
     */
    template<typename TKey, typename TValue>
    void Dictionary<TKey, TValue>::addBack(TKey key, TValue value){
        if(keys().contains(key)){
            (*this)[key] = value;
        }
        else{
            _data.addBack(KeyValuePair<TKey, TValue>(key, value));
        }
    }

    /**
     * Remove an element from the Dictionary
     * @param key The key of the element to remove.
     */
    template<typename TKey, typename TValue>
    void Dictionary<TKey, TValue>::remove(TKey key){
        for(unsigned long i = 0; i < _data.size(); ++i){
            if(_data[i].key() == key){
                _data.remove(i);
            }
        }
    }

    /**
     * Get a LinkedList of keys from the Dictionary
     * @return A LinkedList containing every key value in the Dictionary
     */
    template<typename TKey, typename TValue>
    LinkedList<TKey> Dictionary<TKey, TValue>::keys(){
        LinkedList<TKey> r;

        for(unsigned int i = 0; i < _data.size(); ++i){
            r.addBack(_data[i].key());
        }

        return r;
    }

    /**
     * Get a LinkedList of values from the Dictionary
     * @return A LinkedList containing every value in the Dictionary
     */
    template<typename TKey, typename TValue>
    LinkedList<TValue> Dictionary<TKey, TValue>::values(){
        LinkedList<TKey> r;

        for(unsigned int i = 0; i < _data.size(); ++i){
            r.addBack(_data[i].value());
        }

        return r;
    }

    /**
     * Get the size of the Dictionary
     * @return The size (in elements)
     */
    template<typename TKey, typename TValue>
    unsigned int Dictionary<TKey, TValue>::size(){
        return _data.size();
    }

    /**
     * Get a reference to the value of the input key
     * @param key The key of the value to return
     * @return A reference to the value at the given key
     */
    template<typename TKey, typename TValue>
    TValue& Dictionary<TKey, TValue>::operator[](TKey key){
        for(unsigned long i = 0; i < _data.size(); ++i){
            if(_data[i].key() == key){
                return _data[i].valueref();
            }
        }
        throw Error::ArgumentException("Key not found", Error::ErrorCode::ARGUMENT_EXCEPTION);
    }

    /**
     * Get the value of a key
     * @param key The key to get the value of
     * @return  The value of the given key
     */
    template<typename TKey, typename TValue>
    TValue Dictionary<TKey, TValue>::operator[](TKey key) const{
        for(unsigned long i = 0; i < _data.size(); ++i){
            if(_data[i].key() == key){
                return _data[i].valueref();
            }
        }
        throw Error::ArgumentException("Key not found (const)", Error::ErrorCode::ARGUMENT_EXCEPTION);
    }
}

#endif /* COLLECTIONS_H */

