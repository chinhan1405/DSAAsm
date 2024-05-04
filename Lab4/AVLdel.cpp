#include <iostream>
#include <math.h>
#include <queue>
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
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
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

    Node* rotateLeft(Node* &root)
    {
        Node *tempPtr = root->pRight;
        root->pRight = tempPtr->pLeft;
        tempPtr->pLeft = root;
        return tempPtr;
    }

    Node* rotateRight(Node* &root)
    {
        Node *tempPtr = root->pLeft;
        root->pLeft = tempPtr->pRight;
        tempPtr->pRight = root;
        return tempPtr;
    }

    Node* deleteLeftBalance(Node* &root, bool &shorter)
    {
        if (root->balance == EH)
        {
            root->balance = LH;
            shorter = false;
        }
        else if (root->balance == RH)
            root->balance = EH;
        else
        {
            Node *leftTree = root->pLeft;
            if (leftTree->balance == RH)
            {
                Node *rightTree = leftTree->pRight;
                if (rightTree->balance == RH)
                {
                    leftTree->balance = LH;
                    root->balance = EH;
                }
                else if (rightTree->balance == EH)
                {
                    root->balance = RH;
                    leftTree->balance = EH;
                }
                else
                {
                    root->balance = RH;
                    leftTree->balance = EH;
                }
                rightTree->balance = EH;
                root->pLeft = rotateLeft(leftTree);
                root = rotateRight(root);
            }
            else
            {
                if (leftTree->balance != EH)
                {
                    root->balance = EH;
                    leftTree->balance = EH;
                }
                else
                {
                    root->balance = LH;
                    leftTree->balance = RH;
                    shorter = false;
                }
                root = rotateRight(root);
            }
        }
        return root;
    }

    Node* deleteRightBalance(Node* &root, bool &shorter) {
        if (root->balance == EH) {
            root->balance = RH;
            shorter = false;
        }
        else if (root->balance == LH)
            root->balance = EH;
        else {
            Node* rightTree = root->pRight;
            if (rightTree->balance == LH) {
                Node* leftTree = rightTree->pLeft;
                if (leftTree->balance == LH) {
                    rightTree->balance = RH;
                    root->balance = EH;
                }
                else if (leftTree->balance == EH) {
                    root->balance = LH;
                    rightTree->balance = EH;
                }
                else {
                    root->balance = LH;
                    rightTree->balance = EH;
                }
                leftTree->balance = EH;
                root->pRight = rotateRight(rightTree);
                root = rotateLeft(root);
            }
            else {
                if (rightTree->balance != EH) {
                    root->balance = EH;
                    rightTree->balance = EH;
                }
                else {
                    root->balance = RH;
                    rightTree->balance = LH;
                    shorter = false;
                }
                root = rotateLeft(root);
            }
        }
        return root;
    }

    Node* remove(Node* &root, const T &value, bool &shorter, bool &success)
    {
        if (root == NULL)
        {
            shorter = false;
            success = false;
            return;
        }
        if (value < root->data)
        {
            root->pLeft = remove(root->pLeft, value, shorter, success);
            if (shorter)
                root = deleteRightBalance(root, shorter);
        }
        else if (value > root->data)
        {
            root->pRight = remove(root->pRight, value, shorter, success);
            if (shorter)
                root = deleteLeftBalance(root, shorter);
        }
        else
        {
            Node *deleteNode = root;
            if (root->pLeft == NULL)
            {
                root = root->pRight;
                success = true;
                shorter = true;
                delete deleteNode;
                return root;
            }
            else if (root->pRight == NULL)
            {
                root = root->pLeft;
                success = true;
                shorter = true;
                delete deleteNode;
                return root;
            }
            else
            {
                Node *exchPtr = root->pLeft;
                while (exchPtr->pRight != NULL)
                    exchPtr = exchPtr->pRight;
                root->data = exchPtr->data;
                root->pLeft = remove(root->pLeft, exchPtr->data, shorter, success);
                if (shorter)
                    root = deleteRightBalance(root, shorter);
            }
        }
        return root;
    }

    void remove(const T &value)
    {
        bool shorter = false;
        bool success = false;
        this->root = this->remove(this->root, value, shorter, success);
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