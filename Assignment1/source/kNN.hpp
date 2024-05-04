#include "main.hpp"


template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual bool contain(T value) const = 0;
};

template<typename T>
class ArrayList : public List<T> {
private:
    T* data;
    int capacity;
    int size;
    void resize();
public:
    ArrayList();
    ~ArrayList();
    ArrayList(const ArrayList& other); // deep copy
    ArrayList& operator=(const ArrayList& other);
    void push_back(T value);
    void push_front(T value);
    void insert(int index, T value);
    void remove(int index);
    T& get(int index) const;
    int length() const;
    void clear();
    void print() const;
    void reverse();
    bool contain(T value) const;
    double euclideanDistance(const ArrayList<T>& other) const;
};

class Dataset {
private:
    List<List<int>*>* data;
    List<std::string>* columnsName;
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset(ArrayList<int>& data, std::string columnName = "");
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    double compareSimilarity(const Dataset& other) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columnName = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    List<List<int>*>* getData () const;
    List<int>& getRow(int index) const;
};

class kNN {
private:
    int k;
    Dataset X_train, y_train;
    int getMostCommon(const ArrayList<int>& arr);
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    int predict(const List<int>& x);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

double EuclideanDistance(const List<int>& a, const List<int>& b);
void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed