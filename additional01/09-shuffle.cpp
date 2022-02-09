#include <iostream>

/*
Нека е даден списък L с N елемента. Да се дефинира подходящо параметризирана функция shuffle,
която получава адреса на първия елемент на списъка. Функцията да пренарежда възлите на списъка така,
че елементите от втората половина на списъка да се преместят в началото на списъка, но в обратен ред
(при нечетен брой елементи считаме средния елемент за принадлежащ към първата половина на списъка).

    L1 -> L2 -> L3 -> L4 -> L5 ➡ L5 -> L4 -> L1 -> L2 -> L3

При решението на задачата да не се изтриват или заделят нови възли,
а да се използват съществуващите. Могат да се използват други изучени структури от данни.
*/

template <typename T>
struct Node
{
    T data;
    Node* next;

    Node(T data, Node* next = nullptr)
        : data(data), next(next) {}
};

template <typename T>
Node<T>* getSecondHalf(Node<T>* list)
{
    Node<T>* slow = list;
    Node<T>* fast = list;

    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node<T>* secondHalf = slow->next;
    slow->next = nullptr;
    return secondHalf;
}

template <typename T>
Node<T>* reverse(Node<T>* head) 
{
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    
    while (current)
    {
        Node<T>* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    head = prev;
    return head;  
}

template <typename T>
Node<T>* shuffle(Node<T>* head)
{
    Node<T>* secondHalf = getSecondHalf(head);
    Node<T>* end = secondHalf;
    secondHalf = reverse(secondHalf);
    end->next = head;
    return secondHalf;
}

void print(Node<int>* head)
{
    while (head)
    {
        std::cout << head->data << ' ';
        head = head->next;
    }
}

int main()
{
    Node<int>* head = new Node<int>(1, new Node<int>(2, new Node<int>(3, new Node<int>(4, new Node<int>(5)))));
    Node<int>* head2 = new Node<int>(1,new Node<int>(2, new Node<int>(3, new Node<int>(4, new Node<int>(5, 
                        new Node<int>(6, new Node<int>(7, new Node<int>(8, new Node<int>(9, new Node<int>(10))))))))));


    Node<int>* newHead = shuffle(head);
    print(newHead);

    Node<int>* newHead2 = shuffle(head2);
    std::cout << '\n';
    print(newHead2);
}