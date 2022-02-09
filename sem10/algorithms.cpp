#include "algorithms.hpp"

void BFS(const Graph& g, int start, std::vector<int>& order)
{
    if (!g.existsVertex(start))
    {
        return;
    }

    std::queue<int> q;
    std::vector<bool> visited(g.getVerticesCount());

    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        // order.push_back(current);

        std::vector<std::pair<int, int>> successors;
        g.getSuccessors(current, successors);

        for (int i = 0; i < successors.size(); i++)
        {
            if (visited[successors[i].first])
            {
                continue;
            }

            visited[successors[i].first] = true;
            q.push(successors[i].first);
        }
    }
}

void DFS(const Graph& g, int start, std::vector<int>& order)
{
    if (!g.existsVertex(start))
    {
        return;
    }

    std::stack<int> st;
    std::vector<bool> visited(g.getVerticesCount());

    st.push(start);

    while (!st.empty())
    {
        int current = st.top();
        st.pop();

        if (visited[current])
        {
            continue;
        }

        visited[current] = true;

        // order.push_back(current);

        std::vector<std::pair<int, int>> successors;
        g.getSuccessors(current, successors);

        for (int i = 0; i < successors.size(); i++)
        {
            st.push(successors[i].first);
        }
    }
}

void DFS_rec(const Graph& g, int start, std::vector<bool>& visited)
{
    visited[start] = true;

    std::vector<std::pair<int, int>> successors;
    g.getSuccessors(start, successors);

    for (int i = 0; i < successors.size(); i++)
    {
        if (!visited[successors[i].first])
        {
            DFS_rec(g, successors[i].first, visited);
        }
    }
}
