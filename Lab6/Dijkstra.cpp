#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int Dijkstra(int** graph, int src, int dst) {
	// TODO: return the length of shortest path from src to dst.
    int n = 6;
    int* dist = new int[n];
    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[src] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int min = INT_MAX;
        int minIdx = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                minIdx = j;
            }
        }

        visited[minIdx] = true;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && graph[minIdx][j] && dist[minIdx] != INT_MAX && dist[minIdx] + graph[minIdx][j] < dist[j]) {
                dist[j] = dist[minIdx] + graph[minIdx][j];
            }
        }
    }

    return dist[dst];
	
}

int main() {
    int n = 6;
    int init[6][6] = {
        {0, 10, 20, 0, 0, 0},
        {10, 0, 0, 50, 10, 0},
        {20, 0, 0, 20, 33, 0},
        {0, 50, 20, 0, 20, 2},
        {0, 10, 33, 20, 0, 1},
        {0, 0, 0, 2, 1, 0} };

    int** graph = new int*[n];
    for (int i = 0; i < n; ++i) {
        graph[i] = init[i];
    }

    cout << Dijkstra(graph, 0, 1);
}