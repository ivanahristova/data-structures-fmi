#include <iostream>

template <typename T>
struct Node
{
    T value;
    Node<T>* next;

    Node(const T& value, Node<T>* next = nullptr) 
        : value(value), next(next) {}
};

// 1st solution
template <typename T>
T getElementN(Node<T>* head, int n)
{
    Node<T>* fast = head;
    Node<T>* slow = head;
    
    while (n > 0 && fast && fast->next)
    {
        fast = fast->next;
        n--;
    }

    while (slow && fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return slow->value;
}

// 2nd solution
template <typename T>
int getListLength(Node<T>* head)
{
    Node<T>* iter = head;
    int length = 0;

    while (iter)
    {
        iter = iter->next;
        length++;
    }

    return length;
}

template <typename T>
T getElementN_(Node<T>* head, int n)
{
    Node<T>* iter = head;
    int end = getListLength(head) - n;

    for (int i = 0; i < end; i++)
    {
        iter = iter->next;
    }

    return iter->value;
}

int main()
{
    Node<int>* n10 = new Node<int>(12, nullptr);
    Node<int>* n9 = new Node<int>(10, n10);
    Node<int>* n8 = new Node<int>(11, n9);
    Node<int>* n7 = new Node<int>(1, n8);
    Node<int>* n6 = new Node<int>(82, n7);
    Node<int>* n5 = new Node<int>(64, n6);
    Node<int>* n4 = new Node<int>(10, n5);
    Node<int>* n3 = new Node<int>(17, n4);
    Node<int>* n2 = new Node<int>(2, n3);
    Node<int>* n1 = new Node<int>(8, n2);

    std::cout << getElementN(n1, 3) << '\n';
    std::cout << getElementN_(n1, 7) << '\n';
}