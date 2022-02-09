#include <iostream>
#include <stdexcept>

template <typename T>
struct Node
{
    T value;
    Node<T>* next;

    Node<T>(const T& value)
        : value(value), next(nullptr) {}
};

template <typename T>
class SinglyLinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;

    void copy(const SinglyLinkedList<T>& other);
    void free();

    void swap(SinglyLinkedList<T>& other);

public:
    SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList<T>& other);
    SinglyLinkedList(SinglyLinkedList<T>&& other);
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
    SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&& other);
    ~SinglyLinkedList();

    void clear(); // clears the contents

    void pushFront(const T& value); // O(1)
    void pushBack(const T& value); // O(1)

    void popFront(); // O(1)
    void popBack(); // O(n)

    const T& front(); // O(1)
    const T& back(); // O(1)

    bool empty();

    template <typename U>
    friend void swap(SinglyLinkedList<U>& lhs, SinglyLinkedList<U> rhs);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<U>& other);
};

template <typename T>
void SinglyLinkedList<T>::copy(const SinglyLinkedList<T>& other)
{
    Node<T>* iter = other.head;

    while (iter != nullptr)
    {
        pushBack(iter->value);
        iter = iter->next;
    }
}

template <typename T>
void SinglyLinkedList<T>::free()
{
    while(!empty())
    {
        popFront();
    }

    head = nullptr;
    tail = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::swap(SinglyLinkedList<T>& other)
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
    : head(nullptr), tail(nullptr) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
    : head(nullptr), tail(nullptr)
{
    copy(other);
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other)
    : head(std::move(other.head)), tail(std::move(other.tail))
{
    other.head = nullptr;
    other.tail = nullptr;
}

// assignment operator has a strong runtime_error guarantee
// using the copy-and-swap idiom
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
    SinglyLinkedList<T> temp(other);
    swap(temp);
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other)
{
    SinglyLinkedList<T> temp(std::move(other));
    swap(temp);
    return *this;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    free();
}

template <typename T>
void SinglyLinkedList<T>::clear()
{
    free();
}

template <typename T>
void SinglyLinkedList<T>::pushFront(const T& value)
{
    Node<T>* newNode = new Node<T>(value);

    if (empty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

template <typename T>
void SinglyLinkedList<T>::pushBack(const T& value)
{
    Node<T>* newNode = new Node<T>(value);

    if (empty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename T>
void SinglyLinkedList<T>::popFront()
{
    if (empty())
    {
        throw std::runtime_error("Empty list.");
    }

    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node<T>* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

template <typename T>
void SinglyLinkedList<T>::popBack()
{
    if (empty())
    {
        throw std::runtime_error("Empty list.");
    }

    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node<T>* newTail = head;

        while (newTail->next != tail)
        {
            newTail = newTail->next;
        }

        delete tail;
        newTail->next = nullptr;
        tail = newTail;
    }

}

template <typename T>
const T& SinglyLinkedList<T>::front()
{
    if (empty())
    {
        throw std::runtime_error("Empty list.");
    }

    return head->value;
}

template <typename T>
const T& SinglyLinkedList<T>::back()
{
    if (empty())
    {
        throw std::runtime_error("Empty list.");
    }

    return tail->value;
}

template <typename T>
bool SinglyLinkedList<T>::empty()
{
    return head == nullptr;
}

template <typename T>
void swap(SinglyLinkedList<T>& lhs, SinglyLinkedList<T> rhs)
{
    lhs.swap(rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& other)
{
Node<T>* iter = other.head;
    
    if (iter == nullptr)
    {
        os << "[]";
        return os;
    }

    if (iter == other.tail)
    {
        os << "[ " << iter->value << " ]";
        return os;
    }

    os << "[ ";
    while (iter != other.tail)
    {
        os << iter->value << " -> ";
        iter = iter->next;
    }
    os << iter->value << " ]";

    return os;
}

int main()
{
    SinglyLinkedList<int> s;
    s.pushFront(1);
    s.pushBack(2);
    s.popFront();
    s.pushBack(12);
    s.pushFront(10);
    s.popBack();

    SinglyLinkedList<int> s1 = s;
    SinglyLinkedList<int> s2;
    s2.pushFront(14);
    s2.pushFront(18);
    s2.pushBack(10);

    std::cout << s2 << '\n';
    s2 = s1;

    s1.pushFront(12);
    s2.clear();

    std::cout << s << '\n' << s1 << '\n' << s2 << '\n';
}