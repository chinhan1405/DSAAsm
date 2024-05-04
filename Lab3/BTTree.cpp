#include <iostream>
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

pair<int, int> longestPathSumAndHeight(BTNode* node) {
    if (node == nullptr)
        return pair<int, int>(0, 0);
    else {
        pair<int, int> leftPath = longestPathSumAndHeight(node->left);
        pair<int, int> rightPath = longestPathSumAndHeight(node->right);
        if (leftPath.first > rightPath.first) {
            return pair<int, int>(leftPath.first+1, leftPath.second+node->val);
        }
        else if (leftPath.first < rightPath.first) {
            return pair<int, int>(rightPath.first+1, rightPath.second+node->val);
        }
        else if (leftPath.second > rightPath.second) {
            return pair<int, int>(leftPath.first+1, leftPath.second+node->val);
        }
        else {
            return pair<int, int>(rightPath.first+1, rightPath.second+node->val);
        }
    }
}

int longestPathSum(BTNode* root) {
    return longestPathSumAndHeight(root).second;
}


int main() {
    BTNode* root = new BTNode(1);
    root->left = new BTNode(5);
    root->right = new BTNode(4);
    root->right->left = new BTNode(7);
    root->right->left->left = new BTNode(4);
    root->right->left->left->left = new BTNode(2);
    root->right->left->right = new BTNode(8);
    root->right->right = new BTNode(12);
    cout << longestPathSum(root);
    return 0;
}