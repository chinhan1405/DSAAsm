#include <iostream>
#include <list>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) 
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph {

    int V;
    Adjacency* adj;

public:
    Graph(int V){
        this->V = V;
        adj = new Adjacency[V];
    }
    void addEdge(int v, int w){
        adj[v].push(w);
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            adj[i].print();
            cout << endl;
        }
    }
    
    //Heling functions
    void topologicalSortUtil(int v, int* visited, int& count) {
        visited[v] = -1;
        for(int i = 0; i < adj[v].getSize(); i++){
            int n = adj[v].getElement(i);
            if (visited[n]==0) {
                count++;
                topologicalSortUtil(n, visited, count);
            }
        }
        visited[v] = count++;
    }
    
    void topologicalSort(){
        int* visited = new int[V];
        for(int i = 0; i < V; i++)
            visited[i] = 0;
        int count = 1;
        for(int i = 0; i < V; i++) {
            if(visited[i] == 0)
                topologicalSortUtil(i, visited, count);
        }
        for (int i = 0; i < V; i++) {
            int max = 0;
            for (int j = 0; j < V; j++) {
                if (visited[j] > visited[max]) {
                    max = j;
                }
            }
            cout << max << " ";
            visited[max] = -1;
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topologicalSort();
}