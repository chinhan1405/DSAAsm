#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    // STUDENT ANSWER BEGIN 

    int getHeight(Node* node) {
        if (node == NULL)
            return 0;
        else {
            int leftHeight = getHeight(node->pLeft);
            int rightHeight = getHeight(node->pRight);
            return max(leftHeight, rightHeight) + 1;
        }
    }

    int getHeight() {
        return getHeight(root);
    }

    string preOrder(Node* node) {
        if (node == NULL)
            return "";
        else {
            string result = to_string(node->value) + " ";
            result += preOrder(node->pLeft);
            result += preOrder(node->pRight);
            return result;
        }
    }

    string preOrder() {
        return preOrder(root);
    }

    string inOrder(Node* node) {
        if (node == NULL)
            return "";
        else {
            string result = inOrder(node->pLeft);
            result += to_string(node->value) + " ";
            result += inOrder(node->pRight);
            return result;
        }
    }

    string inOrder() {
        return inOrder(root);
    }

    string postOrder(Node* node) {
        if (node == NULL)
            return "";
        else {
            string result = postOrder(node->pLeft);
            result += postOrder(node->pRight);
            result += to_string(node->value) + " ";
            return result;
        }
    }

    string postOrder() {
        return postOrder(root);
    }

    //Helping functions

    int sumOfLeafs(Node* node) {
        if (node == NULL)
            return 0;
        if (node->pLeft == NULL && node->pRight == NULL)
            return node->value;
        return sumOfLeafs(node->pLeft) + sumOfLeafs(node->pRight);
    }

    int sumOfLeafs(){
        return sumOfLeafs(root);
    }
        
    // STUDENT ANSWER END
};