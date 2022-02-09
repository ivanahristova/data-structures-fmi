#ifndef _GRAPH_ALGORITHMS_
#define _GRAPH_ALGORITHMS_

#include "../sem10/graph.hpp"
#include <stack>
#include <queue>
#include <climits>

enum Color { WHITE, GRAY, BLACK };

void connectedComponents(const Graph& g, int start, std::vector<bool>& visited);
int getConnectedComponentsCount(const Graph& g);

int minVertexBFS(const Graph& g, int start, std::vector<bool>& visited, const std::vector<int>& topValues);
int minValueOfConnectedComponents(const Graph& g, const std::vector<int>& topValues);

void Dijkstra(const Graph& g, int start, std::vector<int>& dist, std::vector<int>& prev);

bool containsCycleRecursiveCallVer1(const Graph& g, int start, std::vector<Color>& colors);
bool containsCycleRecursiveCallVer2(const Graph& g, int start, std::vector<bool>& visited, std::vector<bool>& st);
bool containsCycleVer1(const Graph& g);
bool containsCycleVer2(const Graph& g);

void topoSortDFS(const Graph& g, int start, std::vector<bool>& visited);
void topologicalSort(const Graph& g, std::vector<int>& order);

# endif