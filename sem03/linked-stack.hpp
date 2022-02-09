#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class LinkedStack
{
private:
    Node<T>* head;
    int size;

    void copy(const LinkedStack<T>& other);
    void free();
    void nullify();

public:
    LinkedStack();
    LinkedStack(const LinkedStack<T>& other);
    LinkedStack(LinkedStack<T>&& other) noexcept;
    LinkedStack<T>& operator=(const LinkedStack<T>& other);
    LinkedStack<T>& operator=(LinkedStack<T>&& other) noexcept;
    ~LinkedStack();

    void push(const T& element);
    void pop();
    T& top();

    int getSize() const;
    bool isEmpty() const;

    void reverse();
    void print();
};

template <typename T>
void LinkedStack<T>::copy(const LinkedStack<T>& other)
{
    if (other.isEmpty())
    {
        head = nullptr;
        size = 0;
        return;
    }

    Node<T>* iterOther = other.head;
    head = new Node<T>(iterOther->data); 
    iterOther = iterOther->next;
    Node<T>* iterThis = head;

    while (iterOther != nullptr)
    {
        iterThis->next = new Node<T>(iterOther->data);
        iterOther = iterOther->next;
        iterThis = iterThis->next;
    }

    this->size = other.size;
}

template <typename T>
void LinkedStack<T>::free()
{
    Node<T>* iter = head;

    while (iter != nullptr)
    {
        Node<T>* toDelete = iter;
        iter = iter->next;
        delete toDelete;
    }

    head = nullptr;
    size = 0;
}

template <typename T>
void LinkedStack<T>::nullify()
{
    head = nullptr;
    size = 0;
}

template <typename T>
LinkedStack<T>::LinkedStack() : size(0), head(nullptr) {}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other)
{
    copy(other);
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T>&& rhs) noexcept
    : size(std::move(rhs.size)), head(std::move(rhs.head))
{
    rhs.nullify();
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T>&& other) noexcept
{
    // assert(this != &other);

    free();
    this->head = std::move(other.head);
    this->size = std::move(other.size);
    other.nullify();
    
    return *this;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    free();
}

template <typename T>
void LinkedStack<T>::push(const T& element)
{
    Node<T>* newNode = new Node<T>(element);

    if (!isEmpty())
    {
        newNode->next = head;
    }
    head = newNode;
    size++;
}

template <typename T>
void LinkedStack<T>::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("Pop called on an empty stack");
    }

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node<T>* temp = head->next;
        delete head;
        head = temp;
    }
    size--;
}

template <typename T>
T& LinkedStack<T>::top()
{
    if (isEmpty())
    {
        throw std::runtime_error("Top called on an empty stack");
    }

    return head->data;
}


template <typename T>
int LinkedStack<T>::getSize() const
{
    return size; // O(1)
    
    // Ако нямаме член-данна size,
    // то сложността на метода ще е линейна.

    /*
    int counter = 0;
    Node<T>* iter = head;

    while (iter != nullptr)
    {
        counter++;
        iter = iter->next;
    }

    return counter;
    */
}

template <typename T>
bool LinkedStack<T>::isEmpty() const
{
    return head == nullptr;  
}

template <typename T>
void LinkedStack<T>::reverse()
{
    if (isEmpty())
    {
        return;
    }

    Node<T>* iter = head;
    Node<T>* nextNode = new Node<T>(iter->data);
    iter = iter->next;

    while (iter != nullptr)
    {
        Node<T>* newNode = new Node<T>(iter->data);
        newNode->next = nextNode;
        nextNode = newNode;
        iter = iter->next;
    }

    free();
    head = nextNode;
}

template <typename T>
void LinkedStack<T>::print()
{
    if (head == nullptr)
    {
        std::cout << "[]";
        return;
    }

    Node<T>* iter = head;
    std::cout << '[';
    while (iter->next != nullptr)
    {
        std::cout << iter->data << " -> ";
        iter = iter->next;
    }
    std::cout << iter->data << ']' << '\n';
}

#endif
