#ifndef ARRAY_QUEUE_HPP
#define ARRAY_QUEUE_HPP
#include <stdexcept>

template <typename T>
class ArrayQueue
{
private:
    T* data;
    int count;
    int capacity;
     
    static const int INITIAL_CPACITY = 2;

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

template<typename T>
void ArrayQueue<T>::copy(const ArrayQueue<T>& other)
{
    free(); 
    count = other.count;
    capacity = other.capacity; 
    data = new T [capacity];
    for (size_t i = 0; i < count; i++)
    {
        data[i] = other.data[i];
    }
}

template<typename T>
void ArrayQueue<T>::free()
{
    delete[] data;
    count = 0;
    capacity = 0;

}

template<typename T>
void ArrayQueue<T>::resize(int newCapacity)
{
    capacity *= 2; 
    T* tmp = new T[capacity]; 
    for (size_t i = 0; i < count; i++)
    {
        tmp[i] = data[i]; 
    }
    delete[] data; 
    data = tmp;
}

template<typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& other)
{
    copy(other);
}

template<typename T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& other)
{
    if (this != &other)
    {
        free(); 
        copy(other);
    }
    return *this;
}

template<typename T>
ArrayQueue<T>::~ArrayQueue()
{
    free(); 
}

template<typename T>
 void ArrayQueue<T>::push(const T& value)
{
     if (capacity <= count)
     {
         resize();
     }
     data[count++] = value;
}

 template<typename T>
  void ArrayQueue<T>::pop()
 {
      if (empty())
      {
          throw std::out_of_range("No element to pop");
      }
      for (size_t i = 0; i < count - 1; i++)
      {
          data[i] = data[i + 1]; 
      }
      count--;
 }

  template<typename T>
  const T& ArrayQueue<T>::front() const
  {
      if (empty())
      {
          throw std::out_of_range("Queue is empty");

      }
      return data[0]; 
  }

  template<typename T>
 bool ArrayQueue<T>::empty() const
{
    return (count == 0);
}

 template<typename T>
  int ArrayQueue<T>::size() const
 {
     return count;
 }

template<typename T>
 ArrayQueue<T>::ArrayQueue()
     :count(0), capacity(0)
{
     data = new T[capacity];
}
