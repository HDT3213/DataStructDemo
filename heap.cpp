#include <iostream>
//#include <vector>

using namespace std;

template<typename val_t>
class MinHeap {
protected:
    const static size_t capcity = 10000;
    size_t size;
    val_t vec[capcity];
public:
    MinHeap();
    void insert(val_t val);
    bool empty();
    void rmMin();
    val_t getMin() {
        return vec[1];
    };
    ~MinHeap() = default;
};

template<typename val_t>
MinHeap<val_t>::MinHeap() {
    size = 0;
}

template<typename val_t>
bool MinHeap<val_t>::empty() {
    if (size) {
        return false;
    }
    else {
        return true;
    }
}

template<typename val_t>
void MinHeap<val_t>::insert(val_t val) {
    size_t  i;
    for (i = ++size; vec[i/2] > val; i /= 2) { //covert > to <, to get a max heap
        vec[i]  =  vec[i / 2];
    }
    vec[i] =  val;
}

template<typename val_t>
void MinHeap<val_t>::rmMin() {
    size_t  i, next;
    val_t min, last;
    if (empty()) {
        return;
    }
    min  = vec[1];
    last = vec[size--];
    for (i = 1; i * 2 <= size; i = next) {
        //find smaller next
        next = i * 2;
        if (next != size && vec[next + 1] < vec[next]) {
            next++;
        }
        //
        if (last > vec[next]) {
            vec[i] = vec[next];
        }
        else {
            break;
        }
    }
    vec[i] = last;
}

int main() {
    MinHeap<int> que;
    que.insert(2);
    que.insert(1);
    cout << que.getMin() << endl;
    que.rmMin();
    cout << que.getMin() << endl;
    return 0;
}