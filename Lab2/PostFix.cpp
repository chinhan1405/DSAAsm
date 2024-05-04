#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void processElement(int elem, stack<int>& st) {
    if (elem>=0) st.push(elem);
    else {
        int second = st.top();
        st.pop();
        int first = st.top();
        st.pop();
        if (elem==-1) st.push(first+second);
        else if (elem==-2) st.push(first-second);
        else if (elem==-3) st.push(first*second);
        else st.push(first/second);
    }
}

int evaluatePostfix(string expr){
    vector<int> converted;
    int val = 0;
    for (int i=0; i<(int)expr.length(); i++) {
        char ch = expr[i];
        if (ch==' ') {
            if (expr[i-1]!=' ') {
                converted.push_back(val);
                val = 0;
            }
        }
        else if (ch=='+') val = -1;
        else if (ch=='-') val = -2;
        else if (ch=='*') val = -3;
        else if (ch=='/') val = -4;
        else {
            val = val*10 + (int)ch - 48;
        }
    }
    if (val<0) converted.push_back(val);
    stack<int> st;
    int size = converted.size();
    for (int i=0; i<size; i++) {
        processElement(converted[i], st);
    }
    return st.top();
}


int main() {
    string expr = "0 200 + 10    / 5 * 7 +   ";
    cout << evaluatePostfix(expr) << endl;
    return 0;
}

