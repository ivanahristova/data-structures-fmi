#include <iostream>
#include "../sem10/graph.hpp"
#include "../sem10/adjacency-list-graph/adjacency-list-graph.hpp"
#include "../sem10/edge-list-graph/edge-list-graph.hpp"
#include "../sem10/adjacency-matrix-graph/adjacency-matrix-graph.hpp"
#include "algorithms.hpp"

void printTupleEdge(const std::tuple<int, int, int>& edge)
{
    std::cout << "(" << std::get<0>(edge) 
            << ", " << std::get<1>(edge) 
            << ", " << std::get<2>(edge)
            << ")";
}

void printEdges(const std::vector<std::tuple<int, int, int>>& edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        printTupleEdge(edges[i]);
        std::cout << '\n';
    }
}

int main()
{
    EdgeListGraph g(9, 1);
    
    g.addEdge(0, 1, 2); 
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 5, 10);
    g.addEdge(4, 3, 4);
    g.addEdge(5, 6, 9);
    g.addEdge(5, 7, 11);
    g.addEdge(6, 7, 14);
    g.addEdge(7, 8, 5);

    std::vector<std::tuple<int, int, int>> edges;
    g.getEdges(edges);
    printEdges(edges);
    
    std::cout << "Connected components: " << getConnectedComponentsCount(g) << std::endl;
    std::cout << "Contains cycle: " << containsCycleVer1(g) << std::endl;

    std::vector<int> dist(g.getVerticesCount());
    std::vector<int> prev(g.getVerticesCount());

    Dijkstra(g, 0, dist, prev);
    for (int i = 0; i < g.getVerticesCount(); i++)
    {
        std::cout << "Distance 0-" << i << ": " << dist[i] << std::endl;
    }
    
    EdgeListGraph g1(9, 1);
    
    g1.addEdge(1, 2, 1);
    g1.addEdge(1, 3, 4);
    g1.addEdge(2, 3, 2);
    g1.addEdge(3, 5, 10);
    g1.addEdge(5, 6, 9);
    g1.addEdge(5, 7, 11);
    g1.addEdge(6, 7, 14);

    std::cout << "Connected components: " << getConnectedComponentsCount(g1) << std::endl;

    std::vector<int> order;
    topologicalSort(g, order);

    std::cout << "Topological sort: ";
    for (int i = 0; i < order.size(); i++)
    {
        std::cout << order[i] << ' ';
    }
}
