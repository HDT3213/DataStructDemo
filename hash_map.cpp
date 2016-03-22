#include <iostream>
#include <string>

using namespace std;

template<typename key_t, typename val_t>
class Map {
protected:
    struct Cell {
        int key;
        val_t val;
        Cell *next;
        Cell() : next(NULL) {};
    };
    const static int Len = 1000;
    Cell cells[Len];
    int series(key_t key);
public:
    Map();
    const val_t *at(key_t key);
    void append(key_t key, val_t val);
    void erase(key_t key);
};

template<typename key_t, typename val_t>
Map<key_t, val_t>::Map() {
    int i = 0;
    for (i = 0; i < Len; i++) {
        cells[i].key = -1;
    }
}

template<typename key_t, typename val_t>
int Map<key_t, val_t>::series(key_t key) {
    char *str = (char *)&key;
    int i, sum = 0;
    for (i = 0; i < sizeof(key_t); i++) {
        sum += str[i];
    }
    return (sum > 0) ? (sum) : (-sum);
}

template<typename key_t, typename val_t>
void Map<key_t, val_t>::append(key_t keyArgu, val_t val) {
    int key = series(keyArgu);
    int i = key % Len;
    if (cells[i].key == -1) {
        cells[i].key  = key;
        cells[i].val  = val;
        cells[i].next = NULL;
    }
    else {
        Cell *ptr = cells[i].next;
        while (ptr->next) {
            if (ptr->key == key) {
                return;
            }
            ptr = ptr->next;
        }
        ptr->next = new Cell;
        ptr = ptr->next;

        ptr->val = val;
        ptr->next = NULL;
    }
}

template<typename key_t, typename val_t>
const val_t *Map<key_t, val_t>::at(key_t keyArgu) {
    int key = series(keyArgu);
    int i = key % Len;
    if (cells[i].key == key) {
        return &cells[i].val;
    }
    else {
        Cell *ptr = &cells[i];
        bool t = false;
        while (ptr->next) {
            if (ptr->key == key) {
                t = true;
                break;
            }
            ptr = ptr->next;
        }
        if (t) {
            return &ptr->val;
        }
    }
   return NULL;
}

template<typename key_t, typename val_t>
void Map<key_t, val_t>::erase(key_t keyArgu) {
    int key = series(keyArgu);
    int i = key % Len;
    Cell *ptr, *temp;
    //remove the node and re-mark the flag
    if (cells[i].key == key) {
        ptr = cells[i].next;
        if (ptr) {
            cells[i] = *ptr;
        }
        else {
            temp = new Cell;
            temp->key = -1;
            cells[i] = *temp;
        }
    }
    else {
        //search
        bool t = false;
        ptr = &cells[i];
        while (ptr->next) {
            if (ptr->next->key == key) {
                t = true;
                break;
            }
            ptr = ptr->next;
        }
        //remove the node
        if (t) { //ptr->next == target_ptr
            temp = ptr->next;
            ptr->next = temp->next;
            delete temp;
        }
    }
}


int main()
{
    string nameA("yichya"),nameB("jing");
    int numA = 5211314, numB = 74748886;

    Map<int, string> mapA;
    mapA.append(numA,nameA);
    mapA.append(numB,nameB);
    cout << *mapA.at(numA) << endl;
    cout << *mapA.at(numB) << endl;
    mapA.erase(numA);
    const string *str = mapA.at(numA) ;
    if (str) {
        cout << *str << endl;
    }
    else {
        cout << "(null)" << endl;
    }
    cout << *mapA.at(numB) << endl;
    cout << endl;

    Map<string ,int> mapB;
    mapB.append(nameA,numA);
    mapB.append(nameB,numB);
    cout << *mapB.at(nameA) << endl;
    cout << *mapB.at(nameB) << endl;
    mapB.erase(nameA);
    const int *ptr = mapB.at(nameA);
     if (ptr) {
        cout << *ptr << endl;
    }
    else {
        cout << "(null)" << endl;
    }
    cout << *mapB.at(nameB) << endl;
    return 0;
}
