#include <stdio.h>
#include <stdlib.h>
#define key_t char

typedef struct node{
    key_t key;
    struct node *prior;
    struct node *left;
    struct node *right;
}node;

int num=0;
inline int init_node(node *this){
    this->key='\0';
    this->prior=NULL;
    this->left=NULL;
    this->right=NULL;
    return 0;
}

inline node *append_node(node *prior_argu,key_t key_argu) {
    node *nptr;
    nptr=(node *)malloc(sizeof(node));
    init_node(nptr);
    nptr->prior = prior_argu;
    nptr->key = key_argu;
    if (key_argu < prior_argu->key) {
        prior_argu->left=nptr;
    }
    else if (key_argu > prior_argu->key) {
        prior_argu->right=nptr;
    }
    return nptr;
};

//using root ptr,and the root saves data too. using nullptr as the end.
inline int examp_tree(node *root) {
    root->key='m';
    //1st sub tree
    append_node(root,'f');
    append_node(root,'s');
    //2nd sub tree
    append_node(root->left,'d');
    append_node(root->left,'i');
    append_node(root->right,'p');
    append_node(root->right,'v');
    //3rd sub tree
    append_node(root->left->left,'b');
    append_node(root->left->left,'e');
    append_node(root->left->right,'g');
    append_node(root->left->right,'k');
    append_node(root->right->left,'n');
    append_node(root->right->left,'q');
    append_node(root->right->right,'t');
    append_node(root->right->right,'w');
    return 14;
}


int traver(node *root) { //unrecursion inorder traver
    node *ptr=root;
    node *stack[1024]={NULL};
    int top=0;//top of stack
    while (ptr || top>0) {
        if (ptr) {
            stack[top++]=ptr;//push
            ptr=ptr->left;
        }
        else {
            ptr=stack[--top];//ptr=stack top;pop;
            printf("%c ",ptr->key);//visit root
            num++;
            ptr=ptr->right;
        }
    }
    return num;
}

int depth(node *root) {
    int d1,d2;
    if (!root) {
        return 0;
    }
    d1=depth(root->left);
    d2=depth(root->right);
    return ((d1>d2)?d1:d2) + 1;
}

node *at(node *root, key_t key_argu) {
    node *ptr = root;
    while (ptr->key != key_argu) {
        if (ptr->left != NULL && key_argu < ptr->key ) {
            ptr = ptr->left;
        }
        else if (ptr->right != NULL &&  ptr->key < key_argu ) {
            ptr = ptr->right;
        }
        else {
            return NULL;
        }
    }
    return ptr;
}

node *append(node *root, key_t key_argu) { // left is prior
    node *ptr = root, *nptr;
    //empty
    if (root->left == NULL && root->right==NULL) {
        root->key = key_argu;
        return root;
    }
    //non-empty
    //seek position
    while (ptr->key != key_argu) {
        if (key_argu < ptr->key ) {
            if (ptr->left) {
                ptr = ptr->left;
            }
            else {
                break;
            }
        }
        else if ( ptr->key < key_argu ) {
            if (ptr->right) {
                ptr = ptr->right;
            }
            else {
                break;
            }
        }
    }
    nptr=append_node(ptr,key_argu);
    return nptr;
}

int rm0(node *root,node *ptr) {//no-root and with a full sub tree
    node *temp;
    temp = ptr;
    // replace ptr for ptr->left sub tree
    if (ptr == ptr->prior->left) {
        ptr->prior->left = ptr->left;
    }
     else if (ptr == ptr->prior->right) {
        ptr->prior->right = ptr->left;
    }
    //seek position for ptr->right sub tree
    ptr = ptr->left; //update ptr
    while (ptr->right) {
        ptr = ptr->right;
    }
    ptr->right = temp->right;
    free(temp);
    return 0;
}

node *rm(node *root,key_t key_argu) { //cannot
    node *ptr;
    ptr = at(root,key_argu);
    if (ptr->left == NULL && ptr->right == NULL) {
         if (ptr == ptr->prior->left) {
            ptr->prior->left = NULL;
        }
        else {
            ptr->prior->right = NULL;
        }
        free(ptr);
    }
    else if (ptr->left != NULL && ptr->right == NULL) {
        if (ptr == ptr->prior->left) {
            ptr->prior->left = ptr->left;
        }
        else {
            ptr->prior->right = ptr->left;
        }
        free(ptr);
    }
    else if (ptr->left == NULL && ptr->right != NULL) {
        if (ptr == ptr->prior->left) {
            ptr->prior->left = ptr->right;
        }
        else {
            ptr->prior->right = ptr->right;
        }
        free(ptr);
    }
    else if (ptr->left != NULL && ptr->right != NULL) {
        rm0(root,ptr);
    }
    return root;
}

int clear(node *root) {
    node *ptr=root,*temp;
    if (ptr) {
        temp = ptr->right;
        clear(ptr->left);
        free(ptr);
        clear(temp);
    }
}

int clear2(node *root) {
    node *ptr=root,*temp;
    node *stack[1024]={NULL};
    int top=0;//top of stack
    while (ptr || top>0) {
        if (ptr) {
            stack[top++]=ptr;//push
            ptr=ptr->left;
        }
        else {
            ptr=stack[--top];//ptr=stack top;pop;
            temp = ptr;
            ptr=ptr->right;
            free(temp);
        }
    }
    return num;
}

int main(void) {
    char ch;
    int n;
    node *temp,*root=(node *)malloc(sizeof(node));
    examp_tree(root);
    //display
    num=0;
    temp = at(root, 'b');
    rm(root,'i');
    n=traver(root);
    printf("%d\n",n);
    return 0;
}
