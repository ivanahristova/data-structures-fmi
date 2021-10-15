#ifndef ARRAY_STACK_HPP
#define ARRAY_STACK_HPP

#include <stdexcept>

template <typename T>
class ArrayStack
{
    static const int INITIAL_CAPACITY = 16;
    T* data;
    int size;
    int capacity;

    void free();
    void copy(const ArrayStack<T>& other);
    void resize(int size);

public:
    ArrayStack();
    ArrayStack(const ArrayStack<T>& other);
    ArrayStack<T>& operator=(const ArrayStack<T>& other);
    ~ArrayStack();

    void push(const T& element);
    void pop();
    const T& top() const;

    int getSize() const;
    bool empty() const;
};

template <typename T>
void ArrayStack<T>::free()
{
    delete[] data;
}

template <typename T>
void ArrayStack<T>::copy(const ArrayStack<T>& other)
{
    this->size = other.size;
    this->capacity = other.capacity;
    data = new T[other.capacity];

    for (int i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }   
}

template <typename T>
void ArrayStack<T>::resize(int newCapacity)
{
    T* temp = data;
    data = new T[newCapacity];

    for (int i = 0; i < size; i++)
    {
        data[i] = temp[i];
    }
    
    capacity = newCapacity;
    delete[] temp;
}

template <typename T>
ArrayStack<T>::ArrayStack(): size(0), capacity(INITIAL_CAPACITY)
{
    data = new T[capacity];
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& other)
{
    copy(other);
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return this;
}

template <typename T>
ArrayStack<T>::~ArrayStack()
{
    free();
}

template <typename T>
void ArrayStack<T>::push(const T& element)
{
    if (size == capacity)
    {
        resize(capacity * 2);
    }

    data[size++] = element;
}

template <typename T>
void ArrayStack<T>::pop()
{
    if (empty())
    {
        throw std::runtime_error("Pop called on an empty stack!");
    }

    size--;

    if (size * 2 <= capacity && capacity > 1)
	{
        resize(capacity / 2);
    }
}

template <typename T>
const T& ArrayStack<T>::top() const
{
    if (empty())
    {
        throw std::runtime_error("Top called on an empty stack!");
    }

    return data[size - 1];
}

template <typename T>
int ArrayStack<T>::getSize() const
{
    return size;
}

template <typename T>
bool ArrayStack<T>::empty() const
{
    return size == 0;
}

#endif