#include "adjacency-list-graph.hpp"

AdjListGraph::AdjListGraph(int vertices, bool oriented) 
    : Graph(vertices, oriented), adjList(vertices, std::list<Edge>()) {}

int AdjListGraph::addVertex()
{
    adjList.push_back(std::list<Edge>());
    return vertices++;
}

// 0 -> 2 // , 1
// // 1 -> 5, 6
// 1
// 2
// 3 -> 2, 4
// 4 -> 
// 5 -> // 1

void AdjListGraph::removeVertex(int vertex)
{
    if (!existsVertex(vertex))
    {
        throw std::runtime_error("Invalid vertrex");
    }

    adjList.erase(adjList.begin() + vertex);
    vertices--;

    for (int i = 0; i < vertices; i++)
    {
        for (std::list<Edge>::iterator it = adjList[i].begin(); it != adjList[i].end();)
        {
            if (it->end == vertex)
            {
                it = adjList[i].erase(it);
            }
            else if (it->end > vertex)
            {
                (it->end)--;
                it++;
            }
            else
            {
                it++;
            }
        }   
    }
}

void AdjListGraph::addEdge(int start, int end, int weight)
{
    if (!existsVertex(start) || !existsVertex(end))
    {
        return;
    }

    adjList[start].push_back(Edge(end, weight));

    if (!oriented)
    {
        adjList[end].push_back(Edge(end, weight));
    }
}

void AdjListGraph::removeEdge(int start, int end)
{
    if (!existsVertex(start) || !existsVertex(end))
    {
        return;
    }

    for (std::list<Edge>::iterator it = adjList[start].begin(); it != adjList[start].end();)
    {
        if (it->end == end)
        {
            it = adjList[start].erase(it);
        }
        else
        {
            it++;
        }
    }

    if (oriented)
    {
        return;
    }

    for (std::list<Edge>::iterator it = adjList[end].begin(); it != adjList[end].end();)
    {
        if (it->end == start)
        {
            adjList[end].erase(it);
        }
        else
        {
            it++;
        }
    }
}

void AdjListGraph::getSuccessors(int vertex, std::vector<std::pair<int, int>>& successors) const
{
    if (!existsVertex(vertex))
    {
        throw std::runtime_error("Invalid vertex");
    }

    for (auto i = adjList[vertex].begin(); i != adjList[vertex].end(); i++)
    {
        successors.push_back(std::make_pair(i->end, i->weight));
    }
}

void AdjListGraph::getPredecessors(int vertex, std::vector<std::pair<int, int>>& predecessors) const
{

}

bool AdjListGraph::adjacent(int start, int end) const
{
    if (!existsVertex(start) || !existsVertex(end))
    {
        return false;
    }

    for (auto i = adjList[start].begin(); i != adjList[start].end(); i++)
    {
        if (i->end == end)
        {
            return true;
        }
    }

    return false;
}

void AdjListGraph::getEdges(std::vector<std::tuple<int, int, int>>& edges) const
{
    for (int i = 0; i < adjList.size(); i++)
    {
        for(auto it = adjList[i].begin(); it != adjList[i].end(); it++)
        {
            edges.push_back(std::make_tuple(i, it->end, it->weight));
        }
    }
}
