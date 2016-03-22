#include <stdio.h>
#include <stdlib.h>
#define type int
#define typef "%d"

#define M 16
typedef struct node {
    type val;
    struct node *prior;
    struct node *next;
}node;

#define ini(head , tail) \
{\
     head = (node *)malloc(sizeof(node));\
     tail = (node *)malloc(sizeof(node));\
     head->prior=NULL;\
     head->next=tail;\
     tail->prior=head;\
     tail->next=NULL;\
}

int append(node *tail,type val_argu) {
    node *temp_ptr;
    temp_ptr = (node *)malloc(sizeof(node));
    temp_ptr->val=val_argu;
    tail->prior->next=temp_ptr;
    temp_ptr->prior=tail->prior;
    temp_ptr->next=tail;
    tail->prior=temp_ptr;
    return 0;
}

int erase(node *ptr) {
    ptr->prior->next=ptr->next;
    ptr->next->prior=ptr->prior;
    free(ptr);
    return 0;
}

int display(node *head, node *tail) {
    node *ptr=head;
    while (ptr->next != tail) {
        ptr = ptr->next;
        printf(typef,ptr->val);
        putchar(' ');
    }
    printf("\n");
    return 0;
}

int listlen(node *head, node *tail) {
    node *ptr=head;
    int len=0;
    while (ptr->next != tail) {
        ptr = ptr->next;
        len ++;
    }
    return len;
}

#define clear(head,tail) \
{\
    node *ptr__=head->next,*temp__;\
    while (ptr__->next != tail) {\
        temp__ = ptr__;\
        ptr__ = ptr__->next;\
        free(temp__);\
    }\
    head -> next = tail;\
}

int main(void) {
    node *head,*tail;//(head,tail)
    int i,l,t;
    ini(head,tail);
    //input
    scanf("%d",&l);
    for (i=0;i<l;i++) {
        scanf(typef,&t);
        append(tail,t);
    }
    display(head,tail);
    printf("%d\n",listlen(head,tail));
    clear(head,tail);
    display(head,tail);
    printf("%d\n",listlen(head,tail));
}

