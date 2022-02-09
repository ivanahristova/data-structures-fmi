#include <iostream>

struct SNode
{
    int data;
    SNode* next;

    SNode(int data, SNode* next = nullptr)
        : data(data), next(next) {}
};

struct DNode
{
    SNode* data;
    DNode* prev;
    DNode* next;

    DNode(SNode* data, DNode* prev = nullptr, DNode* next = nullptr)
        : data(data), prev(prev), next(next) {}
};

int getListLength(DNode* list)
{
    int length = 0;

    while (list)
    {
        length++;
        list = list->next;
    }

    return length;
}

int getNumber(SNode* list)
{
    int number = 0;

    while (list)
    {
        number *= 10;
        number += list->data;
        list = list->next;
    }

    return number;
}

bool isValid(DNode* list)
{
    int half = getListLength(list) / 2;

    DNode* iter = list;

    int counter = 0;
    while (++counter < half)
    {
        if (getNumber(iter->data) > getNumber(iter->next->data))
        {
            return false;
        }

        iter = iter->next;
    }

    iter = iter->next;

    counter = 0;
    while (++counter < half)
    {
        if (getNumber(iter->data) < getNumber(iter->next->data))
        {
            return false;
        }

        iter = iter->next;
    }

    return true;
}

void free(SNode* list)
{
    while (list)
    {
        SNode* toDelete = list;
        list = list->next;
        delete toDelete;
    }
}

void free(DNode* list)
{
    while (list)
    {
        DNode* toDelete = list;
        free(list->data);
        list = list->next;
        delete toDelete;
    }
}

int main()
{
    SNode* n11 = new SNode(1);
    SNode* n12 = new SNode(0);
    SNode* n13 = new SNode(0);

    n11->next = n12;
    n12->next = n13;

    SNode* n21 = new SNode(1);
    SNode* n22 = new SNode(0);
    SNode* n23 = new SNode(0);

    n21->next = n22;
    n22->next = n23;

    SNode* n31 = new SNode(3);
    SNode* n32 = new SNode(8);
    SNode* n33 = new SNode(1);

    n31->next = n32;
    n32->next = n33;

    SNode* n41 = new SNode(4);
    SNode* n42 = new SNode(8);
    SNode* n43 = new SNode(1);

    n41->next = n42;
    n42->next = n43;

    SNode* n51 = new SNode(3);
    SNode* n52 = new SNode(3);
    SNode* n53 = new SNode(3);

    n51->next = n52;
    n52->next = n53;

    SNode* n61 = new SNode(2);
    SNode* n62 = new SNode(8);
    SNode* n63 = new SNode(1);

    n61->next = n62;
    n62->next = n63;

    DNode* n1 = new DNode(n11, nullptr);
    DNode* n2 = new DNode(n21, n1);
    DNode* n3 = new DNode(n31, n2);
    DNode* n4 = new DNode(n41, n3);
    DNode* n5 = new DNode(n51, n4);
    DNode* n6 = new DNode(n61, n6);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;

    std::cout << isValid(n1);

    free(n1);
}