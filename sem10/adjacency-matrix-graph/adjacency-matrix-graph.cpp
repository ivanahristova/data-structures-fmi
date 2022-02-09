#include "adjacency-matrix-graph.hpp"

AdjMatrixGraph::AdjMatrixGraph(int vertices, bool oriented)
    : Graph(vertices, oriented), matrix(vertices, std::vector<int>(vertices, 0))
{

}

int AdjMatrixGraph::addVertex()
{
    matrix.push_back(std::vector<int>(vertices + 1, 0));

    for (int i = 0; i < vertices; i++)
    {
        matrix[i].push_back(0);
    }

    return vertices++;
}

void AdjMatrixGraph::removeVertex(int vertex)
{
    if (!existsVertex(vertex))
    {
        throw std::runtime_error("Invalid vertex");
    }

    // 0 ... n-1

    matrix.erase(matrix.begin() + vertex - 1);

    for (std::vector<std::vector<int>>::iterator it = matrix.begin(); it != matrix.end(); it++)
    {
        it->erase(it->begin() + vertex);
    }
    
    vertices--;
}

void AdjMatrixGraph::addEdge(int start, int end, int weight)
{
    if (!existsVertex(start) || !existsVertex(end))
    {
        throw std::runtime_error("Invalid vertex");
    }

    if (matrix[start][end] != 0)
    {
        throw std::runtime_error("Creating an existing edge");
    }

    matrix[start][end] = weight;

    if (!oriented)
    {
        matrix[end][start] = weight;
    }
}

void AdjMatrixGraph::removeEdge(int start, int end)
{
    if (!existsVertex(start) || !existsVertex(end))
    {
        throw std::runtime_error("Invalid vertex");
    }

    matrix[start][end] = 0;
    if (!oriented)
    {
        matrix[end][start] = 0;
    }
}

void AdjMatrixGraph::getSuccessors(int vertex, std::vector<std::pair<int, int>>& successors) const
{
    if (!existsVertex(vertex))
    {
        throw std::runtime_error("Invalid vertex");
    }

    for (int i = 0; i < matrix[vertex].size(); i++)
    {
        if (matrix[vertex][i] > 0)
        {
            successors.push_back(std::make_pair(i, matrix[vertex][i]));
        }
    }
}

void AdjMatrixGraph::getPredecessors(int vertex, std::vector<std::pair<int, int>>& predecessors) const
{
    if (!existsVertex(vertex))
    {
        throw std::runtime_error("Invalid vertex");
    }

    for (int i = 0; i < matrix[vertex].size(); i++)
    {
        if (matrix[i][vertex] > 0)
        {
            predecessors.push_back(std::make_pair(i, matrix[i][vertex]));
        }
    }
}

bool AdjMatrixGraph::adjacent(int start, int end) const
{
    if (!existsVertex(start) || !existsVertex(end))
    {
        throw std::runtime_error("Invalid vertex");
    }

    return matrix[start][end];
}

void AdjMatrixGraph::getEdges(std::vector<std::tuple<int, int, int>>& edges) const
{
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (matrix[i][j] != 0)
            {
                edges.push_back(std::make_tuple(i, j, matrix[i][j]));
            }
        }
    }
}
