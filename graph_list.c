#include <stdio.h>
#include <stdlib.h>
#define M 16

struct Vertex;

typedef struct Edge {
  int headvex;
  int tailvex;
  struct Edge  *outlink;
  struct Edge  *inlink;
  int val;
} Edge;

typedef struct {
  int val;
  Edge *firstin;
  Edge *firstout;
} Vertex;

void appendInEdge(Vertex *vertex, Edge *edge) {
    Edge *ptr;
    edge->inlink = NULL;
    if(vertex->firstin) {
        ptr = vertex->firstin;
        while(ptr->inlink) {
            ptr = ptr->inlink;
        }
        ptr->inlink = edge;
    }
    else {
        vertex->firstin = edge;
    }
}

void appendOutEdge(Vertex *vertex, Edge *edge) {
    Edge *ptr;
    edge->outlink = NULL;
    if(vertex->firstout) {
        ptr = vertex->firstout;
        while(ptr->outlink) {
            ptr = ptr->outlink;
        }
        ptr->outlink = edge;
    }
    else {
        vertex->firstout = edge;
    }
}

void getOList(Vertex  *vertexs, int m) {
  int i, j, k, t;
  Edge *edge;
  for (i = 0; i < m; i++) {
      vertexs[i].firstin  = NULL;
      vertexs[i].firstout = NULL;
  }
  while (scanf("%d %d %d", &i, &j, &t) != EOF) {
        //append
        edge = (Edge *)malloc(sizeof(Edge));
        edge->headvex = i;
        edge->tailvex = j;
        edge->val = t;
        appendOutEdge(&vertexs[i], edge);
        appendInEdge (&vertexs[j], edge);
  }
}

int getEdge(Vertex *vertexs, int x, int y) {
    Edge *ptr;
    ptr = vertexs[x].firstout;
    while (ptr) {
        if (ptr->tailvex == y) {
            return ptr->val;
        }
    }
    return -1;
}

void putOList(Vertex *vertexs, int m) {
      int i, j;
      Edge *ptr;
      //in
      /*for (j = 0; j < m; j++) {
           ptr = vertexs[j].firstin;
           while (ptr) {
              i = ptr->headvex;
              printf("%d %d\n", i, j);
              ptr = ptr->inlink;
           }
      }
      printf("out:\n");*/
      //out
      for (i = 0; i < m; i++) {
           ptr = vertexs[i].firstout;
           while (ptr) {
              j = ptr->tailvex;
              printf("%d %d\n",i , j);
              ptr = ptr->outlink;
           }
      }
      printf("\n");
}

int visited[M];
void DFS(Vertex *vertexs, int m) {
  int i;
  for (i = 0; i < M; i++) {
    visited[i] = 0;
  }

  for (i = 0; i < m; i++) {
    if (!visited[i]) {
      doDFS(vertexs,m,i);
    }
  }
}

void doDFS(Vertex *vertexs, int m, int v) {
  int j;
  Edge *ptr = vertexs[v].firstout;
  visited[v] = 1;
  printf("%d\n",v + 1);
    while (ptr) {
        j = ptr->tailvex;
        if (!visited[j]) {
            doDFS(vertexs, m, j);
        }
        ptr = ptr->outlink;
    }
}

void BFS(Vertex *vertexs, int m) {
  int i, v = 0;
  int front = 0, back = 0,que[M * M] = {0};
  Edge *ptr;
  for (i = 0; i < M; i++) {
    visited[i] = 0;
  }
  printf("%d ", v + 1);
    visited[0] = 1;
    que[back++] = v;

  while (front < back) {
        i = que[front++];
        ptr = vertexs[i].firstout;
        while(ptr) {
            if (!visited[ptr->tailvex]) {
                printf("%d ", ptr->tailvex + 1);
                visited[ptr->tailvex] = 1;
                que[back++]  =  ptr->tailvex;
            }
            ptr = ptr->outlink;
        }
  }
  printf("\n");
}


int main() {
  int i, j, m;
  Vertex vertexs[M];
  freopen("test.in", "r", stdin);
  scanf("%d",&m);
  getOList(vertexs, m);
  //putOList(vertexs, m);
  //DFS(vertexs,m);
  //putchar('\n');
  BFS(vertexs ,m);
  return 0;
}
