#include <iostream>
#include <forward_list>

std::forward_list<int> merge(std::forward_list<int>& l1, std::forward_list<int>& l2)
{
    std::forward_list<int>::iterator it1 = l1.begin();
    std::forward_list<int>::iterator it2 = l2.begin();

    std::forward_list<int> l;
    std::forward_list<int>::iterator it = l.before_begin();

    while (it1 != l1.end() && it2 != l2.end())
    {
        if ((*it1) <= (*it2))
        {
            l.insert_after(it, *it1);
            it++;
            it1++;
        }
        else
        {
            l.insert_after(it, *it2);
            it++;
            it2++;
        }
    }

    while (it1 != l1.end())
    {
        l.insert_after(it, *it1);
        it++;
        it1++;
    }

    while (it2 != l2.end())
    {
        l.insert_after(it, *it2);
        it++;
        it2++;
    }

    return l;
}

int main()
{
    std::forward_list<int> l1;
    l1.push_front(20);
    l1.push_front(16);
    l1.push_front(8);
    l1.push_front(4);
    l1.push_front(1);
    std::forward_list<int> l2;
    l2.push_front(15);
    l2.push_front(5);
    l2.push_front(3);
    l2.push_front(1);
    l2.push_front(0);

    std::forward_list<int> l = merge(l1, l2);

    for (std::forward_list<int>::iterator it = l.begin(); it != l.end(); it++)
    {
        std::cout << *it << ' ';
    }
    
}
