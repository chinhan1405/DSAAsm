#include "kNN.hpp"


#define ARRAYLIST_UPDATE_COEFFICIENT 1.5
#define ARRAYLIST_INITIAL_CAPACITY 100

template<typename T>
void ArrayList<T>::resize() {
    int newCapacity = capacity * ARRAYLIST_UPDATE_COEFFICIENT;
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
ArrayList<T>::ArrayList() {
    capacity = ARRAYLIST_INITIAL_CAPACITY;
    size = 0;
    data = new T[capacity];
}

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] data;
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList& other) {
    capacity = other.capacity;
    size = other.size;
    data = new T[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) {
    if (this == &other) {
        return *this;
    }
    delete[] data;
    capacity = other.capacity;
    size = other.size;
    data = new T[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

template<typename T>
void ArrayList<T>::push_back(T value) {
    if (size == capacity) {
        resize();
    }
    data[size++] = value;
}

template<typename T>
void ArrayList<T>::push_front(T value) {
    if (size == capacity) {
        resize();
    }
    for (int i = size; i > 0; i--) {
        data[i] = data[i - 1];
    }
    data[0] = value;
    size++;
}

template<typename T>
void ArrayList<T>::insert(int index, T value) {
    if (index < 0 || index > size) {
        return;
    }
    if (size == capacity) {
        resize();
    }
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

template<typename T>
void ArrayList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        return;
    }
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

template<typename T>
T& ArrayList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("get(): Out of range");
    }
    return data[index];
}

template<typename T>
int ArrayList<T>::length() const {
    return size;
}

template<typename T>
void ArrayList<T>::clear() {
    size = 0;
}

template<typename T>
void ArrayList<T>::print() const {
    if (size == 0) return;
    std::cout << data[0];
    for (int i = 1; i < size; i++) {
        std::cout << " " << data[i] ;
    }
}

template<typename T>
void ArrayList<T>::reverse() {
    for (int i = 0; i < size / 2; i++) {
        T temp = data[i];
        data[i] = data[size - i - 1];
        data[size - i - 1] = temp;
    }
}

template<typename T>
bool ArrayList<T>::contain(T value) const {
    for (int i = 0; i < size; i++) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename T>
double ArrayList<T>::euclideanDistance(const ArrayList<T>& other) const {
    int size_ = this->size;
    if (size != other.size) {
        size_ = std::min(size, other.size);
    }
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (data[i] - other.data[i]) * (data[i] - other.data[i]);
    }
    return sqrt(sum);
}

Dataset::Dataset() {
    data = new ArrayList<List<int>*>();
    columnsName = new ArrayList<std::string>();
}

Dataset::~Dataset() {
    for (int i = 0; i < data->length(); i++) {
        delete data->get(i);
    }
    delete data;
    delete columnsName;
}

Dataset::Dataset(const Dataset& other) {
    //deep copy
    data = new ArrayList<List<int>*>();
    for (int i = 0; i < other.data->length(); i++) {
        ArrayList<int>* row = new ArrayList<int>();
        for (int j = 0; j < other.data->get(i)->length(); j++) {
            row->push_back(other.data->get(i)->get(j));
        }
        data->push_back(row);
    }
    columnsName = new ArrayList<std::string>();
    for (int i = 0; i < other.columnsName->length(); i++) {
        columnsName->push_back(other.columnsName->get(i));
    }
}

Dataset::Dataset(ArrayList<int>& data, std::string columnName) {
    this->data = new ArrayList<List<int>*>();
    for (int i = 0; i < data.length(); i++) {
        ArrayList<int>* row = new ArrayList<int>();
        row->push_back(data.get(i));
        this->data->push_back(row);
    }
    columnsName = new ArrayList<std::string>();
    columnsName->push_back(columnName);
}

Dataset& Dataset::operator=(const Dataset& other) {
    if (this == &other) {
        return *this;
    }
    for (int i = 0; i < data->length(); i++) {
        delete data->get(i);
    }
    delete data;
    data = new ArrayList<List<int>*>();
    for (int i = 0; i < other.data->length(); i++) {
        ArrayList<int>* row = new ArrayList<int>();
        for (int j = 0; j < other.data->get(i)->length(); j++) {
            row->push_back(other.data->get(i)->get(j));
        }
        data->push_back(row);
    }
    delete columnsName;
    columnsName = new ArrayList<std::string>();
    for (int i = 0; i < other.columnsName->length(); i++) {
        columnsName->push_back(other.columnsName->get(i));
    }
    return *this;
}

bool Dataset::loadFromCSV(const char* fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
        columnsName->push_back(cell);
    }
    while (std::getline(file, line)) {
        ArrayList<int>* row = new ArrayList<int>();
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row->push_back(std::stoi(cell));
        }
        data->push_back(row);
    }
    return true;
}

void Dataset::printHead(int nRows, int nCols) const {
    if (nRows <= 0 || nCols <= 0) {
        return;
    }
    std::cout << columnsName->get(0);
    for (int i = 1; i < nCols && i < columnsName->length(); i++) {
        std::cout << " " << columnsName->get(i);
    }
    for (int i = 0; i < nRows && i < data->length(); i++) {
        std::cout << std::endl;
        std::cout << data->get(i)->get(0);
        for (int j = 1; j < nCols && j < data->get(i)->length(); j++) {
            std::cout << " " << data->get(i)->get(j);
        }
    }
}

void Dataset::printTail(int nRows, int nCols) const {
    if (nRows <= 0 || nCols <= 0) {
        return;
    }
    int endRow = data->length();
    int startRow = endRow - nRows;
    if (startRow < 0) {
        startRow = 0;
    }
    int endCol = columnsName->length();
    int startCol = endCol - nCols;
    if (startCol < 0) {
        startCol = 0;
    }
    std::cout << columnsName->get(startCol);
    for (int i = startCol+1; i < endCol; i++) {
        std::cout << " " << columnsName->get(i);
    }
    for (int i = startRow; i < endRow; i++) {
        std::cout << std::endl;
        std::cout << data->get(i)->get(startCol);
        for (int j = startCol+1; j < endCol; j++) {
            std::cout << " " << data->get(i)->get(j);
        }
    }
}

double Dataset::compareSimilarity(const Dataset& other) const {
    int nRows, nCols;
    getShape(nRows, nCols);
    int nRowsOther, nColsOther;
    other.getShape(nRowsOther, nColsOther);
    nRows = std::min(nRows, nRowsOther);
    nCols = std::min(nCols, nColsOther);
    int count = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            if (data->get(i)->get(j) == other.data->get(i)->get(j)) {
                count++;
            }
        }
    }
    return (double)count / (nRows*nCols);
}

void Dataset::getShape(int& nRows, int& nCols) const {
    nRows = data->length();
    if (nRows == 0) {
        nCols = 0;
        return;
    }
    nCols = data->get(0)->length();
}

void Dataset::columns() const {
    std::cout << columnsName->get(0);
    for (int j = 1; j < columnsName->length(); j++) {
        std::cout << " " << columnsName->get(j);
    }
}

bool Dataset::drop(int axis, int index, std::string columnName) {
    if (axis == 0) {
        if (index < 0 || index >= data->length()) {
            return false;
        }
        data->remove(index);
    } else if (axis == 1) {
        int columnIndex = -1;
        for (int i = 0; i < columnsName->length(); i++) {
            if (columnsName->get(i) == columnName) {
                columnIndex = i;
                break;
            }
        }
        if (columnIndex == -1) {
            return false;
        }
        for (int i = 0; i < data->length(); i++) {
            data->get(i)->remove(columnIndex);
        }
        columnsName->remove(columnIndex);
    }
    else return false;
    return true;
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    Dataset result;
    endRow = std::min(endRow, data->length()-1);
    endCol = std::min(endCol, columnsName->length()-1);
    if (endRow==-1) {
        endRow = data->length()-1;
    }
    if (endCol==-1) {
        endCol = columnsName->length()-1;
    }
    for (int i = startRow; i <= endRow; i++) {
        ArrayList<int>* row = new ArrayList<int>();
        for (int j = startCol; j <= endCol; j++) {
            row->push_back(data->get(i)->get(j));
        }
        result.data->push_back(row);
    }
    for (int i = startCol; i <= endCol; i++) {
        result.columnsName->push_back(columnsName->get(i));
    }
    return result;
}

List<List<int>*>* Dataset::getData() const {
    return data;
}

List<int>& Dataset::getRow(int index) const {
    return *(data->get(index));
}

int kNN::getMostCommon(const ArrayList<int>& arr) {
    int nums[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < arr.length(); i++){
        nums[arr.get(i)]++;
    }
    int maxNum = 0;
    for (int i = 0; i < 10; i++){
        if (nums[i] > maxNum) maxNum = nums[i];
    }
    for (int i = 0; i < arr.length(); i++){
        if (nums[arr.get(i)] == maxNum) return arr.get(i);
    }
    return maxNum;
}

kNN::kNN(int k) {
    this->k = k;
}

void kNN::fit(const Dataset& X_train, const Dataset& y_train) {
    this->X_train = X_train;
    this->y_train = y_train;
}

int kNN::predict(const List<int>& x) {
    ArrayList<int> labels;
    int nRows, nCols;
    X_train.getShape(nRows, nCols);
    ArrayList<int> visited;
    for (int i = 0; i < k; i++) {
        int minIndex = 0;
        int j = 0;
        while (j < nRows) {
            if (visited.contain(j)) {
                j++;
                continue;
            }
            if (EuclideanDistance(X_train.getRow(j), x) < EuclideanDistance(X_train.getRow(minIndex), x)) {
                visited.push_back(j);
                minIndex = j;
            }
            j++;
        }
        labels.push_back(y_train.getRow(minIndex).get(0));
    }
    return getMostCommon(labels);
}

Dataset kNN::predict(const Dataset& X_test) {
    ArrayList<int> labels;
    int nRowsTest, nColsTest;
    X_test.getShape(nRowsTest, nColsTest);
    for (int i = 0; i < nRowsTest; i++) {
        labels.push_back(predict(X_test.getRow(i)));
    }
    Dataset result(labels, "label");
    return result;
}

double kNN::score(const Dataset& y_true, const Dataset& y_pred) {
    return y_pred.compareSimilarity(y_true);
}

double EuclideanDistance(const List<int>& a, const List<int>& b) {
    if (a.length() != b.length()) {
        throw std::invalid_argument("euclideanDistance(): a and b have different length");
    }
    double sum = 0;
    for (int i = 0; i < a.length(); i++) {
        sum += (a.get(i) - b.get(i)) * (a.get(i) - b.get(i));
    }
    return sqrt(sum);
}

void train_test_split(Dataset& X, Dataset& y, double test_size,
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test) {
    int nRows, nCols;
    X.getShape(nRows, nCols);
    int nTest = ceil(nRows*test_size);
    int nTrain = nRows - nTest;
    X_train = X.extract(0, nTrain-1, 0, -1);
    X_test = X.extract(nTrain, nRows, 0, -1);
    y_train = y.extract(0, nTrain-1, 0, -1);
    y_test = y.extract(nTrain, nRows, 0, -1);
}
