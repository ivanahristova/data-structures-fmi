#include <iostream>
#include <stack>

struct Node
{
    int value;
    Node* next;

    Node(int value, Node* next)
        : value(value), next(next) {}
};

// Решение, предложено от вас 
Node* ReverseEveryK(Node* head, int k)
{
    std::stack<Node*> stack;
    
    Node* newhead = nullptr;
    Node* iter = nullptr;
    
    while(head)
    {
        int counter = 0;
        
        while(head && counter < k)
        {
            Node* afterHead = head->next;
            head->next = nullptr;
            stack.push(head);
            head = afterHead;
            ++counter;
        }
        
        if (!newhead)
        {
            newhead = stack.top();
            stack.pop();
            iter = newhead;
        }
        
        while(!stack.empty()) 
        {
            iter->next = stack.top();
            stack.pop();
            iter = iter->next;
        }
        
    }

    return newhead;
}

Node* reverseK(Node** current, int k)
{
    Node* prev = nullptr;
    int count = k;

    while (*current && count > 0)
    {
        Node* next = (*current)->next;
        (*current)->next = prev;

        prev = *current;
        *current = next;

        count--;
    }

    return prev;
}

Node* reverse(Node* head, int k)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node* current = head;

    Node* prev = reverseK(&current, k);
    head->next = reverse(current, k);
    return prev;
}

void push(Node** head, int data)
{
    Node* newNode = new Node(data, *head);
    *head = newNode;
}

void print(Node* head)
{
    if (head == nullptr)
    {
        std::cout << "[]";
        return;
    }

    Node* iter = head;
    std::cout << "[ ";
    while (iter->next)
    {
        std::cout << iter->value << " -> ";
        iter = iter->next;
    }
    std::cout << iter->value << " ]";
}

int main()
{
    int keys[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int size = sizeof(keys) / sizeof(keys[0]);

    Node* head = nullptr;
    for (int i = 0; i < size; i++)
    {
        push(&head, keys[i]);
    }

    print(head);
    head = reverse(head, 3);
    print(head);
    head = ReverseEveryK(head, 3);
    print(head);
    
}
