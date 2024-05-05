#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>

using namespace std;

bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2) {
    sort(arr, arr + n);
    map<int, vector<pair<int, int>>> m;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            m[arr[i] + arr[j]].push_back(make_pair(i, j));
        }
    }
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->second.size() > 1) {
            for (int i = 1; i < it->second.size(); i++) {
                int pair1_1 = it->second[i - 1].first;
                int pair1_2 = it->second[i - 1].second;
                int pair2_1 = it->second[i].first;
                int pair2_2 = it->second[i].second;
                if (it->second[i].first != it->second[i - 1].second) {
                    pair1 = make_pair(arr[pair1_1], arr[pair1_2]);
                    pair2 = make_pair(arr[pair2_1], arr[pair2_2]);
                    return true;
                }
                else {
                    continue;
                }
            }
        }
    }  
    return false;
}

bool checkAnswer(int arr[], int n, pair<int, int> pair1, pair<int, int> pair2) {
    if (pair1.first + pair1.second == pair2.first + pair2.second) {
        set<int> s;
        s.insert(pair1.first);
        s.insert(pair1.second);
        s.insert(pair2.first);
        s.insert(pair2.second);
        if (s.size() == 4) {
            if (arr[pair1.first] + arr[pair1.second] == arr[pair2.first] + arr[pair2.second]) {
                return true;
            }
        }
    }
}

int main() {
    int arr[] = { 3, 4, 7, 1, 2, 9, 8 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)) {
        cout << "Pair 1: " << pair1.first << " " << pair1.second << endl;
        cout << "Pair 2: " << pair2.first << " " << pair2.second << endl;
        if (checkAnswer(arr, n, pair1, pair2)) {
            printf("Your answer is correct.\n");
        }
        else printf("Your answer is incorrect.\n");
    }
    else printf("No pair found.\n");
}