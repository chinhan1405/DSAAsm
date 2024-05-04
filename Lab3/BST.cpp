#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    void add(Node* &node, T value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value < node->value) {
            if (!node->pLeft) {
                node->pLeft = new Node(value);
            }
            else {
                add(node->pLeft, value);
            }
        }
        else if (value > node->value) {
            if (!node->pRight) {
                node->pRight = new Node(value);
            }
            else {
                add(node->pRight, value);
            }
        }
    }

    void deleteNode(Node* &node, T value) {
        if (!node) {
            return;
        }
        if (value < node->value) {
            deleteNode(node->pLeft, value);
        }
        else if (value > node->value) {
            deleteNode(node->pRight, value);
        }
        else {
            if (!node->pLeft) {
                Node* temp = node->pRight;
                delete node;
                node = temp;
            }
            else if (!node->pRight) {
                Node* temp = node->pLeft;
                delete node;
                node = temp;
            }
            else {
                Node* temp = node->pRight;
                while (temp->pLeft) {
                    temp = temp->pLeft;
                }
                node->value = temp->value;
                deleteNode(node->pRight, temp->value);
            }
        }
    }

    void add(T value){
        add(root, value);
    }

    void deleteNode(T value){
        deleteNode(root, value);
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder(){
        return inOrderRec(this->root);
    }
    
    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

int main() {
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.deleteNode(9);
    cout << bst.inOrder();
    return 0;
}