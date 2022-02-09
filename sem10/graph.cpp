#include "graph.hpp"

Graph::Graph(int vertices, bool oriented)
    : vertices(vertices), oriented(oriented) {}

bool Graph::isOriented() const
{
    return oriented;
}

int Graph::getVerticesCount() const
{
    return vertices;
}

bool Graph::existsVertex(int vertex) const
{
    return vertex >= 0 && vertex < vertices;
}
