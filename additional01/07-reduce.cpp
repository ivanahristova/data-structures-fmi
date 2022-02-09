#include <iostream>
#include <stdexcept>

template <class T>
struct Node
{
    T data;
    Node<T>* next;

    Node(T data, Node<T>* next = nullptr)
        : data(data), next(next) {}
};

template <typename T>
T reduce(Node<T>* head, T (*F)(const T&, const T&))
{
    if (!head)
    {
        throw std::runtime_error("Reduce called on an empty list");
    }

    if (!head->next)
    {
        return head->data;
    }

    head->data = F(head->data, head->next->data);
    Node<T>* toDelete = head->next;
    head->next = head->next->next;
    delete toDelete;
    return reduce(head, F);
}

int plus(const int& a, const int& b) 
{
    return a + b;
}

int div(const int& a, const int& b)
{
    return a / b;
}

template <typename T>
void free(Node<T>* list)
{
    while (list)
    {
        Node<T>* toDelete = list;
        list = list->next;
        delete toDelete;
    }
}

int main()
{
    // Node<int>* n5 = new Node<int>(3);
    // Node<int>* n4 = new Node<int>(2, n5);
    // Node<int>* n3 = new Node<int>(1, n4);
    // Node<int>* n2 = new Node<int>(0, n3);
    // Node<int>* n1 = new Node<int>(10, n2);

    // std::cout << reduce(n1, &plus);

    // free(n1);

    Node<int>* n14 = new Node<int>(2);
    Node<int>* n13 = new Node<int>(4, n14);
    Node<int>* n12 = new Node<int>(16, n13);
    Node<int>* n11 = new Node<int>(1024, n12);

    std::cout << reduce(n11, &div);

    free(n11);
}