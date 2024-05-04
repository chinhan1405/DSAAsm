#include <iostream>
#include <queue>
#include <vector>
using namespace std;

long long nthNiceNumber(int n) {
    queue<long long> q;
    q.push(2);
    q.push(5);
    for (int i=1; i<n; i++) {
        long long x = q.front();
        q.pop();
        q.push(x*10+2);
        q.push(x*10+5);
    }
    return q.front();
}

int main() {
    cout << nthNiceNumber(10000);
}