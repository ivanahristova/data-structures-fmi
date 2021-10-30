#ifndef ARRAY_QUEUE_HPP
#define ARRAY_QUEUE_HPP

#include <stdexcept>

template <typename T>
class ArrayQueue
{
private:
    
    static const int INITIAL_CAPACITY = 8;
    T* data;
    int count;
    int capacity;
    int frontIndex;
    int backIndex;

    void copy(const ArrayQueue<T>& other);
    void free();
    void resize(int newCapacity);

public:
    ArrayQueue();
    ArrayQueue(const ArrayQueue<T>& other);
    ArrayQueue<T>& operator=(const ArrayQueue<T>& other);
    ~ArrayQueue();

    // Adds element to the back of the queue
    void push(const T& value);

    // Removes element from the front of the queue
    // Throws exception if queue is empty
    void pop();

    // Returns a constant reference to the first element of the queue
    // The first element of a queue is the element at the head (FIFO)
    const T& front() const;

    bool empty() const;
    int size() const;
};

template <typename T>
ArrayQueue<T>::ArrayQueue(): count(0), capacity(INITIAL_CAPACITY), frontIndex(0), backIndex(0) {
    data = new T[capacity];
}

template <typename T>
void ArrayQueue<T>::copy(const ArrayQueue<T>& other) {
    count = other.count;
    capacity = other.capacity;

    frontIndex = 0;
    backIndex = count;

    data = new T[capacity];
    for(int i = 0; i < count; i++) {
        data[i] = other.data[(i + other.frontIndex) % capacity];
    }
}

template <typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& other) {
    copy(other);
}

template <typename T>
void ArrayQueue<T>::free() {
    delete[] data;
}

template <typename T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& other) {
    if (this != &other) {
        free();
        copy(other);
    }

    return *this;
}

template <typename T>
ArrayQueue<T>::~ArrayQueue() {
    free();
}

template <typename T>
void ArrayQueue<T>::resize(int newCapacity) {
    T* const temp = data;
    data = new T[newCapacity];
    for(int i = 0; i < count; i++) {
        data[i] = temp[(i + frontIndex) % capacity];
    }

    capacity = newCapacity;
    frontIndex = 0;
    backIndex = count;

    delete temp;
}

template <typename T>
void ArrayQueue<T>::push(const T& value) {
    if (count == capacity) {
        resize (capacity * 2);
    }

    data[backIndex++] = value;
    backIndex %= capacity;

    count++;
}

template <typename T>
void ArrayQueue<T>::pop() {
    if(empty()) {
        throw new std::runtime_error("Trying to pop out of an empty queue!\n");
    }

    frontIndex++;
    frontIndex %= capacity;

    count--;
}

template <typename T>
const T& ArrayQueue<T>::front() const {
    if(empty()) {
        throw new std::runtime_error("Trying to access front element of empty queue!\n");
    }

    return data[frontIndex];
}

template <typename T>
bool ArrayQueue<T>::empty() const {
    return count == 0;
}

template <typename T>
int ArrayQueue<T>::size() const {
    return count;
}

#endif