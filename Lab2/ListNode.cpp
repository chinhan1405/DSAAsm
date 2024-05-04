#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};

void printList(ListNode *head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->right;
    }
    cout << endl;
}

void shiftLeft(ListNode* &head, ListNode* node1, ListNode* node2) {
    if (head==node1) {
        head = head->right;
        head->left = nullptr;
    }
    else {
        node1->left->right = node1->right;
        node1->right->left = node1->left;
    }
    node1->right = node2->right;
    node1->left = node2;
    node2->right = node1;
}

ListNode* reverse(ListNode* head, int a, int b) {
    if (head==nullptr) return nullptr;
    ListNode* begin = head;
    int i = 0;
    for (; i<a-1; i++) {
        begin = begin->right;
    }
    ListNode* end = begin;
    for (; i<b-1; i++) {
        end = end->right;
    }
    ListNode* temp;
    for (i=a; i<b; i++) {
        temp = begin->right;
        shiftLeft(head, begin, end);
        begin = temp;
    }
    return head;
}

int main(int argc, char const *argv[])
{
    ListNode *list = new ListNode(1);
    ListNode *temp = list;
    for (int i = 2; i <= 5; i++) {
        temp->right = new ListNode(i, temp);
        temp = temp->right;
    }

    printList(reverse(list, 2, 4));
    delete[] list;
}
