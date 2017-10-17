#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class PQ_unordered {
private:
    vector<int> v;
public:
    long long cmpCount = 0;
    PQ_unordered() {}
    ~PQ_unordered() {}
    void insert(int x) { //simple O(1) insert
        v.push_back(x);
        return;
    }
    int pop_min() { //pop does bulk of the sorting
        int size = v.size();
        int smallest = 2147483647; //max int value
        int pos, tmp, ret;
        for (int i=0; i<size; i++) {
            if (v[i] < smallest) {
                smallest = v[i];
                pos = i;
                cmpCount++; //count + 1 for each comparison made
            }
            else cmpCount++; //even if the if condition is not met, a comparison was still made
        }
        tmp = v[pos];
        v[pos] = v[size-1];
        v[size-1] = tmp;
        ret = v[size-1];
        v.pop_back();
        return ret;
    }
    bool empty() {
        if (v.empty()) return true;
        else return false;
    }
};

class PQ_ordered {
private:
    vector<int> v;
public:
    long long cmpCount = 0;
    PQ_ordered() {}
    ~PQ_ordered() {}
    void insert(int x) { //insert does bulk of the sorting
        v.push_back(x);
        int size = v.size();
        int tmp;
        for (int i=0; i<size; i++) {
            int j = i;
            cmpCount++; //count + 1 each time for loop runs and evaluates while loop condition
            while (j > 0 && v[j] > v[j-1]) {
                tmp = v[j];
                v[j] = v[j-1];
                v[j-1] = tmp;
                j--;
                cmpCount++; //count + 1 for each time while loop is run and swaps are made
            }
        }
        return;
    }
    int pop_min() { //simple O(1) pop
        int size = v.size();
        int tmp = v[size-1];
        v.pop_back();
        return tmp;
    }
    bool empty() {
        if (v.empty()) return true;
        else return false;
    }
};

class PQ_heap {
public:
    vector<int> v;
    long long cmpCount = 0;
    PQ_heap() {
        //makeHeap();
    }
    ~PQ_heap() {}
    void travLeft(int start, int end) { //bubble up
        int childPos = end;
        while (childPos > start) {
            int parentPos = (childPos-1)/2; //in heap, child node is at position parent/2; -1 accounts for starting at pos 0; sets child node as new parent
            if (v[childPos] < v[parentPos]) {
                int tmp = v[parentPos];
                v[parentPos] = v[childPos];
                v[childPos] = tmp;
                childPos = parentPos;
                cmpCount++;
            }
            else {
                cmpCount++;
                break;
            }
        }
        return;
    }
    void travRight(int start, int end) { //bubble down
        int parent = start;
        while ((parent*2)+1 <= end) {
            int left = (parent*2)+1; //left child is parent*2; +1 to account for starting at pos 0
            int right = (parent*2)+2; //right child is (parent*2)+1; extra +1 is to account for starting at pos 0
            int swapPos = parent;
            if (v[swapPos] > v[left]) {
                swapPos = left;
                cmpCount++;
            }
            if (end >= right && v[right] < v[swapPos]) {
                swapPos = right;
                cmpCount++;
            }
            if (swapPos != parent) {
                int tmp = v[parent];
                v[parent] = v[swapPos];
                v[swapPos] = tmp;
                parent = swapPos;
                cmpCount++;
            }
            else {
                cmpCount++;
                break;
            }
        }
        return;
    }
    /*
    void makeHeap() {
      int size = v.size();
      cout << v.size() << "\n";
      int mid = (size-2)/2; //root
      while (mid >= 0) {
        travRight(mid, size-1);
        mid--;
      }
      return;
    }
    */
    void insert(int x) {
      v.push_back(x);
      travLeft(0, v.size()-1);
      return;
    }
    int pop_min() {
        int back = v.size()-1;
        int tmp = v[0];
        v[0] = v[back];
        v[back] = tmp;
        v.pop_back();
        travRight(0, back-1);
        return tmp;
    }
    bool empty() {
        if (v.size() == 0) return true;
        else return false;
    }
};

template<class PQ>
void pq_sort(vector<int>& v) {
    PQ pq;
    for(int x : v) {
        pq.insert(x);
    }
    v.clear();
    while (!pq.empty()) {
        v.push_back(pq.pop_min());
    }
    cout << "Comparisons: " << pq.cmpCount << "\n";
    return;
}