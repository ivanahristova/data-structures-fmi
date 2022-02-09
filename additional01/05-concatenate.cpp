#include <iostream>
#include <queue>
#include <vector>

template <typename T>
struct Node
{
    std::queue<T> data;
    Node<T>* next;

    Node(std::queue<T> data, Node<T>* next = nullptr)
        : data(data), next(next) {}

};

template <typename T>
bool validate(std::queue<T> q, bool (*pred)(T))
{
    while (!q.empty() && pred(q.front()))
    {
        q.pop();
    }

    return q.empty();
}

template <typename T>
void concatenateQueues(std::queue<T>& q1, std::queue<T>& q2)
{
    while (!q2.empty())
    {
        q1.push(q2.front());
        q2.pop();
    }
}

template <typename T>
void concatenate(Node<T>* head, bool (*pred)(T))
{
    Node<T>* iter = head;

    std::vector<bool> validation;

    while (iter)
    {
        validation.push_back(validate(iter->data, pred));
        iter = iter->next;
    }

    int index1 = 0;
    int index2 = 1;

    iter = head;
    while (iter && iter->next)
    {
        if (validation[index1] && validation[index2])
        {
            concatenateQueues(iter->data, iter->next->data);
            iter->next = iter->next->next;
            index2++;
        }
        else
        {
            index1++;
            index2++;
            iter = iter->next;
        }
    }
}

bool isUpperCase(char c)
{
    return c >= 'A' && c <= 'Z';
}

template <typename T>
void printQueue(std::queue<T> q)
{
    while (!q.empty())
    {
        std::cout << q.front() << ' ';
        q.pop();
    }
}

void print(Node<char>* head)
{
    Node<char>* iter = head;

    while (iter->next)
    {
        printQueue(iter->data);
        std::cout << " -> ";
        iter = iter->next;
    }
    printQueue(iter->data);
}

int main()
{
    std::queue<char> q1({'a', 'b', 'C', 'D'});
    std::queue<char> q2({'A', 'B'});
    std::queue<char> q3({'C', 'D'});
    std::queue<char> q4({'E', 'F', 'G'});
    std::queue<char> q5({'H', 'h', 'I'});

    Node<char>* n5 = new Node<char>(q5);
    Node<char>* n4 = new Node<char>(q4, n5);
    Node<char>* n3 = new Node<char>(q3, n4);
    Node<char>* n2 = new Node<char>(q2, n3);
    Node<char>* n1 = new Node<char>(q1, n2);

    print(n1);
    std::cout << '\n';
    concatenate(n1, &isUpperCase);
    print(n1);
}