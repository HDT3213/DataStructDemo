#include <stdio.h>
#include<stdlib.h>

#define M 16

void getGraph(int matrix[M][M], int *m) {
  int i,j;
  scanf("%d", m);
  for (i = 0; i < *m; i++) {
    for (j = 0; j < *m; j++) {
        scanf("%d",&matrix[i][j]);
    }
  }
}

void putGraph(int matrix[M][M], int m) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++) {
      printf("%d ", matrix[i][j]);
    }
    putchar('\n');
  }
}

int visited[M];
void DFS(int matrix[M][M], int m) {
  int i;
  for (i = 0; i < M; i++) {
    visited[i] = 0;
  }
  for (i = 0; i < m; i++) {
    if (!visited[i]) {
      doDFS(matrix,m,i);
    }
  }
}

void doDFS(int matrix[M][M], int m, int v) {
  int i;
  visited[v] = 1;
  printf("%d\n",v + 1);
  for (i = 0; i < m; i++) {
    if (matrix[v][i]) {
      if (!visited[i]) {
        doDFS(matrix, m, i);
      }
    }
  }
}

void BFS(int matrix[M][M], int m) {
  int i, j, v = 0;
  int front = 0, back = 0,que[M * M] = {0};
  for (i = 0; i < M; i++) {
    visited[i] = 0;
  }
  printf("%d ", v + 1);
    visited[0] = 1;
    que[back++] = v;
    while (front < back) {
        i = que[front++];
        for (j = 0; j < m; j++) {
            if(matrix[i][j] && !visited[j]) {
                printf("%d ", j + 1);
                visited[j] = 1;
                que[back++] = j;
            }
        }
    }
    printf("\n");
}


int main() {
  int i, j, m , matrix[M][M] = {0};
  //freopen("test.in","r",stdin);
  freopen("test.in", "r", stdin);
  getGraph(matrix, &m);
  //DFS(matrix, m);
  //putchar('\n');
  BFS(matrix, m);
}
