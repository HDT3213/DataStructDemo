#include <iostream>
#define M 1024

using namespace std;

template<typename key_t, typename val_t>
struct node{
    key_t key;
    val_t val;
    bool vacant;
    node(void): vacant(true) {};
    friend node<key_t, val_t> mknode(key_t keyword, val_t value);
};

template<typename key_t, typename val_t>
inline node<key_t, val_t> mknode(key_t keyword, val_t value) {
    node<key_t, val_t> temp;
    temp.vacant=false;
    temp.key=keyword;
    temp.val=value;
    return temp;
};

template<typename key_t, typename val_t>
class b_array {
//protected:
public:
    node<key_t, val_t> arr[M];
    int pow2(int k) {
        if (k ) {
            return 2<<(k-1);
        }
        else {
            return 1;
        }
    }
    void coor(int& k, int& i, int n) {
        for (k=0;n>=pow2(k)-1; k++);
        k--;
        i=n+1-pow2(k);
        return;
    };
    int index(int k, int i) {
        return pow2(k)+i-1;
    };
    int lnext(int k, int i) {
        return pow2(k+1)+2*i-1;
    };
    int lnext(int n) {
        int i,k;
        coor(k, i, n);
        return pow2(k+1)+2*i-1;;
    };
    int rnext(int k, int i) {
        return pow2(k+1)+2*i;
    };
    int rnext(int n) {
        int i,k;
        coor(k, i, n);
        return pow2(k+1)+2*i;
    };
    int prior(int k, int i) {
            i /= 2; // int / int
            k--;
            return index(k,i);
    };
    int prior(int n) {
        int i,k;
        coor(k,i,n);
        i /= 2; // int / int
        k--;
        return index(k,i);
    };
    bool leaf(int iter) {
        if (arr[lnext(iter)].vacant==true && arr[rnext(iter)].vacant==true) {
            return true;
        }
        else {
            return false;
        }
    }
    int  seek(key_t keyword);
public:
    b_array(void) {
        int i;
        for (i=0;i<M;i++) {
            arr[i].vacant=true;
        }
    };
    node<key_t, val_t> at(key_t keyword);
    bool append(key_t keyword, val_t value);
};

template<typename key_t, typename val_t>
int b_array<key_t, val_t>::seek(key_t keyword) {
    int iter=0;
    while (arr[iter].key != keyword && arr[iter].vacant == false && iter < M) {
        if (arr[iter].key < keyword) {
            iter=rnext(iter);
        }
        else if (arr[iter].key > keyword) {
            iter=lnext(iter);
        }
    }
    if (arr[iter].vacant == true && iter == M) {
        return -1;
    }
    else if (arr[iter].key == keyword) {
        return iter;
    }
}

template<typename key_t, typename val_t>
node<key_t, val_t> b_array<key_t, val_t>::at(key_t keyword) {
    int iter=0;
    node<key_t, val_t> temp;
    while (arr[iter].key != keyword && arr[iter].vacant == false && iter < M) {
        if (arr[iter].key < keyword) {
            iter=rnext(iter);
        }
        else if (arr[iter].key > keyword) {
            iter=lnext(iter);
        }
    }
    if (arr[iter].vacant == true && iter == M) {
        temp.vacant=true;
        return temp;
    }
    else if (arr[iter].key == keyword) {
        return arr[iter];
    }
}

template<typename key_t, typename val_t>
bool b_array<key_t, val_t>::append(key_t keyword, val_t value) {
    int iter=0;
    while (arr[iter].key != keyword && arr[iter].vacant == false && iter < M) {
        if (arr[iter].key < keyword) {
            iter=rnext(iter);
        }
        else if (arr[iter].key > keyword) {
            iter=lnext(iter);
        }
    }
    if (iter < M) {
        arr[iter].vacant = false;
        arr[iter].key=keyword;
        arr[iter].val=value;
        return true;
    }
    else {
        return false;
    }
}

template<typename key_t, typename val_t>
bool b_array<key_t, val_t>::clear(void) {
    int iter;
    for (iter=0;iter<M;iter++) {
        arr[iter].vacant=true;
    }
    return true;
}

template<typename key_t, typename val_t>
bool b_array<key_t, val_t>::copy(node<key_t, val_t> *dest, int root) {
    int iter=root;
    if (leaf(root) || (dest[lnext(root)].vacant==false && dest[rnext(root)].vacant==false)) {
        dest[root]=arr[root];
    }
    else {
        copy(dest, lnext(root));
        copy(dest, rnext(root));
    }
    return true;
}

template<typename key_t, typename val_t>
bool b_array<key_t, val_t>::cle(int root) {
    while (arr[root].vacant == true) {
        if (leaf(root)) {
            arr[root].vacant = true;
        }
        else {
            cle(lnext(root));
            cle(rnext(root));
        }
    }
    return true;
}

int main()
{
    b_array<int,int> ar1;
    node<int,int> temp,dest[M];
    int k,i;
    ar1.append(10,10);
    ar1.append(5,5);
    ar1.append(20,20);
    ar1.append(4,4);
    ar1.append(12,12);
    ar1.append(18,18);
    ar1.cle(0);
    return 0;
}
