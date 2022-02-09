#ifndef _ADJACENCY_LIST_GRAPH_
#define _ADJACENCY_LIST_GRAPH_

#include "../graph.hpp"
#include <list>

class AdjListGraph : public Graph
{
private:

    struct Edge
    {
        int end;
        int weight;

        Edge(int end, int weight = 1)
            : end(end), weight(weight) {}
    };

    std::vector<std::list<Edge>> adjList;

public:
    AdjListGraph(int vertices, bool oriented);

    int addVertex() override;
    void removeVertex(int vertex) override;

    void addEdge(int start, int end, int weight = 1) override;
    void removeEdge(int start, int end) override;

    void getSuccessors(int vertex, std::vector<std::pair<int, int>>& successors) const override;
    void getPredecessors(int vertex, std::vector<std::pair<int, int>>& predecessors) const override;

    bool adjacent(int start, int end) const override;
    void getEdges(std::vector<std::tuple<int, int, int>>& edges) const override;

};

#endif
