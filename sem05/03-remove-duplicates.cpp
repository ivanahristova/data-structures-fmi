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
void removeDuplicates(Node<T>* head)
{
    Node<T>* iter = head;
    
    while (iter && iter->next)
    {
        if (iter->value == iter->next->value)
        {
            if (iter->next->next)
            {
                Node<T>* toDelete = iter->next;
                iter->next = iter->next->next;
                iter->next->prev = iter;
                delete toDelete;
            }
            else
            {
                Node<T>* toDelete = iter->next;
                iter->next = nullptr;
                delete toDelete;
            }
        }
        else
        {
            iter = iter->next;
        }
    }
}

template <typename T>
void print(Node<T>* head)
{
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
    Node<int>* n2 = new Node<int>(8, n1);
    Node<int>* n3 = new Node<int>(17, n2);
    Node<int>* n4 = new Node<int>(17, n3);
    Node<int>* n5 = new Node<int>(64, n4);
    Node<int>* n6 = new Node<int>(64, n5);
    Node<int>* n7 = new Node<int>(64, n6);
    Node<int>* n8 = new Node<int>(2, n7);
    Node<int>* n9 = new Node<int>(10, n8);
    Node<int>* n10 = new Node<int>(12, n9);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n7;
    n7->next = n8;
    n8->next = n9;
    n9->next = n10;

    removeDuplicates(n1);
    print(n1);
}
