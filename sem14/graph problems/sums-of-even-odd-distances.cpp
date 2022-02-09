#include <iostream>
#include <vector>
#include <queue>

class Graph
{
    int vertices;
    std::vector<std::vector<int>> adjList;

public:
    Graph(int vertices) : vertices(vertices), adjList(vertices, std::vector<int>()) {}

    Graph(int vertices, std::vector<std::pair<int, int>> edges) : Graph(vertices)
    {
        int edgesCount = edges.size();
        for (int i = 0; i < edgesCount; i++)
        {
            adjList[edges[i].first].push_back(edges[i].second);
        }
    }

    void getEvenSumOddSum(int start, int& odd, int& even)
    {
        std::queue<std::pair<int, bool>> q; // true -> even
        std::vector<bool> visited(vertices, false);

        q.push({start, true});
        visited[start] = true;

        while (!q.empty())
        {
            std::pair<int, bool> current = q.front();
            q.pop();

            if (current.second)
            {
                even += current.first;
            }
            else
            {
                odd += current.first;
            }

            int size = adjList[current.first].size();
            for (int i = 0; i < size; i++)
            {
                int neightbour = adjList[current.first][i];
                if (!visited[neightbour])
                {
                    q.push(std::make_pair(neightbour, !current.second));
                    visited[neightbour] = true;
                }
            }
        }
    }
};

int main()
{
    //  ┌------------┐
    //  |            |     
    //  |   (1) ←-- (0) ---→ (4)
    //  |    |\              /
    //  |    | \            /
    //  |    |  └ → (2)    /
    //  |    |       ↑    /
    //  |    |      /    /
    //  |    |     /    /
    //  |    |    /    /
    //  |    |   /    /
    //  |    |  /    /
    //  |    | /    /
    //  |    ↓/    /
    //  └-→ (3) ←-┘


    int n = 5;
    int m = 7;
    std::vector<std::pair<int, int>> edges = 
    {{0, 4}, {0, 3}, {0, 1}, 
    {1, 3}, {1, 2}, {3, 2}, {4, 3}};

    Graph g(n, edges);
    int start = 0;
    int even = 0, odd = 0;
    g.getEvenSumOddSum(start, even, odd);
    std::cout << "Even: " << even << "\nOdd: " << odd;
    std::cout << '\n';

    // (7) -> (8)
    // 
    // (4) -------> (5)
    //  \           /
    //   \         /
    //    \> (6) </
    // 
    // ...
    // 
    // Започвайки от 0, обхождаме само нейната свързана компонента

    int n1 = 9;
    int m1 = 8;
    std::vector<std::pair<int, int>> edges1 = 
    {{7, 8}, {4, 5}, {4, 6}, {5, 6}, 
    {2, 1}, {0, 3}, {0, 1}, {2, 3}};

    Graph g1(n1, edges1);
    int start1 = 0;
    int even1 = 0, odd1 = 0;
    g1.getEvenSumOddSum(start1, even1, odd1);
    std::cout << "Even: " << even1 << "\nOdd: " << odd1;  
}