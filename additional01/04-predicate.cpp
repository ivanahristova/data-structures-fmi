#include <iostream>

struct Node
{
    int data;
    Node* next;

    Node(int data, Node* next = nullptr)
        : data(data), next(next) {}
};

Node* filter(Node* head, bool (*pred)(int))
{
    Node* newHead = head;
    Node* iter = head;
    Node* end = head;
    Node* initialEnd = head;
    Node* prev = nullptr;

    while (end->next)
    {
        end = end->next;
    }

    initialEnd = end;

    while (iter != initialEnd)
    {
        if(!pred(iter->data))
        {
            Node* newEnd = iter;

            if (prev)
            {
                prev->next = iter->next;
            }
            else
            {
                newHead = iter->next;
            }

            iter = iter->next;
            newEnd->next = nullptr;
            end->next = newEnd;
            end = newEnd;
        }
        else
        {
            prev = iter;
            iter = iter->next;
        }
    }
    
    return newHead;
}

bool isEven(int data)
{
    return data % 2 == 0;
}

void print(Node* head)
{
    while (head)
    {
        std::cout << head->data << ' ';
        head = head->next;
    }
}

int main()
{
    Node* n5 = new Node(5);
    Node* n4 = new Node(4, n5);
    Node* n3 = new Node(3, n4);
    Node* n2 = new Node(2, n3);
    Node* n1 = new Node(1, n2);

    Node* head = filter(n1, &isEven);
    print(head);
}