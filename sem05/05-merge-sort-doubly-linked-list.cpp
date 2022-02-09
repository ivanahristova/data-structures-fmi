#include <iostream>

template <typename T>
struct Node
{
    T value;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& value, Node<T>* prev = nullptr, Node<T>* next = nullptr) 
        : value(value), prev(prev), next(next) {}
};

template <typename T>
Node<T>* merge(Node<T>* first, Node<T>* second)
{
    if (first == nullptr)
    {
        return second;
    }

    if (second == nullptr)
    {
        return first;
    }

    if (first->value <= second->value)
    {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = nullptr;
        return first;
    }
    else
    {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = nullptr;
        return second;
    }

}

template <typename T>
Node<T>* getSecondHalf(Node<T>* head)
{
    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node<T>* secondHalf = slow->next;
    slow->next = nullptr;
    return secondHalf;
}

template <typename T>
Node<T>* mergeSort(Node<T>* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    Node<T>* secondHalf = getSecondHalf(head);

    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);
    return merge(head, secondHalf);
}


template <typename T>
void print(Node<T>* head)
{
    if (head == nullptr)
    {
        std::cout << "[]";
        return;
    }

    Node<T>* iter = head;

    std::cout << "[ ";
    while (iter->next)
    {
        std::cout << iter->value << " <-> ";
        iter = iter->next;
    }
    std::cout << iter->value << " ]";
}

int main()
{
    Node<int>* n1 = new Node<int>(8);
    Node<int>* n2 = new Node<int>(2, n1);
    Node<int>* n3 = new Node<int>(17, n2);
    Node<int>* n4 = new Node<int>(1, n3);
    Node<int>* n5 = new Node<int>(6, n4);
    Node<int>* n6 = new Node<int>(4, n5);
    Node<int>* n7 = new Node<int>(64, n6);
    Node<int>* n8 = new Node<int>(12, n7);
    Node<int>* n9 = new Node<int>(10, n8);
    Node<int>* n10 = new Node<int>(3, n9);
    
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n7;
    n7->next = n8;
    n8->next = n9;
    n9->next = n10;

    Node<int>* sorted = mergeSort(n1);
    print(sorted);
}