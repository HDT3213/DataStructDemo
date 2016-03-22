#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 10000
//创建map二维数组储存图表，low数组记录每2个点间最小权值，visited数组标记某点是否已访问

int map[N][N],low[N],visited[N];
int m, n;
int prim()
{
    int i, j, pos, min, result=0;
    memset(visited,0,sizeof(visited));
    visited[0] = 1;
    pos = 0;
    //init low
    for(i = 0; i < n; i++) {
       if(i != pos) {
          low[i] = map[pos][i];
       }
    }
    //get mini
    for(i = 0; i < n - 1; i++) //n -1 ?
    {
        min = INT_MAX;
        for(j = 0; j < n; j++) ｛
            if(visited[j] == 0 && min > low[j] ) {
             min=low[j];
             pos=j;
            }
        ｝
        result += min;
        visited[pos] = 1;
        //update
        for(j = 0; j < n; j++) {
            if(visited[j]==0 && low[j] > map[pos][j]) {
                low[j] = map[pos][j];
            }
        }
    }
    return result;
}

int head[N],tail[N],weight[N];
int parent[N],sorted[N];

int cmp(const void *ip, const void *jp)
{
    int i = *(int *)ip, j = *(int *)jp;
    return weight[i] - weight[j];
}

int find(int x) //find the root
{
    if (parent[x] == x) {
        return x;
    }
    else {
        parent[x] = find(parent[x]);
        return parent[x];
    }
}

//m vertex, n edge
int kruskal()
{
    int count = 0, x, y, i, e, ans = 0;
    //init
    for(i = 0; i < n; i++) {
        parent[i] = i;
    }
    for(i=0; i < n; i++) {
        sorted[i] = i;
    }
    //sort(r,r+m,cmp);
    qsort(sorted, m, sizeof(int), cmp);
    for(i = 0; i < m; i++)
    {
        e = sorted[i];
        x = find( head[e] );
        y = find( tail[e] );
        if(x != y) {
            ans += weight[e];
            parent[x] = y;
            count++;
        }
    }
    if (count < n - 1) { //无法连通
        return -1;
    }
    return ans;
}

int main()
{
    int i,v,j,ans;
    scanf("%d",&n);
    memset(map,INT_MAX,sizeof(map));
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
           scanf("%d",&v);
           map[i][j] = v;
           map[j][i] = v;
        }
    }
    ans = prim();
    printf("%d\n",ans);
    return 0;
}
