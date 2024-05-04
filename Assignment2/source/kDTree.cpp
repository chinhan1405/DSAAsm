#include "kDTree.hpp"

// kDTree
string kDTreeNode::format() const {
    if (data.empty()) return "";
    stringstream ss;
    ss << "(" << data[0];
    for (int i = 1; i < data.size(); i++) {
        ss << "," << data[i];
    }
    ss << ")";
    return ss.str();
}

kDTree::kDTree(int k) {
    this->k = k;
    this->root = nullptr;
}

kDTree::~kDTree() {
    delete root;
}

const kDTree &kDTree::operator=(const kDTree &other) {
    if (this == &other) return *this;
    this->k = other.k;
    if (other.root == nullptr) {
        this->root = nullptr;
    } else {
        this->root = new kDTreeNode(*other.root);
    }
    return *this;
}

kDTree::kDTree(const kDTree &other) {
    this->k = other.k;
    if (other.root == nullptr) {
        this->root = nullptr;
    } else {
        this->root = new kDTreeNode(*other.root);
    }
}

void kDTree::inorderTraversal(kDTreeNode *root) const {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->format() << " ";
    inorderTraversal(root->right);
}

void kDTree::inorderTraversal() const {
    inorderTraversal(root);
    cout << "\b";
}

void kDTree::preorderTraversal(kDTreeNode *root) const {
    if (root == nullptr) {
        return;
    }
    cout << root->format() << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void kDTree::preorderTraversal() const {
    preorderTraversal(root);
    cout << "\b";
}

void kDTree::postorderTraversal(kDTreeNode *root) const {
    if (root == nullptr) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->format() << " ";
}

void kDTree::postorderTraversal() const {
    postorderTraversal(root);
    cout << "\b";
}

int kDTree::height(kDTreeNode *root) const {
    if (root == nullptr) {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

int kDTree::height() const {
    return height(root);
}

int kDTree::nodeCount(kDTreeNode *root) const {
    if (root == nullptr) {
        return 0;
    }
    return 1 + nodeCount(root->left) + nodeCount(root->right);
}

int kDTree::nodeCount() const {
    return nodeCount(root);
}

int kDTree::leafCount(kDTreeNode *root) const {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    return leafCount(root->left) + leafCount(root->right);
}

int kDTree::leafCount() const {
    return leafCount(root);
}

void kDTree::insert(kDTreeNode *&root, const vector<int> &point, int depth) {
    if (point.size() != k) return;
    if (root == nullptr) {
        root = new kDTreeNode(point);
        return;
    }
    if (point[depth%k] < root->data[depth%k]) {
        insert(root->left, point, depth + 1);
    } else {
        insert(root->right, point, depth + 1);
    }
}

void kDTree::insert(const vector<int> &point) {
    insert(root, point, 0);
}

kDTreeNode* kDTree::findMin(kDTreeNode *root, int depth, int dim) {
    if (root == nullptr) {
        return nullptr;
    }
    if (depth == dim) {
        if (root->left == nullptr) {
            return root;
        }
        return findMin(root->left, depth + 1, dim);
    }
    kDTreeNode *left = findMin(root->left, depth + 1, dim);
    kDTreeNode *right = findMin(root->right, depth + 1, dim);
    kDTreeNode *min = root;
    if (left != nullptr && left->data[dim] < min->data[dim]) {
        min = left;
    }
    if (right != nullptr && right->data[dim] < min->data[dim]) {
        min = right;
    }
    return min;
}

void kDTree::remove(kDTreeNode *&root, const vector<int> &point, int depth) {
    if (root == nullptr) {
        return;
    }
    if (root->data == point) {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->right) {
            kDTreeNode *target = findMin(root->right, depth + 1, depth % k);
            root->data = target->data;
            remove(root->right, target->data, depth + 1);
        } else {
            kDTreeNode *target = findMin(root->left, depth + 1, depth % k);
            root->data = target->data;
            remove(root->left, target->data, depth + 1);
        }
    } else {
        if (point[depth] < root->data[depth]) {
            remove(root->left, point, depth + 1);
        } else {
            remove(root->right, point, depth + 1);
        }
    }
}

void kDTree::remove(const vector<int> &point) {
    remove(root, point, 0);
}

bool kDTree::search(kDTreeNode *root, const vector<int> &point, int depth) {
    if (root == nullptr) {
        return false;
    }
    if (root->data == point) {
        return true;
    }
    if (point[depth%k] < root->data[depth%k]) {
        return search(root->left, point, depth + 1);
    } else {
        return search(root->right, point, depth + 1);
    }
}

bool kDTree::search(const vector<int> &point) {
    return search(root, point, 0);
}

int kDTree::mergeSort(vector<vector<int>> &pointList, int left, int right, int depth, bool isLeft) {
    depth %= k;
    if (left >= right) return 0;
    int mid = 0;
    if (isLeft) {
        mid = left + (right - left) / 2;
        mergeSort(pointList, left, mid, depth, isLeft);
        mergeSort(pointList, mid + 1, right, depth, isLeft);
    } else {
        mid = left + ceil((right - left) / 2.0);
        mergeSort(pointList, left, mid - 1, depth, isLeft);
        mergeSort(pointList, mid, right, depth, isLeft);
    }
    vector<vector<int>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (pointList[i][depth] < pointList[j][depth]) {
            temp[k++] = pointList[i++];
        } else {
            temp[k++] = pointList[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = pointList[i++];
    }
    while (j <= right) {
        temp[k++] = pointList[j++];
    }
    for (int i = left; i <= right; i++) {
        pointList[i] = temp[i - left];
    }
    return mid;
}

void kDTree::buildTree(kDTreeNode *&root, vector<vector<int>> &pointList, int left, int right, int depth, bool isLeft) {
    if (left > right) return;
    else if (left == right) {
        root = new kDTreeNode(pointList[left]);
        return;
    }
    int mid = mergeSort(pointList, left, right, depth, isLeft);
    root = new kDTreeNode(pointList[mid]);
    buildTree(root->left, pointList, left, mid - 1, depth + 1, true);
    buildTree(root->right, pointList, mid + 1, right, depth + 1, false);
}

void kDTree::buildTree(const vector<vector<int>> &pointList) {
    vector<vector<int>> tempList = pointList;
    buildTree(root, tempList, 0, tempList.size() - 1, 0, true);
}

double kDTree::distance_squared(const vector<int> &a, const vector<int> &b) {
    double sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += pow(a[i] - b[i], 2);
    }
    return sum;
}

void kDTree::nearestNeighbour(kDTreeNode *root, const vector<int> &target, kDTreeNode *best, int depth) {
    if (root == nullptr) return;
    if (root->data == target) {
        best->data = target;
        return;
    }
    if (target[depth%k] < root->data[depth%k] && root->left) {
        nearestNeighbour(root->left, target, best, depth + 1);
        if (distance_squared(root->data, target) < distance_squared(best->data, target)) {
            best->data = root->data;
        }
        if (root->right && distance_squared(best->data, target) > pow(target[depth%k] - root->data[depth%k], 2))
            nearestNeighbour(root->right, target, best, depth + 1);
    } else if (target[depth%k] >= root->data[depth%k] && root->right) {
        nearestNeighbour(root->right, target, best, depth + 1);
        if (distance_squared(root->data, target) < distance_squared(best->data, target)) {
            best->data = root->data;
        }
        if (root->left && distance_squared(best->data, target) > pow(target[depth%k] - root->data[depth%k], 2))
            nearestNeighbour(root->left, target, best, depth + 1);
    }
    else {
        if (best->data == vector<int>(k, 0) || distance_squared(root->data, target) < distance_squared(best->data, target))
            best->data = root->data;
        return;
    }
}

void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *best) {
    nearestNeighbour(root, target, best, 0);
}

void kDTree::addNearNeighbour(kDTreeNode *best, const vector<int> &target, vector<kDTreeNode *> &bestList, int k) {
    if (bestList.empty()) {
        bestList.push_back(best);
        return;
    }
    if (distance_squared(best->data, target) < distance_squared(bestList.back()->data, target)) {
        for (int i=0; i<bestList.size(); i++) {
            if (distance_squared(best->data, target) < distance_squared(bestList[i]->data, target)) {
                bestList.insert(bestList.begin() + i, best);
                if (bestList.size() > k)
                    bestList.pop_back();
                break;
            }
        }
    }
    if (bestList.size() < k) {
        bestList.push_back(best);
    }
}

void kDTree::kNearestNeighbour(kDTreeNode *root, const vector<int> &target, int k, vector<kDTreeNode *> &bestList, int depth) {
    if (root == nullptr) return;
    if (target[depth%this->k] < root->data[depth%this->k] && root->left) {
        kNearestNeighbour(root->left, target, k, bestList, depth + 1);
        addNearNeighbour(root, target, bestList, k);
        if (root->right && distance_squared(bestList.front()->data, target) > pow(target[depth%this->k] - root->data[depth%this->k], 2))
            kNearestNeighbour(root->right, target, k, bestList, depth + 1);
    } else if (target[depth%this->k] >= root->data[depth%this->k] && root->right) {
        kNearestNeighbour(root->right, target, k, bestList, depth + 1);
        addNearNeighbour(root, target, bestList, k);
        if (root->left && distance_squared(bestList.front()->data, target) > pow(target[depth%this->k] - root->data[depth%this->k], 2))
            kNearestNeighbour(root->left, target, k, bestList, depth + 1);
    }
    else {
        addNearNeighbour(root, target, bestList, k);
        return;
    }
}

void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList) {
    kNearestNeighbour(root, target, k, bestList, 0);
}


// kNN

kNN::kNN(int k) {
    this->k = k;
}

void kNN::fit(const Dataset &X_train, const Dataset &y_train) {
    int nRows, nCols;
    this->X_train = new Dataset(X_train);
    this->X_train->getShape(nRows, nCols);
    this->y_train = new Dataset(y_train);
    this->numClasses = getNumClasses(y_train);
    this->kdtree = new kDTree(nCols);
    vector<vector<int>> pointList;
    for (auto& row : this->X_train->data) {
        vector<int> point;
        for (auto& ele : row) {
            point.push_back(ele);
        }
        pointList.push_back(point);
    }
    this->kdtree->buildTree(pointList);
}

Dataset kNN::predict(const Dataset &X_test) {
    Dataset y_pred;
    y_pred.columnName = this->y_train->columnName;
    int nRows, nCols;
    X_test.getShape(nRows, nCols);
    int count = 0;
    for (auto& row : X_test.data) {
        vector<int> point;
        for (auto& ele : row) {
            point.push_back(ele);
        }
        vector<kDTreeNode *> bestList;
        this->kdtree->kNearestNeighbour(point, this->k, bestList);
        vector<int> bestLabelList;
        for (auto& best : bestList) {
            bestLabelList.push_back(getLabel(best->data));
        }
        int bestClass = getMajorityClass(bestLabelList);
        y_pred.data.push_back({bestClass});
    }
    return y_pred;
}

int kNN::getNumClasses(const Dataset &y_train) {
    int nRows, nCols;
    y_train.getShape(nRows, nCols);
    int numClasses = 0;
    for (auto& row : y_train.data) {
        for (auto& ele : row) {
            numClasses = max(numClasses, ele);
        }
    }
    return numClasses + 1;
}

int kNN::getMajorityClass(const vector<int> &bestLabelList) {
    vector<int> count(this->numClasses, 0);
    for (auto& label : bestLabelList) {
        count[label]++;
    }
    int maxCount = 0, maxClass = 0;
    for (int label = 0; label < count.size(); label++) {
        if (count[label] > maxCount) {
            maxCount = count[label];
            maxClass = label;
        }
    }
    return maxClass;
}

int kNN::getLabel(const vector<int> &point) {
    list<list<int>>::const_iterator i = this->X_train->data.begin();
    list<list<int>>::const_iterator j = this->y_train->data.begin();
    while(i != this->X_train->data.end() && j != this->y_train->data.end()) {
        if ((*i) == list<int>(point.begin(), point.end())){
            return (*j).front();
        }
        i++;
        j++;
    }
    return -1;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred) {
    int nRows, nCols;
    y_test.getShape(nRows, nCols);
    int correct = 0;
    list<list<int>>::const_iterator i = y_test.data.begin();
    list<list<int>>::const_iterator j = y_pred.data.begin();
    while(i != y_test.data.end() && j != y_pred.data.end()) {
        if ((*i).front() == (*j).front()) {
            correct++;
        }
        i++;
        j++;
    }
    return (double)correct / nRows;
}