#include <stdio.h>
#include <stdlib.h>

int board[64]={0};
//使用一维数组存储棋盘，下标i表示皇后的行号，元素a[i]表示皇后的列号
//下标从1开始，a[i] == 0表示未放置皇后
//a[i]只有一个值避免了行冲突，每行或每列有且只有一个皇后每个a[i]都应有一个非0值。
int index=8;
//皇后数

#define vacan -1000  //定义表示位置未被占用的值，该值很小防止使用0值让vaild函数误判

int valid(int i, int j) {
    int k;
    for (k=1;k<index;k++) {
        if ( board[k]==j || j-i == board[k]-k || i+j == k+board[k] ) {
            //列冲突j==j0，主对角线冲突j-i == j0-i00, 次对角线冲突 i+j == i0+j0
            return 0;
        }
    }
    return 1;
}

int queens(void) {
    int num=0; //记录解的个数
    int i=1,j=1,iter;   //记录当前行列号
    for (iter=0;iter<=index;board[iter]=vacan,iter++); //初始化棋盘
    while (i<=index) { //遍历行
        while (j<=index) {
            if (valid(i,j)) {
                board[i]=j; //放置皇后
                j=1;        //重置列号
                break;
            }
            else {
                j++;
            }
        }
        if (board[i] == vacan) {
            //如果当前行没有放置位置，说明上一行的放置有问题应进行回溯
            if (i==1) {
                break;   //如果回溯完第1行仍无解，说明已找到所有解
            }
            else {
                i--;     //回溯到上一行
                j=board[i]+1; //因为1至board[i]均已扫描过，从下一列开始继续扫描。
                board[i]=vacan;   //清除上一行的皇后
                continue;
            }
        }
        if (i==index) {   //如果已扫描到最后一行找到一个解，打印答案
            printf("answer:%d\n",++num);
            for(iter=1;iter<=index;iter++) {
                printf("[%d,%d]\n",iter,board[iter]);
            }
            printf("\n");
            j=board[i]+1; //从最后一行下一列继续扫描
            board[i]=vacan;
            continue;
        }
        i++;
    }
    printf("num:%d\n",num);
    return num;
}

int main(void)
{
    scanf("%d",&index);
    queens();
    return 0;
}
