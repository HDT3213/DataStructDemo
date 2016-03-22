#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define M 100001

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

void getOList(Vertex  *vertexs, int m, int n) {
	int i, j, k, weight;
	Edge *edge;
	for (i = 0; i < m; i++) {
	    vertexs[i].firstin  = NULL;
	    vertexs[i].firstout = NULL;
	}
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &i, &j, &weight);
        //对齐下标
        i--;
        j--;
        //append
        edge = (Edge *)malloc(sizeof(Edge));
        edge->headvex = i;
        edge->tailvex = j;
        edge->val = weight;
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
        ptr = ptr->outlink;
    }
    return -1;
}

int visited[M], low[M];
int prim(Vertex  *vertexs, int m, int n)
{
    int i, j, t, pos, min, result = 0;
    memset(visited,0,sizeof(visited));
    visited[0] = 1;
    pos = 0;
    //init low
    for(i = 0; i < n; i++) {
       if(i != pos) {
          low[i] = getEdge(vertexs,pos,i);
       }
    }
    //get mini
    for(i = 0; i < n - 1; i++) //n -1 ?
    {
        min = INT_MAX;
        for(j = 0; j < n; j++)
            if(visited[j] == 0 && min > low[j] ) {
             min=low[j];
             pos=j;
         }
         result += min;
         visited[pos] = 1;
        //update
        for(j = 0; j < n; j++) {
            t = getEdge(vertexs,pos,j);
            if(visited[j]==0 && low[j] > t) {
                low[j] = t;
            }
        }
    }
    return result;
}


//m vertexs, n edges
int main(void)
{
    int i, m, n;
    long long int ans;
    Vertex vertexs[M];
    scanf("%d %d", &m, &n);
    getOList(vertexs, m, n);
    ans = prim(vertexs, m, n);
    printf("%ld\n",ans);
    return 0;
}
