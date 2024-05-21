#include <iostream>
#include <vector>
#include <list>
using namespace std;

class DirectedGraph 
{ 
	int V;
	vector<list<int>> adj;
public:
	DirectedGraph(int V)
	{
		this->V = V; 
		adj = vector<list<int>>(V, list<int>());
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}
    bool isCyclicTraverse(vector<bool>& visited, vector<bool>& tempVisited, int v)
    {
        visited[v] = true;
        tempVisited[v] = true;

        for(auto i = adj[v].begin(); i != adj[v].end(); i++)
        {
            if(!visited[*i] && isCyclicTraverse(visited, tempVisited, *i))
                return true;
            else if(tempVisited[*i])
                return true;
        }
        tempVisited[v] = false;
        return false;
    }
	bool isCyclic()
	{
	    vector<bool> visited = vector<bool>(V, false);
        vector<bool> tempVisited = vector<bool>(V, false);

        for(int i = 0; i < V; i++)
            if(!visited[i] && isCyclicTraverse(visited, tempVisited, i))
                return true;
        return false;
	    
	}
}; 

int main() {
    DirectedGraph g(8); 
    int edege[][2] = {{0,6}, {1,2}, {1,4}, {1,6}, {3,0}, {3,4}, {5,1}, {7,0}, {7,1}};

    for(int i = 0; i < 9; i++)
        g.addEdge(edege[i][0], edege[i][1]);

    if(g.isCyclic()) 
        cout << "Graph contains cycle"; 
    else
        cout << "Graph doesn't contain cycle"; 
}