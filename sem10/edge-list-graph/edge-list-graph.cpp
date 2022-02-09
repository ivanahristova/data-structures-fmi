#include "edge-list-graph.hpp"

EdgeListGraph::EdgeListGraph(int n, bool oriented)
    : Graph(n, oriented) {}

int EdgeListGraph::addVertex()
{
    vertices++;
    return vertices - 1;
}

void EdgeListGraph::removeVertex(int vertex)
{
	if (!existsVertex(vertex))
	{
        throw std::runtime_error("Invalid vertex");
    }

	//remove edges to/from vertex
	for (auto it = edges.begin(); it != edges.end();)
	{
		if (it->start == vertex || it->end == vertex)
		{
			edges.erase(it);
			continue;
		}

		if (it->start > vertex)
		{
            it->start--;
        }
		if (it->end > vertex)
		{
            it->end--;
        }
		it++;
	}

	vertices--;
}

void EdgeListGraph::addEdge(int start, int end, int weight)
{
    if (!existsVertex(start) || !existsVertex(end))
    {
        throw std::runtime_error("Invalid index");
    }

    edges.push_back({ start, end, weight });

	if (!oriented)
	{
        edges.push_back({ end, start, weight });
    }
}

void EdgeListGraph::removeEdge(int start, int end)
{
    if (!existsVertex(start) || !existsVertex(end))
	{
        throw std::runtime_error("Invalid index");
    }

	for (auto it = edges.begin(); it != edges.end();)
	{
		if ((it->start == start && it->end == end) || (!oriented && it->start == end && it->end == start))
    	{
            it = edges.erase(it);
        }	
		else
		{
            it++;
        }	
	}
}

void EdgeListGraph::getSuccessors(int vertex, std::vector<std::pair<int, int>>& successors) const
{
    if (!existsVertex(vertex))
	{
        throw std::runtime_error("Invalid index");
    }

	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if (it->start == vertex)
		{
            successors.push_back(std::make_pair(it->end, it->weight));
        }	
	}
}

void EdgeListGraph::getPredecessors(int vertex, std::vector<std::pair<int, int>>& predecessors) const
{
    if (!existsVertex(vertex))
	{
        throw std::runtime_error("Invalid index");
    }

	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if (it->end == vertex)
		{
            predecessors.push_back(std::make_pair(it->start, it->weight));
        }
	}
}

bool EdgeListGraph::adjacent(int start, int end) const
{
    if (!existsVertex(start) || !existsVertex(end))
	{
        throw std::runtime_error("Invalid vertex");
    }

	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if (it->start == start && it->end == end)
		{
			return true;
		}
	}

	return false;
}

void EdgeListGraph::getEdges(std::vector<std::tuple<int, int, int>>& edges) const
{
    for (auto it = this->edges.begin(); it != this->edges.end(); it++)
	{
        edges.push_back(std::make_tuple(it->start, it->end, it->weight));
    }
}
