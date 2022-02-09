#include <iostream>
#include <vector>
#include <queue>

class Graph 
{
    int vertices;
    std::vector<std::vector<int>> adjList;
    
public:
    Graph(int vertices) 
        : vertices(vertices), adjList(vertices, std::vector<int>()) {}

    Graph(int vertices, std::vector<std::pair<int, int>> edges) : Graph(vertices)
    {
        int edgesCount = edges.size();
        for (int i = 0; i < edgesCount; i++)
        {
            adjList[edges[i].first].push_back(edges[i].second);
            adjList[edges[i].second].push_back(edges[i].first);
        }
    }

    double getAverageOfConnectedComponents();
    void BFS(int start, std::vector<bool>& visited, int& sum, int& vertexCount);
};

void Graph::BFS(int start, std::vector<bool>& visited, int& sum, int& vertexCount)
{
	std::queue<int> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int currentVertex = q.front();
		q.pop();

		sum += currentVertex;
		vertexCount++;

		for (int i = 0; i < adjList[currentVertex].size(); i++)
		{
			if (!visited[adjList[currentVertex][i]])
			{
                visited[adjList[currentVertex][i]] = true;
			    q.push(adjList[currentVertex][i]);
            }
		}
	}

}

double Graph::getAverageOfConnectedComponents()
{
	std::vector<bool> visited(adjList.size(), false);

	double result = 0;
	for (int i = 0; i < adjList.size(); i++)
	{
		if (!visited[i])
		{
			int vertexCount = 0, sum = 0;
			BFS(i, visited, sum, vertexCount);
			result +=  ((double)sum / vertexCount);
		}
	}
	return result;
}

int main()
{
    // (7) --- (8)    => 7.5
    // 
    // (4) ----- (5)     => 5
    //  \         /      
    //   \       /
    //    \ (6) /
    // 
    //   _______________________
    //  |                       |      => 1.5
    // (0) --- (1) --- (2) --- (3)

    int n = 9;
    int m = 8;
    std::vector<std::pair<int, int>> edges = 
    {{7, 8}, 
    {4, 5}, {4, 6}, {5, 6}, 
    {2, 1}, {0, 3}, {0, 1}, {2, 3}};

    Graph g(n, edges);
    std::cout << g.getAverageOfConnectedComponents();
}