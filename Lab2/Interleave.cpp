#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void interleaveQueue(queue<int>& q){
    int size = q.size();
    queue<int> q2;
    for (int i=0; i<size/2; i++) {
        q2.push(q.front());
        q.pop();
    }
    for (int i=0; i<size/2; i++) {
        q.push(q2.front());
        q2.pop();
        q.push(q.front());
        q.pop();
    }
}

int main() {
    queue<int> q;
    int n; cin >> n;
    for (int i = 0; i < n; i++){
        int element; cin >> element;
        q.push(element);
    }
    interleaveQueue(q);
    while (!q.empty()){
        cout << q.front() << ' ';
        q.pop();
    }
}