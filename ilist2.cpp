#include <iostream>

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
struct myiter {
    node<type> *iter;
    myiter(): iter(NULL) {};
    myiter(node<type> *p) {
        iter=p;
    };
    node<type>& operator*(void) {
        return *iter;
    }
    bool show(void) {
        cout<<iter->val<<endl;
    };
    myiter<type> operator=(myiter<type> rval) {
        iter=rval.iter;
        return *this;
    }
    myiter<type>& operator++(void);
    myiter<type>& operator++(int);
    myiter<type>& operator--(void);
    myiter<type>& operator--(int);
    bool operator==(myiter<type>& iterb) {
        if (iter == iterb.iter) {
            return true;
        }
        else {
            return false;
        }
    };
     bool operator!=(myiter<type>& iterb) {
        if (iter == iterb.iter) {
            return false;
        }
        else {
            return true;
        }
    };
};

template<typename type>
myiter<type>& myiter<type>::operator++(void) {
        iter=iter->next;
        return *this;
}

template<typename type>
myiter<type>& myiter<type>::operator--(void) {
        iter=iter->prior;
        return *this;
}

template<typename type>
myiter<type>& myiter<type>::operator++(int) {
        myiter<type> temp;
        temp=*this;
        iter=iter->next;
        return temp;
}

template<typename type>
myiter<type>& myiter<type>::operator--(int) {
        myiter<type> temp;
        temp=*this;
        iter=iter->prior;
        return temp;
}

template<typename type>
class dlist {
private:
    node<type> *head;
    node<type> *tail;
public:
    dlist(void) {
        head= new node<type>;
        tail= new node<type>;
        head->prior=NULL;
        head->next=tail;
        tail->prior=head;
        tail->next=NULL;
    };
    myiter<type> begin(void) {
        myiter<type> temp(head->next);
        return temp;
    };
    myiter<type> end(void) {
        myiter<type> temp(tail);
        return temp;
    };
    bool empty(void) {
        if (head->next == tail) {
            return true;
        }
        else {
            return false;
        }
    };
    int listlen(void);
    bool append(type);
    bool insert(type, myiter<type>);   //insert to the prior of iter_argu;
    int  insert(myiter<type> iter_argu, myiter<type> beg_argu, myiter<type> end_argu);
    bool erase(myiter<type>);
    int  erase(myiter<type> beg_argu, myiter<type> end_argu);
    bool clear(void);
    int assign(myiter<type> beg_argu, myiter<type> end_argu);
    bool show(void);
};

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
bool dlist<type>::insert(type val_argu,myiter<type> iter_argu) {
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
int dlist<type>::insert(myiter<type> iter_argu, myiter<type> beg_argu, myiter<type> end_argu) {
    int len=0;
    myiter<type> i;
    type temp;
    for (i=beg_argu;i != end_argu;++i) {
        temp=i.iter->val;
        insert(temp,iter_argu);
        len++;
    }
    return len;
}

template<typename type>
bool dlist<type>::erase(myiter<type> iter_argu) {
    node<type> *cur_iter=iter_argu.iter;
    cur_iter->prior->next=cur_iter->next;
    cur_iter->next->prior=cur_iter->prior;
    delete cur_iter;
    return true;
}

template<typename type>
int dlist<type>::erase(myiter<type> beg_argu,myiter<type> end_argu) {
    int len=0;
    myiter<type> i;
    for (i=beg_argu;i != end_argu;++i) {
        erase(i);
        len++;
    }
    return len;
}

template<typename type>
int dlist<type>::assign(myiter<type> beg_argu,myiter<type> end_argu) {
    int len;
    myiter<type> i;
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


int main()
{
    dlist<int> list1,list2;
    myiter<int> i;
    list1.insert(1,list1.end());
    list1.append(2);
    list1.clear();
    cout<<list1.empty()<<endl;
    return 0;
}






/*struct test{
    int a;
    static int num;
    test() {
        num++;
    };
    test fun() {
        cout<<"fun"<<endl;
        return *this;
    }
    ~test() {cout<<"des"<<num<<endl;};
};
int test::num=0;*/
