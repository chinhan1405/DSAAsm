#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int _val = 0, ListNode* _next = nullptr) : val(_val), next(_next) { }
};

ListNode* mergeLists(ListNode* a, ListNode* b) {
    ListNode* iter1;
    ListNode* iter2;
    ListNode* head;
    if (a->val <= b->val) {
        iter1 = a;
        iter2 = b;
        head = a;
    }
    else {
        iter1 = b;
        iter2 = a;
        head = b;
    }
    while (iter1->next!=nullptr) {
        if (iter2!=nullptr && iter1->val <= iter2->val 
        && iter1->next->val > iter2->val) {
            ListNode* temp = iter2;
            iter2 = iter2->next;
            temp->next = iter1->next;
            iter1->next = temp;
        }
        iter1 = iter1->next;
    }
    iter1->next = iter2;
    return head;
}

// Sort and unsorted list given its head pointer
ListNode* mergeSortList(ListNode* head) {
    if (head->next==nullptr) return head;
    ListNode* first_head = head;
    ListNode* first_iter = first_head;
    ListNode* second_head = head->next;
    ListNode* second_iter = second_head;
    head = second_head->next;
    bool first_turn = true;
    while (head!=nullptr) {
        if (first_turn) {
            first_iter->next = head;
            first_iter = head;
            head = head->next;
        }
        else {
            second_iter->next = head;
            second_iter = head;
            head = head->next;
        }
        first_turn = !first_turn;
    }
    first_iter->next = nullptr;
    second_iter->next = nullptr;
    ListNode* sorted_first = mergeSortList(first_head);
    ListNode* sorted_second = mergeSortList(second_head);
    return mergeLists(sorted_first, sorted_second);
}

int main() {
    int list[] = {9,8,7,6,6,5,4,3,2,1};
    ListNode* head = new ListNode(list[0]);
    ListNode* iter = head;
    for (int i=1; i<sizeof(list)/4; i++){
        iter->next = new ListNode(list[i]);
        iter = iter->next;
    }
    ListNode* sorted = mergeSortList(head);
    while (sorted!=nullptr) {
        cout << sorted->val << " ";
        sorted = sorted->next;
    }
    cout << endl;
}