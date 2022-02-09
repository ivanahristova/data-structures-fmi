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
class LinkedQueue
{
private:
    Node<T>* head;
    Node<T>* tail;

    void copy(const LinkedQueue<T>& other);
    void free();
    void nullify();

public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue<T>& other);
    LinkedQueue(LinkedQueue<T>&& other) noexcept;
    LinkedQueue<T>& operator=(const LinkedQueue<T>& other);
    LinkedQueue<T>& operator=(LinkedQueue<T>&& other) noexcept;
    ~LinkedQueue();

    void enqueue(const T& value);
    void dequeue();

    T front() const;

    bool empty() const;
};

template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& other)
{
    Node<T>* iter = other.head;

    while(iter != nullptr)
    {
        enqueue(iter->data);
        iter = iter->next;
    }
}

template <typename T>
void LinkedQueue<T>::free()
{
    Node<T>* iter = head;
    while (iter != nullptr)
    {
        Node<T>* toDelete = iter;
        iter = iter->next;
        delete toDelete; 
    }
}

template <typename T>
void LinkedQueue<T>::nullify()
{
    head = nullptr;
    tail = nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue() 
    : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other) : LinkedQueue()
{
    copy(other);
}

template <typename T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T>&& other) noexcept
    : head(std::move(other.head)), tail(std::move(other.tail)) 
{
    other.nullify();
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T>&& other) noexcept
{
    free();

    head = std::move(other.head);
    tail = std::move(other.tail);

    other.nullify();

    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    free();
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& value)
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
void LinkedQueue<T>::dequeue()
{
    if (empty())
    {
        throw std::runtime_error("Pop called on an empty queue.");
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
T LinkedQueue<T>::front() const
{
    if (empty())
    {
        throw std::runtime_error("Front called on an empty queue.");
    }

    return head->data;
}

template <typename T>
bool LinkedQueue<T>::empty() const
{
    return head == nullptr;
}

int main()
{
    LinkedQueue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	std::cout << q.front() << std::endl; q.dequeue();
    std::cout << q.front() << std::endl; q.dequeue();
    std::cout << q.front() << std::endl; q.dequeue();
    std::cout << q.front() << std::endl; q.dequeue();
    std::cout << q.front() << std::endl; q.dequeue();

    std::cout << q.empty() << std::endl;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	LinkedQueue<int> q2 = q;
	std::cout << q2.front() << std::endl; 
    q2.dequeue();
	std::cout << q2.front() << std::endl; 
    q2.dequeue();
	std::cout << q2.front() << std::endl; 
    q2.dequeue();
	std::cout << q2.front() << std::endl; 
    q2.dequeue();
	std::cout << q2.front() << std::endl; 
    q2.dequeue();
}