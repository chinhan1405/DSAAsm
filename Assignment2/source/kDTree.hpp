#include "main.hpp"
#include "Dataset.hpp"

struct kDTreeNode
{
    vector<int> data;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    kDTreeNode(const kDTreeNode &other)
    {
        data = other.data;
        if (other.left != nullptr)
            left = new kDTreeNode(*other.left);
        else
            left = nullptr;
        if (other.right != nullptr)
            right = new kDTreeNode(*other.right);
        else
            right = nullptr;
    }
    ~kDTreeNode()
    {
        delete left;
        delete right;
    }
    string format() const;
};

class kDTree
{
private:
    int k;
    kDTreeNode *root;

    void inorderTraversal(kDTreeNode *root) const;
    void preorderTraversal(kDTreeNode *root) const;
    void postorderTraversal(kDTreeNode *root) const;
    int height(kDTreeNode *root) const;
    int nodeCount(kDTreeNode *root) const;
    int leafCount(kDTreeNode *root) const;
    void insert(kDTreeNode *&root, const vector<int> &point, int depth);
    kDTreeNode *findMin(kDTreeNode *root, int depth, int dim);
    void remove(kDTreeNode *&root, const vector<int> &point, int depth);
    bool search(kDTreeNode *root, const vector<int> &point, int depth);
    int mergeSort(vector<vector<int>> &pointList, int left, int right, int depth, bool isLeft);
    void buildTree(kDTreeNode *&root, vector<vector<int>> &pointList, int left, int right, int depth, bool isLeft);
    double distance_squared(const vector<int> &a, const vector<int> &b);
    void nearestNeighbour(kDTreeNode *root, const vector<int> &target, kDTreeNode *best, int depth);
    void kNearestNeighbour(kDTreeNode *root, const vector<int> &target, int k, vector<kDTreeNode *> &bestList, int depth);

public:
    kDTree(int k = 2);
    ~kDTree();

    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other);

    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    int height() const;
    int nodeCount() const;
    int leafCount() const;

    void insert(const vector<int> &point);
    void remove(const vector<int> &point);
    bool search(const vector<int> &point);
    void buildTree(const vector<vector<int>> &pointList);
    void nearestNeighbour(const vector<int> &target, kDTreeNode *best);
    void addNearNeighbour(kDTreeNode *best, const vector<int> &target, vector<kDTreeNode *> &bestList, int k);
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList);
};

class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    kDTree *kdtree;
    int numClasses;

    int getNumClasses(const Dataset &y_train);
    int getMajorityClass(const vector<int> &bestLabelList);
    int getLabel(const vector<int> &point);

public:
    kNN(int k = 5);
    void fit(const Dataset &X_train, const Dataset &y_train);
    Dataset predict(const Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};