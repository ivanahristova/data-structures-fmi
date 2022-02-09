#include <iostream>
#include <list>

void insert(std::list<int>& l, int x)
{
    std::list<int>::iterator it = l.begin();

    bool inserted = false;

    while (it != l.end())
    {
        if ((*it) >= x)
        {
            l.insert(it, x);
            inserted = true;
            break;
        }

        it++;
    }

    if (!inserted)
    {
        l.insert(it, x);
    }
}

void printList(const std::list<int>& list)
{
    for (int el : list) 
    {
        std::cout << el << " -> ";
    }
    std::cout << "end\n";
}

int main()
{
    std::list<int> l;
    l.push_front(6);
    l.push_front(5);
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);
    int x = 0;
    insert(l, x);
    x = 7;
    insert(l, x);
    x = 4;
    insert(l, x);
    printList(l);
}