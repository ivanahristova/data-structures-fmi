#include <iostream>

template <typename T>
struct Node
{
    T value;
    Node<T>* next;

    Node(const T& value, Node<T>* next = nullptr) 
        : value(value), next(next) {}
};

template <typename T>
bool containsCycle(Node<T>* head)
{
    Node<T>* slow = head;
    Node<T>* fast = head;

    bool hasCycle = false;
    while (slow && fast && fast->next && !hasCycle)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            hasCycle = true;
        }
    }

    return hasCycle;
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
    // n10->next = n7;

    std::cout << containsCycle(n1);
}