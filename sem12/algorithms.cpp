#include "algorithms.hpp"

void connectedComponents(const Graph& g, int start, std::vector<bool>& visited)
{
    visited[start] = true;

    std::vector<std::pair<int, int>> successors;
    g.getSuccessors(start, successors);
    int successorsCount = successors.size();

    for (int i = 0; i < successorsCount; i++)
    {
         if (!visited[successors[i].first])
         {
             connectedComponents(g, successors[i].first, visited);
         }
    }
}

int getConnectedComponentsCount(const Graph& g)
{
    int vertices = g.getVerticesCount();
    std::vector<bool> visited(vertices, false);
    int count = 0;

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            connectedComponents(g, i, visited);
            count++;
        }
    }

    return count;
}

int minVertexBFS(const Graph& g, int start, std::vector<bool>& visited, const std::vector<int>& topValues)
{
    std::queue<int> q;
    q.push(start);
    visited[start];

    int min = topValues[start];

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        std::vector<std::pair<int, int>> successors;
        g.getSuccessors(current, successors);
        for (int i = 0; i < successors.size(); i++)
        {
            if (!visited[successors[i].first])
            {
                q.push(successors[i].first);

                if (topValues[successors[i].first] < min)
                {
                    min = topValues[successors[i].first];
                }

                visited[successors[i].first] = true;
            }
        }
    }

    return min;
}

int minValueOfConnectedComponents(const Graph& g, const std::vector<int>& topValues)
{
    int vertices = g.getVerticesCount();
    std::vector<bool> visited(vertices, false);

    int minSum = 0;
    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            minSum += minVertexBFS(g, i, visited, topValues);
        }
    }
    
    return minSum;
}

void Dijkstra(const Graph& g, int start, std::vector<int>& dist, std::vector<int>& prev)
{
    int vertices = g.getVerticesCount();
    std::vector<bool> visited(vertices);

    // initial values
    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    struct Edge 
    {
        int vertex;
        int distance;

        bool operator<(const Edge& other) const
        {
            return this->distance > other.distance;
        }
    };
    
    std::priority_queue<Edge> pq;
    pq.push({start, 0});
    dist[start] = 0;

    while (!pq.empty())
    {
        Edge current = pq.top();
        pq.pop();

        visited[current.vertex] = true;

        // if (dist[current.vertex] < current.distance)
        // {
        //      continue;
        // }

        std::vector<std::pair<int, int>> succ;
        g.getSuccessors(current.vertex, succ);

        for (int i = 0; i < succ.size(); i++)
        {
            int newDist = dist[current.vertex] + succ[i].second;
            if (newDist < dist[succ[i].first])
            {
                dist[succ[i].first] = newDist;
                prev[succ[i].first] = current.vertex;

                pq.push({succ[i].first, newDist});
            }
        }
    }
}


void DFS(const Graph& g, int start, std::vector<int>& path)
{
    std::vector<bool> visited(g.getVerticesCount());
    std::stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int current = s.top();
        s.pop();
        if (visited[current])
        {
            continue;
        }

        visited[current] = true;
        path.push_back(current);

        std::vector<std::pair<int, int>> successors;
		g.getSuccessors(current, successors);
        int successorsCount = successors.size();

        for (int i = 0; i < successorsCount; i++)
        {
            s.push(successors[i].first);
        }
    }
}

// unoriented graph
bool isConnected(const Graph& g)
{
	std::vector<int> path;
	DFS(g, 0, path);

	return path.size() == g.getVerticesCount();
}

bool containsCycleRecursiveCallVer1(const Graph& g, int start, std::vector<Color>& colors)
{
    colors[start] = GRAY;

    std::vector<std::pair<int, int>> succ;
    g.getSuccessors(start, succ);

    for (int i = 0; i < succ.size(); i++)
    {
        if (colors[succ[i].first] == GRAY)
        {
            return true;
        }
        else if (colors[succ[i].first] == WHITE)
        {
            bool foundCycle = containsCycleRecursiveCallVer1(g, succ[i].first, colors);
            if (foundCycle)
            {
                return true;
            }
        }
    }
    
    colors[start] = BLACK;
    return false;
}

bool containsCycleVer1(const Graph& g)
{
    int vertices = g.getVerticesCount();
    std::vector<Color> colors(vertices, WHITE);

    bool containsCycle = false;

    for (int i = 0; i < vertices; i++)
    {
        if (colors[i] == WHITE)
        {
            containsCycle = containsCycleRecursiveCallVer1(g, i, colors);

            if (containsCycle)
            {
                return true;
            }
        }
    }
    
    return containsCycle;
}

bool containsCycleRecursiveCallVer2(const Graph& g, int start, std::vector<bool>& visited, std::vector<bool>& st)
{
    visited[start] = true;

    std::vector<std::pair<int, int>> succ;
    g.getSuccessors(start, succ);

    for (int i = 0; i < succ.size(); i++)
    {
        if (st[succ[i].first])
        {
            return true;
        }

        if (!visited[succ[i].first])
        {
            bool foundCycle = containsCycleRecursiveCallVer2(g, succ[i].first, visited, st);
            if (foundCycle)
            {
                return true;
            }
        }
    }
    
    st[start] = false;
    return false;
}

bool containsCycleVer2(const Graph& g)
{
    int vertices = g.getVerticesCount();
    std::vector<bool> visited(vertices);
    std::vector<bool> visitation(vertices);

    bool containsCycle = false;

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            containsCycle = containsCycleRecursiveCallVer2(g, i, visited, visitation);

            if (containsCycle)
            {
                return true;
            }
        }
    }
    
    return containsCycle;
}

void topoSortDFS(const Graph& g, int start, std::vector<bool>& visited, std::stack<int>& st)
{
    visited[start] = true;
    std::vector<std::pair<int, int>> succ;
    g.getSuccessors(start, succ);

    for (int i = 0; i < succ.size(); i++)
    {
         if (!visited[succ[i].first])
         {
             topoSortDFS(g, succ[i].first, visited, st);
         }
    }

    st.push(start);
}

void topologicalSort(const Graph& g, std::vector<int>& order)
{
    if (containsCycleVer1(g))
    {
        return;
    }

    int vertices = g.getVerticesCount();
    std::vector<bool> visited(vertices);
    std::stack<int> sorting;

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            topoSortDFS(g, i, visited, sorting);
        }
    }
    
    while (!sorting.empty())
    {
        order.push_back(sorting.top());
        sorting.pop();
    }
}
