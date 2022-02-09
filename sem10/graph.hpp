#ifndef _GRAPH_
#define _GRAPH_

#include <vector>
#include <stdexcept>
#include <tuple>

class Graph
{
protected:
    int vertices;
    bool oriented;
    
public:

    Graph(int vertices, bool oriented);

    virtual int addVertex() = 0;
    virtual void removeVertex(int vertex) = 0;

    virtual void addEdge(int start, int end, int weight = 1) = 0;
    virtual void removeEdge(int start, int end) = 0;

    virtual void getSuccessors(int vertex, std::vector<std::pair<int, int>>& successors) const = 0;
    virtual void getPredecessors(int vertex, std::vector<std::pair<int, int>>& predecessors) const = 0;

    virtual bool adjacent(int start, int end) const = 0;
    virtual void getEdges(std::vector<std::tuple<int, int, int>>& edges) const = 0;

    bool isOriented() const;
    int getVerticesCount() const;
    bool existsVertex(int vertex) const;

};

#endif
