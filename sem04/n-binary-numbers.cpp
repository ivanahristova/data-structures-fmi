#include <iostream>
#include <string>
#include <queue>

void generate(int n)
{
    std::queue<std::string> q;
    q.push("1");

    for (int i = 0; i < n; i++)
    {
        q.push(q.front() + "0");
        q.push(q.front() + "1");

        std::cout << q.front() << ' ';
        q.pop();
    }
    std::cout << '\n';
}

int main()
{
    int n = 10;
    generate(n);

    n = 16;
    generate(n);
}