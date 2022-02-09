#include <iostream>
#include <stack>
#include <queue>

struct Node
{
    int data;
    Node* next;
    
    Node(int data, Node* next = nullptr)
        : data(data), next(next) {}
};

struct SNode
{
    std::stack<int> st;
    SNode* prev;
    SNode* next;

    SNode(std::stack<int> st, SNode* prev = nullptr, SNode* next = nullptr)
        : st(st), prev(prev), next(next) {}

};

struct QNode
{
    std::queue<int> q;
    QNode* prev;
    QNode* next;

    QNode(std::queue<int> q, QNode* prev = nullptr, QNode* next = nullptr)
        : q(q), prev(prev), next(next) {}

};

struct DNode
{
    Node* l;
    DNode* prev;
    DNode* next;

    DNode(Node* data, DNode* prev = nullptr, DNode* next = nullptr)
        : l(data), prev(prev), next(next) {}
};


DNode* intersection(SNode* stackList, QNode* queueList)
{
    DNode* start = nullptr;
    DNode* end = nullptr;

    while (stackList && queueList)
    {
        Node* newIntersection = nullptr;
        Node* endIntersection = nullptr;

        while (!stackList->st.empty() && !queueList->q.empty())
        {
            if (stackList->st.top() < queueList->q.front())
            {
                queueList->q.pop();
            }
            else if (stackList->st.top() > queueList->q.front())
            {
                stackList->st.pop();
            }
            else
            {
                Node* newNode = new Node(stackList->st.top());

                if (!newIntersection)
                {
                    newIntersection = newNode;
                    endIntersection = newNode;
                }
                else
                {
                    endIntersection->next = newNode;
                    endIntersection = newNode;
                }

                stackList->st.pop();
                queueList->q.pop();
            }
        }

        DNode* newNode = new DNode(newIntersection);

        if (!start)
        {
            start = newNode;
            end = newNode;
        }
        else if (start == end)
        {
            start->next = newNode;
            newNode->prev = start;
            end = newNode;
        }
        else
        {
            newNode->prev = end;
            end->next = newNode;
            end = newNode;
        }

        stackList = stackList->next;
        queueList = queueList->next;
    }

    return start;
}

void print(Node* head)
{
    if (head == nullptr)
    {
        std::cout << "[]";
        return;
    }

    Node* iter = head;
    std::cout << "[";
    while (iter->next)
    {
        std::cout << iter->data << "->";
        iter = iter->next;
    }
    std::cout << iter->data << "]";
}

void print(DNode* head)
{
    if (head == nullptr)
    {
        std::cout << "{}";
        return;
    }

    DNode* iter = head;
    std::cout << "{";
    while (iter->next)
    {
        print(iter->l);
        std::cout << " <-> ";
        iter = iter->next;
    }
    print(iter->l);
    std::cout << "}";
}

int main()
{
    std::stack<int> s1({1, 4, 5});
    std::stack<int> s2({6, 7, 8, 9});
    std::stack<int> s3({10, 11, 12});

    SNode* n1 = new SNode(s1);
    SNode* n2 = new SNode(s2, n1);
    SNode* n3 = new SNode(s3, n2);

    n1->next = n2;
    n2->next = n3;

    std::queue<int> q1({4, 1});
    std::queue<int> q2({14, 11, 10, 9, 8, 7, 6});
    std::queue<int> q3({12, 5});

    QNode* m1 = new QNode(q1);
    QNode* m2 = new QNode(q2, m1);
    QNode* m3 = new QNode(q3, m2);

    m1->next = m2;
    m2->next = m3;

    DNode* head = intersection(n1, m1);
    print(head);
}