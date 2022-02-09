#include <iostream>
#include <stack>
#include <vector>

struct Node
{
    std::stack<int> st;
    Node* next;

    Node(const std::stack<int>& st, Node* next = nullptr)
        : st(st), next(next) {}
};

struct Pair
{
    int length;
    int elements;

    Pair(int length, int elements)
        : length(length), elements(elements) {}
};

Pair getListSpecs(Node* head)
{
    int length = 0;
    int elements = 0;
    
    Node* iter = head;
    while (iter)
    {
        length++;
        elements += iter->st.size();

        iter = iter->next;
    }

    return Pair(length, elements);
}

void equalize(Node* head)
{
    Pair pair = getListSpecs(head);

    int totalElements = pair.elements;
    int stacks = pair.length;

    // средният брой елементи, които трябва да има във всеки стек, за да са равни
    int average = totalElements / stacks;

    // броят на стековете, които имат average+1 елементи
    int topOne = totalElements % stacks;

    // ще ползваме два пойтъра, защото не знаем положението им един спрямо друг
    Node* toFill = head; // стека, който искаме да пълним
    Node* filler = head; // стека, с който ще пълним

    // с 1 ще означаваме стековете, които са готови
    std::vector<bool> tampered(stacks, 0);
    int toFillIndex = 0;
    int fillerIndex = 0;

    bool foundToFill = false;
    bool foundFiller = false;

    while (toFill && filler)
    {
        if (!foundFiller)
        {
            int currentSize = filler->st.size();
        
            if (tampered[fillerIndex])
            {
                fillerIndex++;
                filler = filler->next;
            }
            else if (currentSize == average && topOne > 0)
            {
                fillerIndex++;
                filler = filler->next;
            }
            else if (currentSize == average && topOne == 0)
            {
                tampered[fillerIndex++] = true;
                filler = filler->next;
            }
            else if (currentSize == average + 1 && topOne > 0)
            {
                topOne--;
                tampered[fillerIndex++] = true;
                filler = filler->next;
            }
            else if (currentSize == average + 1 && topOne == 0)
            {
                foundFiller = true;
            }
            else if (currentSize > average + 1)
            {
                foundFiller = true;
            }
            else 
            {
                fillerIndex++;
                filler = filler->next;
            }
        }

        if (!foundToFill)
        {
            int currentSize = toFill->st.size();
            
            if (tampered[toFillIndex])
            {
                toFillIndex++;
                toFill = toFill->next;
            }
            else if (currentSize < average)
            {
                foundToFill = true;
            }
            else if (currentSize < average + 1 && topOne > 0)
            {
                foundToFill = true;
            }
            else if (currentSize == average + 1 && topOne > 0)
            {
                topOne--;
                tampered[toFillIndex++] = true;
                toFill = toFill->next;
            }
            else if (currentSize == average && topOne == 0)
            {
                tampered[toFillIndex++] = true;
                toFill = toFill->next;
            }
            else
            {
                toFillIndex++;
                toFill = toFill->next;
            }
        }

        if (foundToFill && foundFiller)
        {
            if (topOne)
            {
                if (toFillIndex < fillerIndex)
                {
                    while (filler->st.size() > average && toFill->st.size() < average + 1)
                    {
                        toFill->st.push(filler->st.top());
                        filler->st.pop();
                    }
                    
                    if (toFill->st.size() == average + 1)
                    {
                        topOne--;
                        tampered[toFillIndex++] = true;
                        toFill = toFill->next;
                    }

                    if (filler->st.size() == average + 1 && topOne > 0)
                    {
                        topOne--;
                        tampered[fillerIndex++] = true;
                        filler = filler->next;
                    }
                    else if (filler->st.size() == average && topOne == 0)
                    {
                        tampered[fillerIndex++] = true;
                        filler = filler->next;
                    }
                }
                else
                {
                    while (filler->st.size() > average + 1 && toFill->st.size() < average)
                    {
                        toFill->st.push(filler->st.top());
                        filler->st.pop();
                    }
                    
                    if (filler->st.size() == average + 1)
                    {
                        topOne--;
                        tampered[fillerIndex++] = true;
                        filler = filler->next;
                    }

                    if (toFill->st.size() == average && topOne == 0)
                    {
                        tampered[fillerIndex++] = true;
                        filler = filler->next;
                    }
                }
            } 
            else
            {
                while (filler->st.size() > average && toFill->st.size() < average)
                {
                    toFill->st.push(filler->st.top());
                    filler->st.pop();
                }
            }
            foundToFill = false;
            foundFiller = false;
        }
    }
}

void print(std::stack<int> st)
{
    std::cout << "[ ";
    while (!st.empty())
    {
        std::cout << st.top() << ' ';
        st.pop();
    }
    std::cout << "]";
}

void print(Node* head)
{
    Node* iter = head;
    while (iter->next)
    {
        print(iter->st);
        std::cout << " -> ";
        iter = iter->next;
    }
    print(iter->st);
}

int main()
{
    std::stack<int> s1({1, 4});
    std::stack<int> s2({6, 7, 8, 9, 5});
    std::stack<int> s3({10, 11, 12});
    std::stack<int> s4({1, 41});
    std::stack<int> s5({6, 7, 8, 9, 5, 7, 9, 0, 10, 20, 30});

    Node* head = new Node(s1, new Node(s2, new Node(s3, new Node(s4, new Node(s5)))));
    equalize(head);
    print(head);

    std::stack<int> s11({16});
    std::stack<int> s12({1, 2, 3, 4, 5, 12, 13});
    std::stack<int> s13({6, 7});
    std::stack<int> s14({8, 9, 10, 11, 11, 10, 100});

    Node* head1 = new Node(s11, new Node(s12, new Node(s13, new Node(s14))));
    equalize(head1);
    std::cout << '\n';
    print(head1);

    std::stack<int> s21({1, 4, 0, 11, 12});
    std::stack<int> s22({6, 7});
    std::stack<int> s23({10, 11, 12, 11, 10, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    std::stack<int> s24({1, 41});
    std::stack<int> s25({6, 7, 8, 9, 5, 7, 9, 0});

    Node* head2 = new Node(s21, new Node(s22, new Node(s23, new Node(s24, new Node(s25)))));
    equalize(head2);
    std::cout << '\n';
    print(head2);
}
