#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 32

typedef struct Node{
    char ch;
    struct Node *prior;
    struct Node *left;
    struct Node *right;
}Node;

int num=0;
inline int init_Node(Node *this){
    this->ch='\0';
    this->prior=NULL;
    this->left=NULL;
    this->right=NULL;
    return 0;
}

inline Node *append_Node(Node *prior_argu,char ch_argu) {
    Node *nptr;
    nptr=(Node *)malloc(sizeof(Node));
    init_Node(nptr);
    nptr->prior=prior_argu;
    nptr->ch=ch_argu;
    if (ch_argu < prior_argu->ch) {
        prior_argu->left=nptr;
    }
    else if (ch_argu > prior_argu->ch) {
        prior_argu->right=nptr;
    }
    return nptr;
};

//using root ptr,and the root saves data too. using nullptr as the end.
inline int examp_tree(Node *root) {
    root->ch='m';
    //1st sub tree
    append_Node(root,'f');
    append_Node(root,'s');
    //2nd sub tree
    append_Node(root->left,'d');
    append_Node(root->left,'i');
    append_Node(root->right,'p');
    append_Node(root->right,'v');
    //3rd sub tree
    append_Node(root->left->left,'b');
    append_Node(root->left->left,'e');
    append_Node(root->left->right,'g');
    append_Node(root->left->right,'k');
    append_Node(root->right->left,'n');
    append_Node(root->right->left,'q');
    append_Node(root->right->right,'t');
    append_Node(root->right->right,'w');
    return 15;
}

int preorder(Node *root) {
    if (root != NULL) {
        printf("%c ",root->ch);
        preorder(root->left);
        preorder(root->right);
        num++;
    }
     return num;
}

int preorder2(Node *root) {
    Node *ptr=root;
    Node *stack[1024]={NULL};
    int top=0;//top of stack
    while (ptr || top>0){
        if (ptr) {
            stack[top++]=ptr;//push
            printf("%c ",ptr->ch);//visit root
            num++;
            ptr=ptr->left;
        }
        else {
            ptr=stack[--top]; //ptr=stack top;pop;
            ptr=ptr->right;

        }
    }
    return num;
}

int inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%c ",root->ch);
        inorder(root->right);
        num++;
    }
     return num;
}

int inorder2(Node *root) {
    Node *ptr=root;
    Node *stack[1024]={NULL};
    int top=0;//top of stack
    while (ptr || top>0) {
        if (ptr) {
            stack[top++]=ptr;//push
            ptr=ptr->left;
        }
        else {
            ptr=stack[--top];//ptr=stack top;pop;
            printf("%c ",ptr->ch);//visit root
            num++;
            ptr=ptr->right;
        }
    }
    return num;
}

int postorder(Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ",root->ch);
        num++;
    }
     return num;
}

int postorder2(Node *root) {
    Node *ptr=root;
    Node *stack[1024]={NULL};
    Node *previsited=NULL;//The last Node has been visited
    int top=0;//top of stack
    while (ptr || top > 0) {
        while (ptr) {
            stack[top++]=ptr;//push
            ptr=ptr->left;
        }
        ptr=stack[top-1];
        if (ptr->right==NULL || ptr->right == previsited) {
            printf("%c ",ptr->ch);//visit root
            num++;
            previsited=ptr;
            top--;
            ptr = NULL;
        }
        else {
            ptr = ptr -> right;
        }
    }
    return num;
}

/*int postorder3(Node *root) { //postorder traver wihth two stacks
    Node *ptr=root;
    Node *stack1[1024]={NULL},*stack2[1024]={NULL};
    int top1=0,top2=0;//top of stack
    stack1[top1++]=ptr;//push into stack1
    while (top1 > 0) {
        ptr=stack1[--top1];//ptr = stack1.top();stack1.pop()
        stack2[top2++]=ptr;//stack2.push(ptr)
        if (ptr->left) {
            stack1[top1++]=ptr->left;//stack1.push(ptr->left)
        }
        if (ptr->right) {
            stack2[top2++]=ptr->right;//stack2.push(ptr->right)
        }
    }
     while (top2 > 0) {
            printf("%c ",stack2[--top2]->ch);//stack2.top();stack2.pop();
            num++;
        }
    return num;
}*/

int levelorder(Node *root) {
    Node *ptr=root;
    Node *queue[1024]={NULL};
    int front=-1,back=0;//(front,back)
    if (ptr) {
        printf("%c ",ptr->ch);
        num++;
        queue[back++]=ptr;//queue.push(ptr);
    }
    while (back > front+1) {//queue.empty()==false;
        ptr=queue[++front];//ptr=queue.front();queue.pop();
        if (ptr->left) {
            printf("%c ",ptr->left->ch);
            num++;
            queue[back++]=ptr->left;//queue.push(ptr->left);
        }
        if (ptr->right) {
            printf("%c ",ptr->right->ch);
            num++;
            queue[back++]=ptr->right;//queue.push(ptr->left);
        }
    }
    return num;
}

int depth(Node *root) {
    int d1,d2;
    if (!root) {
        return 0;
    }
    d1=depth(root->left);
    d2=depth(root->right);
    return ((d1>d2)?d1:d2) + 1;
}

typedef Node* NodePtr;
void creat(NodePtr *rootPtr,char *mid, char * post, int mleft, int mright,int pleft, int pright) {

    *rootPtr = (Node *)malloc( sizeof(Node) );
    NodePtr root = *rootPtr;
    root->ch  = post[pright];
    root->left = NULL;
    root->right = NULL;

    int pos = mleft;
    while (mid[pos] != post[pright]) {
        pos++;
    }
    int Len = pos - mleft;
    if (pos > mleft) {
        creat(&root->left, mid, post, mleft, pos-1, pleft, pleft + Len -1);
    }
    if (pos < mright) {
        creat(&root->right, mid, post, pos+1, mright, pleft + Len, pright - 1);
    }

}

void test(void)
{
    int n;
    Node *root;
    root=(Node *)malloc(sizeof(Node));
    examp_tree(root);

    printf("preorder\n");
    num=0;
    n=preorder(root);
    printf("%d\n",n);
    printf("preorder2\n");
    num=0;
    n=preorder2(root);
    printf("%d\n",n);

    printf("inorder\n");
    num=0;
    n=inorder(root);
    printf("%d\n",n);
    printf("inorder2\n");
    num=0;
    n=inorder2(root);
    printf("%d\n",n);

    printf("postorder\n");
    num=0;
    n=postorder(root);
    printf("%d\n",n);
    printf("postorder2\n");
    num=0;
    n=postorder2(root);
    printf("%d\n",n);

    printf("levelorder\n");
    num=0;
    n=levelorder(root);
    printf("%d\n",n);

    n=depth(root);
    printf("depth:%d\n",n);

    char mid[M], post[M];
    gets(mid);
    gets(post);
    creat(&root, mid, post, 0, strlen(mid)-1, 0, strlen(post)-1);
    preorder(root);
}

int main() {
    test();
    return 0;
}
