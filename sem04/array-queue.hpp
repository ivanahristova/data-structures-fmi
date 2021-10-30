#ifndef ARRAY_QUEUE_HPP
#define ARRAY_QUEUE_HPP

template <typename T>
class ArrayQueue
{
private:
    T* data;
    int count;
    int capacity;

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

#endif