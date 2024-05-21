#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int numberOfFriendGroups(vector<vector<int>>& friends) {
    int num = friends.size();
    vector<bool> visited = vector<bool>(num, false);
    queue<int> q;
    int count = 0;
    for (int i=0; i<num; i++) {
        if (!visited[i]) {
            count++;
            q.push(i);
        }
        while (!q.empty()) {
            int visit = q.front();
            q.pop();
            visited[visit] = true;
            for (int adj : friends[visit]) {
                if (!visited[adj]) q.push(adj);
            }
        }
    }
    return count;
}

int main() {
    vector<vector<int>> graph {
        {1},
        {0, 2},
        {1},
        {4},
        {3},
        {}
    };
    cout << numberOfFriendGroups(graph);
}