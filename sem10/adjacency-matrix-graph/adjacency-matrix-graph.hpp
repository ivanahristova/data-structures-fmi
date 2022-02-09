#ifndef _ADJACENCY_MATRIX_GRAPH_
#define _ADJACENCY_MATRIX_GRAPH_

#include "../graph.hpp"

class AdjMatrixGraph : public Graph
{
private:
    std::vector<std::vector<int>> matrix;

public:
    AdjMatrixGraph(int vertices, bool oriented);

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
