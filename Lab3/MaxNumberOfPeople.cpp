#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int maxNumberOfPeople(vector<int>& rooms, vector<int>& people, int k) {
    sort(rooms.begin(), rooms.end());
    sort(people.begin(), people.end());
    int count = 0;
    int room_index = 0;
    int people_index = 0;
    while(room_index<rooms.size() && people_index<people.size()) {
        int size_desired = people[people_index];
        int min_size = size_desired - k;
        int max_size = size_desired + k;
        int room_size = rooms[room_index];
        if (room_size < min_size) {
            room_index++;
        }
        else if (room_size > max_size) {
            people_index++;
        }
        else {
            room_index++;
            people_index++;
            count++;
        }
    }
    return count;
}


int main() {
    vector<int> rooms = {4, 3, 2, 1, 5};
    vector<int> people = {2, 3, 7, 5, 6};
    int k = 1;
    cout << maxNumberOfPeople(rooms, people, k);
}