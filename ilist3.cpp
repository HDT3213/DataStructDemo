#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template<typename type>
struct node {
    type val;
    node<type> *prior;
    node<type> *next;
    node():prior(NULL),next(NULL) {};
    node(type val_argu): val(val_argu),prior(NULL),next(NULL) {};
};

template<typename type>
class dlist {

private:
    node<type> *head;
    node<type> *tail;

public:
      class iterator {
      public:
        node<type> *iter;

        iterator(): iter(NULL) {};

        iterator(node<type> *ptr): iter(ptr) {};

        type& operator*(void) {
            return (*iter).val;
        }

        bool operator==(dlist<type>::iterator rval) {
            if (iter == rval.iter) {
                return true;
            }
            else {
                return false;
            }
        }

        bool operator!=(dlist<type>::iterator rval) {
              if (iter == rval.iter) {
                 return false;
               }
              else {
                 return true;
              }
        }

        dlist<type>::iterator& operator++(void) {
            iter=iter->next;
            return *this;
        }

        dlist<type>::iterator& operator++(int) {
            dlist<type>::iterator temp;
            temp=*this;
            iter=iter->next;
            return temp;
        }

        dlist<type>::iterator& operator--(void) {
             iter=iter->prior;
             return *this;
        }
        dlist<type>::iterator& operator--(int) {
            dlist<type>::iterator temp;
            temp=*this;
            iter=iter->prior;
            return temp;
        }
        //temporary
        dlist<type>::iterator next(void) {
            return iter->next;
        }
      };

public:
    dlist(void);
    dlist<type>::iterator begin(void) {
        dlist<type>::iterator temp(head->next);
        return temp;
    };
    dlist<type>::iterator end(void) {
        dlist<type>::iterator temp(tail);
        return temp;
    };
    bool empty(void);
    int  listlen(void);
    bool append(type);
    bool insert(type, dlist<type>::iterator);   //insert to the prior of iter_argu;
    int  insert(dlist<type>::iterator iter_argu, dlist<type>::iterator beg_argu, dlist<type>::iterator end_argu);
    bool erase(dlist<type>::iterator);
    int  erase(dlist<type>::iterator beg_argu, dlist<type>::iterator end_argu);
    bool clear(void);
    int  assign(dlist<type>::iterator beg_argu, dlist<type>::iterator end_argu);
    bool show(void);

    bool pop_back(void);
    ~dlist();

    //temporary
    bool append2(type val);
};


template<typename type>
dlist<type>::dlist() {
    head= new node<type>;
    tail= new node<type>;
    head->prior=NULL;
    head->next=tail;
    tail->prior=head;
    tail->next=NULL;
}

template<typename type>
bool dlist<type>::empty() {
    if (head->next == tail) {
        return true;
    }
    else {
        return false;
    }
}

template<typename type>
bool dlist<type>::append(type val_argu) {
    node<type> *temp_ptr= new node<type>;
    temp_ptr->val=val_argu;
    //insert
    tail->prior->next=temp_ptr;
    temp_ptr->prior=tail->prior;
    temp_ptr->next=tail;
    tail->prior=temp_ptr;
    return true;
}

template<typename type>
bool dlist<type>::insert(type val_argu, dlist<type>::iterator iter_argu) {
    node<type> *cur_iter=iter_argu.iter;
    node<type> *temp_ptr= new node<type>;
    temp_ptr->val=val_argu;
    //insert
    cur_iter->prior->next=temp_ptr;
    temp_ptr->prior=cur_iter->prior;
    temp_ptr->next=cur_iter;
    cur_iter->prior=temp_ptr;
    return true;
}

template<typename type>
int dlist<type>::insert(dlist<type>::iterator iter_argu, dlist<type>::iterator beg_argu, dlist<type>::iterator end_argu) {
    int len=0;
    dlist<type>::iterator i;
    type temp;
    for (i=beg_argu;i != end_argu;++i) {
        temp=i.iter->val;
        insert(temp,iter_argu);
        len++;
    }
    return len;
}

template<typename type>
bool dlist<type>::erase(dlist<type>::iterator iter_argu) {
    node<type> *cur_iter=iter_argu.iter;
    cur_iter->prior->next=cur_iter->next;
    cur_iter->next->prior=cur_iter->prior;
    delete cur_iter;
    return true;
}

template<typename type>
int dlist<type>::erase(dlist<type>::iterator beg_argu,dlist<type>::iterator end_argu) {
    int len=0;
    dlist<type>::iterator i;
    for (i=beg_argu;i != end_argu;++i) {
        erase(i);
        len++;
    }
    return len;
}

template<typename type>
int dlist<type>::assign(dlist<type>::iterator beg_argu,dlist<type>::iterator end_argu) {
    int len;
    dlist<type>::iterator i;
    clear();
    len=insert(end(),beg_argu,end_argu);
    return len;
}

template<typename type>
int dlist<type>::listlen() {
    int len=0;
    node<type> *p=head;
    while (p->next != tail ) {
        p=p->next;
        len++;
    }
    return len;
}

template<typename type>
bool dlist<type>::show() {
    node<type> *p=head;
    while (p->next != tail ) {
        p=p->next;
        cout<<p->val<<" ";
    }
    cout<<endl;
    return true;
}

template<typename type>
bool dlist<type>::clear() {
    node<type> *p=head,*q;
      while (p->next != tail) {
        q=p;
        p=p->next;
        delete q;
    }
    return true;
}

template<typename type>
bool dlist<type>::pop_back() {
    node<type> *cur_iter = tail->prior;
    cur_iter->prior->next=tail;
    tail->prior=cur_iter->prior;
    delete cur_iter;
    return true;
}

template<typename type>
dlist<type>::~dlist() {
   // clear();
}

template<typename type>
bool dlist<type>::append2(type val_argu) {
     node<type> *temp_ptr= new node<type>;
     temp_ptr->val=val_argu;
     //append
    head->next->prior = temp_ptr;
    temp_ptr->next = head->next;
    temp_ptr->prior = head;
    head->next = temp_ptr;
    return true;
}


template<typename type>
void sort(dlist<type> list1) {
    type temp;
    dlist<int>::iterator i, j, p;
    for (i = list1.begin(); i != list1.end(); i++) {
        p = i;
        for (j = i.next(); j != list1.end(); j++) {
            if( *j < *p ) {
                p = j;
            }
        }
        if (p != i) {
            temp = *p;
            *p = *i;
            *i = temp;
        }
    }
}


//test
void traver(dlist<int> list1) {
    dlist<int>::iterator iter;
    for (iter = list1.begin(); iter != list1.end(); iter++) {
        cout << *iter << ' ';
    }
    if (list1.empty()) {
        cout << "empty list!";
    }
    cout << endl;
}

int test1()
{
    int temp;
    dlist<int> list1;
    dlist<int>::iterator iter;
    //input
    while(1) {
        cin >> temp;
        if (temp == 0) {
            break;
        }
        list1.append2(temp);
    }
    while (!list1.empty()) {
        traver(list1);
        list1.pop_back();
    }
    traver(list1);
    return 0;
}

int test2() {
    int temp;
    dlist<int> list1;
    dlist<int>::iterator iter;
    //input
    while(1) {
        cin >> temp;
        if (temp == 0) {
            break;
        }
        list1.append(temp);
    }
    sort(list1);
    list1.show();
}

int main(void) {
    test1();
    cout << endl;
    test2();
    cout << endl;
}

