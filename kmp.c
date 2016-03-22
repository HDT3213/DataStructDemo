#include <stdio.h>
#include <string.h>

int substr(char *test, char *sub) {
    int i=0,j=0;
    while ( test[i]&&sub[j]) {
        if (test[i] == sub[j]) {
            i++;
            j++;
        }
        else {
            i = i-j + 1;    //i back to the start of the current sub
            j=0;
        }
    }
    return i-j; //i == the index of the end of sub, j == the length of the sub
}

int next[1024]={0};

void getnext(char *sub) {
    int i=1,j=0;
    next[0]=0;
    next[1]=0;
    while (sub[i]) {
        if (j==0 || sub[i]==sub[j]) {
            i++;
            j++;
            next[i]=j;
        }
        else {
            j=next[j];
        }
    }
}

int substr_kmp(char *test, char *sub) {
    int i=0,j=1;
    while ( test[i]&&sub[j]) {
        if (test[i] == sub[j-1] || j==0) {
            i++;
            j++;
        }
        else {
           j=next[j];
        }
    }
    if (sub[j]) {
       return -1;
    }
    else {
        return i-j+1;
    }
}

int main(void)
{
    getnext("bca");
    printf("%d\n",substr_kmp("abcabaabc","bcd"));
    return 0;
}
