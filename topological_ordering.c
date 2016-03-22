#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define M 10001

int n, m, button[M][M], i, j;

int sorted, indegree[M]; //sorted 已排序的顶点个数



int main()

{

    int a, b, k;

    scanf("%d %d",&n, &m);

    //建立邻接矩阵，和入度表
    for (i=1; i<=m; i++)

    {

        scanf("%d %d",&a, &b);

        button[a][b]=1;

        indegree[b]++;

    }

    for (i=1; i<=n; i++) {

        for (j=1; j<=n; j++) {

            if (indegree[j] == 0) { //遍历所有入度为0的顶点

               indegree[j] = -1;

               sorted++;

               for (k=1; k<=n; k++) {

                   if (button[j][k]==1) { //遍历所有入度为1的顶点

                      button[j][k]=0;     //删除边e

                      indegree[k]--;       //更新入度表

                   }

               }

               break;

            }

        }
    }
    printf("%d\n", sorted);
    return 0;

}
