#include <stdio.h>
#include <stdlib.h>

#define M 32

int strLength(char *str) {
    int i;
    for (i = 0;str[i];i++);
    return i;
}

void strAssign(char *dest, const char * src) {
    int i;
    for (i = 0;src[i];i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

void strConcact(char *dest, const char *src) {
    int i,j;
    for (i = 0; dest[i];i++);
    for (j = 0;src[j];j++) {
        dest[i++] = src[j];
    }
    dest[i] = '\0';
}

char *subStr(const char *src, int index, int len) {
    int i;
    char *dest;
    dest = (char *)malloc(M * sizeof(char));
    for (i = 0;i < len; i++) {
        dest[i] = src[index + i];
    }
    dest[i] = '\0';
    return dest;
}

int strCmp(const char *strA,const char *strB) {
    int i;
    if (strA[0] != strB[0]) {
        return strA[i] - strB[i];
    }
    for (i = 1;(strA[i] || strA[i-1]) && (strB[i] || strB[i-1]); i++) {
        if (strA[i] != strB[i]) {
            return strA[i] - strB[i];
        }
    }
}

//Kmp


int strIndex(const char *test, const char *sub) {
    int i, j, t;
    for (i = 0; test[i]; i++) {
        t = 1;
        for (j = 0;sub[j]; j++) {
            if (test[i+j] != sub[j]) {
              t = 0;
              break;
            }
        }
        if (t) {
            return i;
        }
    }
    return -1;
}

void strInsert(char *dest,int index,const char *sub) {
    int i;
    char *temp;
    temp = (char *)malloc(M * sizeof(char));
    strAssign(temp,dest + index);
    for (i = 0; sub[i]; i++) {
        dest[index + i] = sub[i];
    }
    dest[index + i] = '\0';
    strConcact(dest,temp);
}

void strReplace(char *test, int index, int len, const char *newStr) {
    int i;
    char temp[M] = {'\0'};
    for (i = 0; i < index; i++) {
        temp[i] = test[i];
    }
    temp[i] = '\0';
    strConcact(temp,newStr);
    strConcact(temp,test + index + len);
    strAssign(test,temp);
}

void strRep(char *test, char *oldStr, char *newStr) {
    int i, j, len;
    len = strLength(oldStr);
    for (i = 0; test[i]; i++) {
        j = strIndex(test+i,oldStr);
        if (j != -1) {
           strReplace(test,i + j,len,newStr);
           i = i + j + len;
        }
    }
}

int main(void)
{
    char strA[M], *strB = NULL;
    strAssign(strA,"Hell World");
    strInsert(strA,5,"oo");
    puts(strA);
    return 0;
}
