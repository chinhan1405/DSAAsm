#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int secondsToBeRotten(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            }
            else if (grid[i][j] == 1) {
                fresh++;
            }
        }
    }
    if (fresh == 0) return 0;
    int seconds = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i=0; i<size; i++) {
            pair<int, int> p = q.front();
            q.pop();
            for (int j=0; j<4; j++) {
                int x = p.first, y = p.second;
                if (j==0) {
                    x += 1;
                }
                else if (j==1) {
                    x -= 1;
                }
                else if (j==2) {
                    y += 1;
                }
                else {
                    y -= 1;
                }
                if (x>=0 && x<m && y>=0 && y<n && grid[x][y] == 1) {
                    grid[x][y] = 2;
                    q.push({x, y});
                    fresh--;
                }
            }
        }
        seconds++;
    }
    return fresh == 0 ? seconds-1 : -1;
}

int main() {
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    cout << secondsToBeRotten(grid);
}