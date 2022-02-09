#include <iostream>

struct Node
{
    int value;
    Node* next;

    Node(const int& value, Node* next = nullptr)
        : value(value), next(next) {}
};

Node* rearrange(Node* head)
{
    Node* evenHead = nullptr;
    Node* evenTail = nullptr;

    Node* oddHead = nullptr;
    Node* oddTail = nullptr;

    Node* iter = head;
    while (iter)
    {
        if (iter->value % 2 == 0)
        {
            if (evenHead == nullptr)
            {
                evenHead = iter;
                evenTail = iter;
            }
            else
            {
                evenTail->next = iter;
                evenTail = iter;
            }
        }
        else
        {
            if (oddHead == nullptr)
            {
                oddHead = iter;
                oddTail = iter;
            }
            else
            {
                oddTail->next = iter;
                oddTail = iter;
            }
        }

        iter = iter->next;
    }

    if (evenTail)
    {
        evenTail->next = oddHead;
    }

    if (oddTail)
    {
        oddTail->next = nullptr;
    }

    return evenHead ? evenHead : oddHead;
}

void print(Node* head)
{
    if (head == nullptr)
    {
        std::cout << "[]";
        return;
    }

    Node* iter = head;
    while (iter->next)
    {
        std::cout << iter->value << " -> ";
        iter = iter->next;
    }
    std::cout << iter->value << " ]";
}

int main()
{
    Node* n1 = new Node(3);
    Node* n2 = new Node(8);
    Node* n3 = new Node(1);
    Node* n4 = new Node(7);
    Node* n5 = new Node(4);
    Node* n6 = new Node(2);
    Node* n7 = new Node(9);
    Node* n8 = new Node(6);
    Node* n9 = new Node(5);
    Node* n10 = new Node(0);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n7;
    n7->next = n8;
    n8->next = n9;
    n9->next = n10;

    Node* newNode = rearrange(n1);
    print(newNode);
}
