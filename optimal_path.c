#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define M 100
#define N 100

int matrix[N][M];      //邻接矩阵
int n;                 //顶点数
int e;                 //边数

int visited[M];
void DijkstraPath(int *dist, int *path, int v0)   //v0表示源顶点
{
    int i, j, k, t;
    int min, u;
    //init
    for(i = 0; i < n; i++)  {
        if(matrix[v0][i]>0 && i != v0) {
            dist[i] = matrix[v0][i];
            path[i] = v0;     //path记录最短路径上从v0到i的前一个顶点
        }
        else {
            dist[i] = INT_MAX;    //若i不与v0直接相邻，则权值置为无穷大
            path[i] = -1;
        }
        visited[i] = 0;
        path[v0] = v0;
        dist[v0] = 0;
    }
    visited[v0] = 1;
    for(i = 1; i < n; i++)     //循环扩展n-1次
    {
        min = INT_MAX;
        for(j = 0; j < n; j++)    //寻找未被扩展的权值最小的顶点
        {
            if( !visited[j] && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }
        visited[u] = 1;
        for(k = 0; k < n; k++)   {
             //更新dist数组的值和路径的值
            t = min + matrix[u][k];
            if( !visited[k] && matrix[u][k] > 0 && t < dist[k])  {
                dist[k] = t;
                path[k] = u;
            }
        }
    }
}

void showPath(int *path,int v,int v0)   //打印最短路径上的各个顶点
{
    int s[M], top = 0;
    int u = v;
    while(v != v0) {
        s[top++] = v; //s.push(v);
        v = path[v];
    }
    s[top++] = v;//s.push(v);
    while(top > 0) {
        printf("%d ", s[--top]);
    }
}

int main(int argc, char *argv[])
{
    int i,j;
    int s,t,w;      //表示存在一条边s->t,权值为w
    int v0;
    int *dist=(int *)malloc(sizeof(int)*n);
    int *path=(int *)malloc(sizeof(int)*n);
    scanf("%d %d", &n, &e);
    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            matrix[i][j]=0;
        }
    }
    for(i=0;i<e;i++) {
        scanf("%d %d %d", &s, &t, &w);
        matrix[s][t]=w;
    }
    scanf("%d", &v0);        //输入源顶点
    DijkstraPath(dist,path,v0);
    for(i = 0; i < n; i++) {
        if(i!=v0) {
            showPath(path,i,v0);
            printf("%d\n",dist[i]);
        }
    }
    return 0;
}
