#include <iostream>
#include <stack>
#include <utility>
using namespace std;

class BTNode {
    public: 
        int val; 
        BTNode *left; 
        BTNode *right; 
        BTNode() {
            this->left = this->right = NULL;
        } 
        BTNode(int val) {
            this->val = val;
            this->left = this->right = NULL;
        } 
        BTNode(int val, BTNode*& left, BTNode*& right) {
            this->val = val;
            this->left = left;
            this->right = right;
        } 
};

int sumDigitPath(BTNode* root) {
    long long sum = 0;
    stack<pair<BTNode*, long long>> st;
    st.push({root,root->val});
    while(!st.empty()) {
        BTNode* curNode = st.top().first;
        long long curSum = st.top().second;
        st.pop();
        if ((!curNode->left) && (!curNode->right)) {
            cout << curSum << endl;
            sum += curSum;
        }
        else {
            if (curNode->right) {
                st.push({curNode->right, curSum*10+curNode->right->val});
            }
            if (curNode->left) {
                st.push({curNode->left, curSum*10+curNode->left->val});
            }
        }
    }
    return sum % 27022001;
}


int main() {
    BTNode* root = new BTNode(1);
    root->left = new BTNode(2);
    cout << sumDigitPath(root);
}