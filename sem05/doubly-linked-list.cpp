#include <iostream>
#include <stdexcept>

template <typename T>
struct Node 
{
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node<T>(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList;

template <typename T>
class Iterator 
{   
    friend class DoublyLinkedList<T>;
    Node<T>* position;         

public:
    Iterator(Node<T>* position = nullptr);

    bool valid() const;

    Iterator<T> prev() const;
    Iterator<T> next() const;

    const T& get() const;

    Iterator<T> operator++(int);
    Iterator<T>& operator++();

    Iterator<T> operator--(int);
    Iterator<T>& operator--();

    T& operator*();

    bool operator==(const Iterator<T>& it) const;
    bool operator!=(const Iterator<T>& it) const;

    operator bool() const;

    // +=
    // -=
    // ...

};

template <typename T>
Iterator<T>::Iterator(Node<T>* position)
    : position(position) {}

template <typename T>
bool Iterator<T>::valid() const
{
    return position != nullptr;
}

template <typename T>
Iterator<T> Iterator<T>::prev() const
{
    if (!valid())
    {
        return *this;
    }

    return Iterator<T>(position->prev);
}

template <typename T>
Iterator<T> Iterator<T>::next() const
{
    if (!valid())
    {
        return *this;
    }

    return Iterator<T>(position->next);
}

template <typename T>
const T& Iterator<T>::get() const
{
    return position->data;
}

// ++it (prefix)
template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
    *this = next();
    return *this;
}

// it++ (postfix)
template <typename T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> temp = *this;
    ++(*this);
    return temp;
}

// --it
template <typename T>
Iterator<T>& Iterator<T>::operator--()
{
    *this = prev();
    return *this;
}

// it--
template <typename T>
Iterator<T> Iterator<T>::operator--(int)
{
    Iterator<T> temp = *this;
    --(*this);
    return temp;
}

// (*it)
template <typename T>
T& Iterator<T>::operator*()
{
    return position->data;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& it) const
{
    return position == it.position;
}

// we must compare the positions in case of nullptr
template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& it) const
{
    return position != it.position;
}

// it <=> it.valid()
template <typename T>
Iterator<T>::operator bool() const
{
    return valid();
}

template <typename T>
class DoublyLinkedList 
{
    Node<T>* head;
    Node<T>* tail;

    void copy(const DoublyLinkedList<T>& other);
    void free();

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    DoublyLinkedList& operator=(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();

    bool empty() const;

    Iterator<T> insert(const Iterator<T>& pos, const T& data);
    Iterator<T> erase(Iterator<T> pos);
    Iterator<T> erase(Iterator<T> first, Iterator<T> last);

    void pushBack(const T& data);
    void pushFront(const T& data);
    void popBack();
    void popFront();

    Iterator<T> begin();
    Iterator<T> end();
    Iterator<T> beforeEnd();

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<U>& other);
};

template <typename T>
bool DoublyLinkedList<T>::empty() const 
{ 
    return head == nullptr;
}

template <typename T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T>& other)
{
    Node<T>* iter = other.head;

    while (iter != nullptr)
    {
        pushBack(iter->data);
        iter = iter->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::free() 
{
    while (!empty())
    {
        popFront();
    }
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() 
    : head(nullptr), tail(nullptr) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) 
    : head(nullptr), tail(nullptr)
{
    copy(other);
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) 
{
    if (this != &other) 
    {
        free();
        copy(other);
    }
    return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() 
{ 
    free();
}

template <typename T>  
void DoublyLinkedList<T>::pushFront(const T& data)
{
    Node<T>* newNode = new Node<T>(data);

    if (empty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T& data)
{
    Node<T>* newNode = new Node<T>(data);

    if (empty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

}

template <typename T>
void DoublyLinkedList<T>::popFront()
{
    if (empty())
    {
        return;
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
        head->next->prev = nullptr;
        head = head->next;
        delete toDelete;
    }
}

template <typename T>
void DoublyLinkedList<T>::popBack()
{
    if (empty())
    {
        return;
    }

    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node<T>* toDelete = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        delete toDelete;
    }
}

template <typename T>
Iterator<T> DoublyLinkedList<T>::insert(const Iterator<T>& it, const T& data)
{
    if (!it)
    {
        throw std::runtime_error("Invalid position");
    }

    if (it == begin())
    {
        pushFront(data);
        return begin();
    }
    else if (it == beforeEnd())
    {
        pushBack(data);
        return Iterator<T>(tail);
    }
    else
    {
        Node<T>* insertAt = it.position;
        Node<T>* newNode = new Node<T>(data);
        newNode->prev = insertAt->prev;
        newNode->next = insertAt;
        insertAt->prev->next = newNode;
        insertAt->prev = newNode;
        return Iterator<T>(newNode);
    }
}

template <typename T>
Iterator<T> DoublyLinkedList<T>::erase(Iterator<T> pos)
{
    Node<T>* toDelete = pos.position;

    if (toDelete == nullptr)
    {
        throw std::runtime_error("Empty list.");
    }

    if (toDelete->next == nullptr)
    {
        popBack();
        return end();
    }
    else if (toDelete->prev == nullptr)
    {
        popFront();
        return begin();
    }
    else
    {
        Node<T>* toReturn = toDelete->prev;
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        delete toDelete;
        return Iterator<T>(toReturn);
    }
}


template <typename T>
Iterator<T> DoublyLinkedList<T>::erase(Iterator<T> first, Iterator<T> last)
{
    Iterator<T> current = first;
    while (current != last)
    {
        current = erase(current).next();
        // current = current.next()
    }
    return current.prev();
}

template <typename T>
Iterator<T> DoublyLinkedList<T>::begin()
{
    return Iterator<T>(head);
}

// the end() iterator MUST point at the actual end
// example: for (std::list<T>::iterator it = l.begin(); it != end(); it++)
template <typename T>
Iterator<T> DoublyLinkedList<T>::end()
{
    return Iterator<T>(tail->next);
}

template <typename T>
Iterator<T> DoublyLinkedList<T>::beforeEnd()
{
    return Iterator<T>(tail);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& other)
{
    Node<T>* iter = other.head;
    
    if (iter == nullptr)
    {
        os << "[]";
        return os;
    }

    if (iter == other.tail)
    {
        os << "[ " << iter->data << " ]";
        return os;
    }

    os << "[ ";
    while (iter != other.tail)
    {
        os << iter->data << " <-> ";
        iter = iter->next;
    }
    os << iter->data << " ]";

    return os;
}

int main()
{
    DoublyLinkedList<int> s;
    s.pushFront(1);
    s.pushFront(10);
    s.pushFront(80);
    s.pushFront(19);
    s.pushFront(20);
    s.pushBack(2);
    s.pushBack(12);
    s.pushBack(11);
    s.pushBack(17);
    s.pushBack(18);

    Iterator<int> it(s.begin());

    std::cout << *(it.next()) << '\n';
    it++;
    ++it;
    std::cout << it.get() << '\n';

    for (Iterator<int> i = s.begin(); i != s.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout << '\n';

    it = s.erase(it);
    it++;
    it = s.erase(it);
    std::cout << s << '\n';

    Iterator<int> last = it.next();
    
    // += 3
    last++; 
    last++; 
    last++;

    it = s.erase(it.next(), last);
    std::cout << s << '\n';

    s.insert(it.next(), 3);
    std::cout << s << '\n';

    s.insert(s.begin(), 1);
    std::cout << s << '\n';

    s.insert(s.beforeEnd(), 80);
    std::cout << s << '\n';

    DoublyLinkedList<int> s1 = s;
    
    DoublyLinkedList<int> s2;
    s2.pushFront(14);
    s2.pushFront(18);
    s2.pushBack(10);

    std::cout << s2;
    s2 = s1;

    s1.pushFront(12);

    std::cout << s << '\n' << s1 << '\n' << s2 << '\n';
}