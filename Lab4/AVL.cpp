#include <iostream>
#include <math.h>
#include <queue>
#include <string>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << "  ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data << temp->balance;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    //Helping functions
    Node* rotateRight(Node* &root) {
        Node* temp = root->pLeft;
        root->pLeft = temp->pRight;
        temp->pRight = root;
        return temp;
    }

    Node* rotateLeft(Node* &root) {
        Node* temp = root->pRight;
        root->pRight = temp->pLeft;
        temp->pLeft = root;
        return temp;
    }

    Node* leftBalance(Node* &root, bool &taller) {
        Node* leftTree = root->pLeft;
        if (leftTree->balance == LH) {
            root->balance = EH;
            root = rotateRight(root);
            leftTree->balance = EH;
        }
        else {
            Node* rightTree = leftTree->pRight;
            if (rightTree->balance == LH) {
                root->balance = RH;
                leftTree->balance = EH;
            }
            else if (rightTree->balance == EH) {
                root->balance = EH;
                leftTree->balance = EH;
            }
            else {
                root->balance = EH;
                leftTree->balance = LH;
            }
            rightTree->balance = EH;
            root->pLeft = rotateLeft(leftTree);
            root = rotateRight(root);
        }
        return root;
    }

    Node* rightBalance(Node* &root, bool &taller) {
        Node* rightTree = root->pRight;
        if (rightTree->balance == RH) {
            root->balance = EH;
            root = rotateLeft(root);
            rightTree->balance = EH;
        }
        else {
            Node* leftTree = rightTree->pLeft;
            if (leftTree->balance == RH) {
                root->balance = LH;
                rightTree->balance = EH;
            }
            else if (leftTree->balance == EH) {
                root->balance = EH;
                rightTree->balance = EH;
            }
            else {
                root->balance = EH;
                rightTree->balance = RH;
            }
            leftTree->balance = EH;
            root->pRight = rotateRight(rightTree);
            root = rotateLeft(root);
        }
        return root;
    }

    Node* insert(Node* &root, const T &value, bool &taller) {
        if (!root) {
            taller = true;
            root = new Node(value);
            return root;
        }
        if (value < root->data) {
            root->pLeft = insert(root->pLeft, value, taller);
            if (taller) {
                if (root->balance==LH) {
                    root = leftBalance(root, taller);
                    taller = false;
                }
                else if (root->balance==EH) {
                    root->balance = LH;
                }
                else {
                    root->balance = EH;
                    taller = false;
                }
            }
        }
        else {
            root->pRight = insert(root->pRight, value, taller);
            if (taller) {
                if (root->balance==RH) {
                    root = rightBalance(root, taller);
                    taller = false;
                }
                else if (root->balance==EH) {
                    root->balance = RH;
                }
                else {
                    root->balance = EH;
                    taller = false;
                }
            }
        }
        return root;
    }

    void insert(const T &value){
        bool taller = false;
        root = insert(root, value, taller);
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main()
{
    AVLTree<int> tree;
    string input = "";
    while (true) {
        cin >> input;
        if (input == "") continue;
        if (input == "end") {
            break;
        }
        tree.insert(stoi(input));
        tree.printTreeStructure();
    }
    
    return 0;
}

// 6 3 9 12 10 8 6 8 9 10 9 9 12 10 15 11 12 8 9