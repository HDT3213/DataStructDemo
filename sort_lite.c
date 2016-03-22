#include<stdio.h>
#include<stdlib.h>

#define out(_a,_m) \
for (i=0;i<_m;i++) {\
printf("%d ",_a[i]);}printf("\n");

//#define syn
int *b_sort(int *a, int m) {
  int i, j, t;
  for (j = 0; j < m; j++) {
    for (i = 0; i < m - j - 1; i++) {
      if (a[i] > a[i + 1]) {
        t = a[i];
        a[i] = a[i + 1];
        a[i + 1] = t;
      }
    }
  }
  return a;
}

int *i_sort(int *a, int m) {
  int i, j, t;
#ifdef syn
  scanf("%d", a);
#endif
  for (i = 1; i < m; i++) {
#ifdef syn
    scanf("%d", &t);
#else
    t = a[i];
#endif 

    for (j = i - 1; a[j] > t && j >= 0; j--) {
      a[j + 1] = a[j];// out(a,m);
    }

    if (j != i - 1) {
      a[j + 1] = t;
    }
#ifdef syn
    else {
      a[i] = t;
    }
#endif 
  }
  return a;
}

int *s_sort(int *a, int m) {
  int i, j, p, t;
  for (i = 0; i < m - 1; i++) {
    p = i;
    for (j = i + 1; j < m; j++) {
      if (a[j] < a[p]) {
        p = j;
      }
    }
    if (p != i) {
      t = a[i];
      a[i] = a[p];
      a[p] = t;
    }
    //printf("i:%d ", a[i]);
    out(a, m);
  }
  return a;
}
int tell(const void *a,void *b){
	int x,y;
	x=*(int *)a;
	y=*(int *)b;
	return x-y;
}

int main() {
  int i, m, a[256] = { 0 };
  int (*tp)(const void *a,void *b);
  tp=tell;
  scanf("%d", &m);
#ifndef syn
  for (i = 0; i < m; i++) {
    scanf("%d", &a[i]);
  }
#endif
i_sort(a,m);
//  qsort (a, m,sizeof(int ),tp);
  out(a, m);
  return 0;
}
