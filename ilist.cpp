#include <iostream>

using namespace std;

//class ilist {};

template<typename type>
class node {
public:
    type item;
    node<type> *next;
    // friend ilist;
    friend bool operator== (node<type> a,node<type> b) {
        if (a.item==b.item) {
            return true;
        }
        return false;
    };
     friend bool operator!= (node<type> a,node<type> b) {
        if (a.item==b.item) {
            return false;
        }
        return true;
    };
    type operator= (type b) {
        item=b;
        return b;
    };
    node(): item(0),next(NULL) {};
    node(type n):  item(n),next(NULL) {};
    type get() {
        return item;
    };
};

template<typename type>
class ilist {
protected:
    node<type> *head;
public:
    ilist() {
        head=new node<type>;
    };
   /*ilist(ilist<type>& l) {
        (*this)=l;
    };*/
    node<type> *first() {
       return head;
    };
    node<type> *tail();
    int inode(node<type> *p,node<type> *q);  //insert node q after p
    int inode(node<type> *);  //push_back
    int inode(node<type> *,type);
    int inode(type);
    int inode(node<type>*,ilist<type>);
    int inode(ilist<type>);
    int del(node<type> *);
    int listlen();
    int show();
    node<type> *seek(type);
    ilist<type> operator= (ilist<type>);
    ~ilist();
};

template<typename type>
node<type> *ilist<type>::tail() {
    node<type> *p=head;
    while (p->next) {
        p=p->next;
    }
    return p;
}

//inode
template<typename type>
int ilist<type>::inode(node<type> *p,node<type> *q) {  //insert node q after p
    q->next=p->next;
    p->next=q;
    return 0;
}

template<typename type>
int ilist<type>::inode(node<type> *q) {
    node<type> *p=tail();
    q->next=p->next;
    p->next=q;
    return 0;
}

template<typename type>
int ilist<type>::inode(node<type> *p,type n) {  //insert a new node after p
    node<type> *q=new node<type>;
    q->item=n;
    q->next=p->next;
    p->next=q;
    return 0;
}

template<typename type>
int ilist<type>::inode(type n) {
    node<type> *q=new node<type>;
    node<type> *p=tail();
    q->item=n;
    p->next=q;
    q->next=NULL;
    return 0;
}

template<typename type>
int ilist<type>::inode(node<type> *p,ilist<type> l) {  //insert a new node after p
    node<type> *q=l.head();
    q->next=p->next;
    p->next=l.tail();
    return 0;
}

template<typename type>
int ilist<type>::inode(ilist<type> l) { //q is new
    node<type> *q=l.first();
    node<type> *p=tail();
    p->next=q;
    return 0;
}

template<typename type>
int ilist<type>::del(node<type> *p) {
    node<type> *q;
    q=p->next;
    p->next=q->next;
    delete q;
    return 0;
}

template<typename type>
int ilist<type>::listlen() {
    int i=0;
    node<type> *p=head;
    while (p->next) {
        p=p->next;
        i++;
    }
    return i;
}

template<typename type>
int ilist<type>::show() {
    node<type> *p=head;
    while (p->next) {
        p=p->next;
        cout<<p->item<<endl;

    }
    return 0;
}

template<typename type>
node<type> *ilist<type>::seek(type n) {
    node<type> *p=head;
    while (p->next) {
        if (p->item == n) {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

template<typename type>
ilist<type>::~ilist() {
    node<type> *p=head,*q;
      while (p->next) {
        q=p;
        p=p->next;
        delete q;
    }
}


template<typename type>
ilist<type> ilist<type>::operator= (ilist<type> l) {
    node<type> *p=l.first()->next;
    node<type> *t;
    node<type> *q=head;
    while (p) {
        t=new node<type>;
        *t=*p;
        q->next=t;
        p=p->next;
        q=t;
    }
    //q->next=NULL;
    show();
    return *this;
}

template<typename type>
class loop_ilist: ilist<type> {
public:
    loop_ilist();
    ~loop_ilist();
    int inode(node<type> q,node<type> *p);
    node<type> *tail() { return NULL; };  //overwrite tail()
};


int main() {
    ilist<int> l1,l2;
    l1.inode(1);
    l2=l1;
    //l2.show();
    return 0;
}

