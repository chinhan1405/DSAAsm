#include <iostream>
#include <string>
using namespace std;

class SplayTree {
    struct Node {
        int val;
        Node* pLeft;
        Node* pRight;
        Node* pParent;
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr, Node* par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) { }
    };
    Node* root;

    // print the tree structure for local testing
    void printBinaryTree(string prefix, const Node* root, bool isLeft, bool hasRightSibling) {
        if (!root && isLeft && hasRightSibling) {
            cout << prefix << "├──\n";
        }
        if (!root) return;
        cout << prefix;
        if (isLeft && hasRightSibling) 
            cout << "├──";
        else 
            cout << "└──";
        cout << root->val << '\n';
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pLeft, true, root->pRight);
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pRight, false, root->pRight);
    }

    void printPreorder(Node* p) {
        if (!p) {
            return;
        }
        cout << p->val << ' ';
        printPreorder(p->pLeft);
        printPreorder(p->pRight);
    }
public:
    SplayTree() {
        root = nullptr;
    }
    ~SplayTree() {
        // Ignore deleting all nodes in the tree
    }

    void printBinaryTree() {
        printBinaryTree("", root, false, false);
    }

    void printPreorder() {
        printPreorder(root);
        cout << "\n";
    }

    void rotateRight(Node* p) {
        Node* q = p->pLeft;
        if (!q) return;
        p->pLeft = q->pRight;
        if (q->pRight) {
            q->pRight->pParent = p;
        }
        q->pParent = p->pParent;
        if (!p->pParent) {
            root = q;
        } else if (p == p->pParent->pLeft) {
            p->pParent->pLeft = q;
        } else {
            p->pParent->pRight = q;
        }
        q->pRight = p;
        p->pParent = q;
    }

    void rotateLeft(Node* p) {
        Node* q = p->pRight;
        if (!q) return;
        p->pRight = q->pLeft;
        if (q->pLeft) {
            q->pLeft->pParent = p;
        }
        q->pParent = p->pParent;
        if (!p->pParent) {
            root = q;
        } else if (p == p->pParent->pLeft) {
            p->pParent->pLeft = q;
        } else {
            p->pParent->pRight = q;
        }
        q->pLeft = p;
        p->pParent = q;
    }

    void splay(Node* p) {
        while (p->pParent) {
            Node* parent = p->pParent;
            Node* grandParent = parent->pParent;
            if (!grandParent) {
                if (p == parent->pLeft) {
                    rotateRight(parent);
                } else {
                    rotateLeft(parent);
                }
            } else {
                if (p == parent->pLeft && parent == grandParent->pLeft) {
                    rotateRight(grandParent);
                    rotateRight(parent);
                } else if (p == parent->pRight && parent == grandParent->pRight) {
                    rotateLeft(grandParent);
                    rotateLeft(parent);
                } else if (p == parent->pLeft && parent == grandParent->pRight) {
                    rotateRight(parent);
                    rotateLeft(grandParent);
                } else {
                    rotateLeft(parent);
                    rotateRight(grandParent);
                }
            }
        }
    }

    Node* insert(Node* &root, int val) {
        if (!root) {
            root = new Node(val);
            return root;
        }
        else {
            if (val < root->val) {
                root->pLeft = insert(root->pLeft, val);
            } else {
                root->pRight = insert(root->pRight, val);
            }
            return root;
        }
    }

    void insert(int val) {
        Node* newNode = new Node(val);
        if (!root) {
            root = newNode;
            return;
        }
        Node* p = root;
        while (true) {
            if (val < p->val) {
                if (p->pLeft) {
                    p = p->pLeft;
                } else {
                    p->pLeft = newNode;
                    newNode->pParent = p;
                    break;
                }
            } else {
                if (p->pRight) {
                    p = p->pRight;
                } else {
                    p->pRight = newNode;
                    newNode->pParent = p;
                    break;
                }
            }
        }
        splay(newNode);
    }

    bool search(Node* p, int val) {
        if (!p) return false;
        if (p->val == val) {
            splay(p);
            return true;
        }
        if (val < p->val) {
            if (!p->pLeft) {
                splay(p);
                return false;
            }
            return search(p->pLeft, val);
        } else {
            if (!p->pRight) {
                splay(p);
                return false;
            }
            return search(p->pRight, val);
        }
    }

    bool search(int val) {
        return search(root, val);
    }

    Node* remove(int val) {
        if (!root) return NULL;
        if (search(val)) {
            Node* target = root;
            Node* tree1 = root->pLeft;
            Node* tree2 = root->pRight;
            if (!tree1) {
                root = tree2;
                if (tree2) tree2->pParent = NULL;
            } else {
                while (tree1->pRight) {
                    tree1 = tree1->pRight;
                }
                splay(tree1);
                tree1->pRight = tree2;
                if (tree2) tree2->pParent = tree1;
                root = tree1;
            }
        }
        else {
            return NULL;
        }
    }
};

int main(int argc, char const *argv[])
{
    SplayTree tree;
    int query;
    cin >> query;
    for(int i = 0; i < query; i++) {
        string op;
        int val;
        cin >> op >> val;
        if (op == "insert")
            tree.insert(val);
    }
    // print preorder traversal of the tree
    tree.printPreorder();
    // print structure of the tree
    tree.printBinaryTree();
    return 0;
}
