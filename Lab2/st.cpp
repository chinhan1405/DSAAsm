#include<stack>
#include<iostream>
using namespace std;

class Node { public: int x, y; int dir; Node(int i, int j) { x = i; y = j; dir = 0; } };

bool checkMove(int maze[5][5], Node* node){
    if (node->dir==0) {
        if (node->x>0 && maze[node->x-1][node->y]) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (node->dir==1) {
        if (node->y<4 && maze[node->x][node->y+1]) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (node->dir==2) {
        if (node->x<4 && maze[node->x+1][node->y]) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (node->dir==3) {
        if (node->y>0 && maze[node->x][node->y-1]) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool canEatFood(int maze[5][5], int fx, int fy){
    stack<Node*> s;
    Node *current = new Node(0, 0);
    while(true) {
        if (current->x==fx && current->y==fy) {
            return true;
        }
        if (checkMove(maze, current)) {
            maze[current->x][current->y] = 0;
            s.push(current);
            if (current->dir==0)
                current = new Node(current->x-1, current->y);
            else if (current->dir==1)
                current = new Node(current->x, current->y+1);
            else if (current->dir==2)
                current = new Node(current->x+1, current->y);
            else if (current->dir==3)
                current = new Node(current->x, current->y-1);
        }
        else if (current->dir < 4){
            current->dir++;
        }
        else {
            if (s.empty()) {
                return false;
            }
            maze[current->x][current->y] = 1;
            current = s.top();
            current->dir++;
            s.pop();
        }
    }
}




int main() {

    // Maze matrix
    int maze[5][5] = {
        { 1, 0, 0, 1, 0 },
        { 1, 1, 1, 0, 1 },
        { 0, 1, 0, 1, 1 },
        { 1, 1, 0, 1, 0 },
        { 1, 0, 0, 1, 0 }
    };

    // Food coordinates
    int fx = 1, fy = 4;

    cout << canEatFood(maze, fx, fy);

    return 0;
}