#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include <stdexcept>

template <typename T>
class CircularQueue
{
private:
    
    static const int INITIAL_CAPACITY = 8;
    T* data;
    int count;
    int capacity;
    int frontIndex;
    int backIndex;

    void copy(const CircularQueue<T>& other);
    void free();
    void resize(int newCapacity);

public:
    CircularQueue();
    CircularQueue(const CircularQueue<T>& other);
    CircularQueue<T>& operator=(const CircularQueue<T>& other);
    ~CircularQueue();

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
CircularQueue<T>::CircularQueue(): count(0), capacity(INITIAL_CAPACITY), frontIndex(0), backIndex(0) {
    data = new T[capacity];
}

template <typename T>
void CircularQueue<T>::copy(const CircularQueue<T>& other) {
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
CircularQueue<T>::CircularQueue(const CircularQueue<T>& other) {
    copy(other);
}

template <typename T>
void CircularQueue<T>::free() {
    delete[] data;
}

template <typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>& other) {
    if (this != &other) {
        free();
        copy(other);
    }

    return *this;
}

template <typename T>
CircularQueue<T>::~CircularQueue() {
    free();
}

template <typename T>
void CircularQueue<T>::resize(int newCapacity) {
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
void CircularQueue<T>::push(const T& value) {
    if (count == capacity) {
        resize (capacity * 2);
    }

    data[backIndex++] = value;
    backIndex %= capacity;

    count++;
}

template <typename T>
void CircularQueue<T>::pop() {
    if(empty()) {
        throw new std::runtime_error("Trying to pop out of an empty queue!\n");
    }

    frontIndex++;
    frontIndex %= capacity;

    count--;
}

template <typename T>
const T& CircularQueue<T>::front() const {
    if(empty()) {
        throw new std::runtime_error("Trying to access front element of empty queue!\n");
    }

    return data[frontIndex];
}

template <typename T>
bool CircularQueue<T>::empty() const {
    return count == 0;
}

template <typename T>
int CircularQueue<T>::size() const {
    return count;
}

#endif
