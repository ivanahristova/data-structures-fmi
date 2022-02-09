#include <iostream>

struct DNode
{
    int data;
    DNode* prev;
    DNode* next;

    DNode(int data, DNode* prev = nullptr, DNode* next = nullptr)
        : data(data), prev(prev), next(next) {}
};

struct SNode
{
    DNode* data;
    SNode* next;

    SNode(DNode* data, SNode* next = nullptr)
        : data(data), next(next) {}
};

DNode* getSecondHalf(DNode* list)
{
    DNode* slow = list;
    DNode* fast = list;

    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    DNode* secondHalf = slow->next;
    slow->next = nullptr;
    return secondHalf;
}

DNode* merge(DNode* first, DNode* second)
{
    if (!first)
    {
        return second;
    }

    if (!second)
    {
        return first;
    }

    if (first->data <= second->data)
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

DNode* mergeSort(DNode* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    DNode* secondHalf = getSecondHalf(head);
    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);

    return merge(head, secondHalf);
}

struct Interval
{
    int low;
    int high;

    Interval(int low, int high)
        : low(low), high(high) {}
};

Interval getInterval(DNode* list)
{
    Interval interval(list->data, 0);

    while (list->next)
    {
        list = list->next;
    }

    interval.high = list->data;
    return interval;
}

bool intersect(Interval i1, Interval i2)
{
    return !(i1.high < i2.low || i2.high < i1.low);
}

void filter(SNode* list)
{
    SNode* iter = list;

    while (iter && iter->next)
    {
        Interval int1 = getInterval(iter->data);
        Interval int2 = getInterval(iter->next->data);

        if (intersect(int1, int2))
        {
            iter->next = iter->next->next;
        }
        else
        {
            iter = iter->next;
        }
    }
}

void print(DNode* head)
{
    if (head == nullptr)
    {
        std::cout << "[]";
        return;
    }

    DNode* iter = head;
    std::cout << "[";
    while (iter->next)
    {
        std::cout << iter->data << "->";
        iter = iter->next;
    }
    std::cout << iter->data << "]";
}

void print(SNode* head)
{
    if (head == nullptr)
    {
        std::cout << "{}";
        return;
    }

    SNode* iter = head;
    std::cout << "{";
    while (iter->next)
    {
        print(iter->data);
        std::cout << " <-> ";
        iter = iter->next;
    }
    print(iter->data);
    std::cout << "}";
}

void sort(SNode* list)
{
    SNode* iter = list;

    while (iter) 
    {
        DNode* sorted = mergeSort(iter->data);
        iter->data = sorted;
        iter = iter->next;
    }
}

int main()
{
    // SNode* l1 = new SNode(10, new SNode(1, new SNode(2, new SNode(3, new SNode(6, new SNode(-3, new SNode(-3, new SNode(-3, new SNode(-3, nullptr)))))))));
    // SNode* l2 = new SNode(12, new SNode(10, new SNode(-10, new SNode(10, nullptr))));
    // SNode* l3 = new SNode(1, new SNode(2, new SNode(2, new SNode(3, new SNode(6, new SNode(8, new SNode(5, new SNode(-3, new SNode(3, nullptr)))))))));

    // DNode* n1 = new DNode(l1);
    // DNode* n2 = new DNode(l2, n1);
    // DNode* n3 = new DNode(l3, n2);

    // n1->next = n2;
    // n2->next = n3;

    DNode* n1 = new DNode(3);
    DNode* n2 = new DNode(5, n1);
    DNode* n3 = new DNode(1, n2);
    DNode* n4 = new DNode(7, n3);
    DNode* n5 = new DNode(4, n4);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

    DNode* n6 = new DNode(4);
    DNode* n7 = new DNode(7, n6);
    DNode* n8 = new DNode(1, n7);

    n6->next = n7;
    n7->next = n8;

    DNode* n9 = new DNode(5);
    DNode* n10 = new DNode(3, n9);
    
    n9->next = n10;

    DNode* n11 = new DNode(10);
    DNode* n12 = new DNode(12, n11);
    
    n11->next = n12;

    SNode* l1 = new SNode(n1);
    SNode* l2 = new SNode(n6);
    SNode* l3 = new SNode(n9);
    SNode* l4 = new SNode(n11);

    l1->next = l2;
    l2->next = l3;
    l3->next = l4;
    
    sort(l1);
    print(l1);

    std::cout << '\n';
    
    filter(l1);
    print(l1);
}