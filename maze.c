#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int dir; //the direction of the next step
} Step;

int board[10][10]= {\
    {1,1,1,1,1,1,1,1,1,1},\
    {1,0,0,1,1,0,0,1,0,1},\
    {1,0,0,1,0,0,0,1,0,1},\
    {1,0,0,0,0,1,1,0,0,1},\
    {1,0,1,1,1,0,0,0,0,1},\
    {1,0,0,0,1,0,0,0,0,1},\
    {1,0,1,0,0,0,1,0,0,1},\
    {1,0,1,1,1,0,1,1,0,1},\
    {1,1,0,0,0,0,0,0,0,1},\
    {1,1,1,1,1,1,1,1,1,1}};

Step steps[1024];
int top=-1; //out of the end


int maze(int in_i,int in_j, int out_i, int out_j) {
    int i=in_i, j=in_j,dire=0, acce; // direction , access
    Step temp_step;
    top=0;
    steps[top].x=in_i;
    steps[top].y=in_j;
    steps[top].dir=0;
    board[in_i][in_j]=-1;
    while(steps[top].x != in_i || steps[top].y != in_j) { //栈顶位置不是出口
       acce=0;
       while (dire<4 && acce==0) {
                dire++;
                switch (dire) {
                    case 1: i=steps[top].x-1;
                            j=steps[top].y;
                            break;
                    case 2: i=steps[top].x;
                            j=steps[top].y+1;
                            break;
                    case 3: i=steps[top].x+1;
                            j=steps[top].y;
                            break;
                    case 4: i=steps[top].x;
                            j=steps[top].y-1;
                            break;
                }
                if (board[i][j] == 0) {
                    acce=1;
                }
            }
            if (acce == 1) {
                steps[top].dir = dire;
                top++;
                steps[top].dir = 0;
                steps[top].x = i;
                steps[top].y = j;
                board[i][j]=-1;
            }
            else {
                if (top < 0) {
                    return -1;
                }
                else {
                 board[steps[top].x][steps[top].y] = 0;
                 top--;
                }
            }   //若栈空则找到全部解
    }
    return 0;
}

int main(void)
{
    int t;
    t=maze(1,1,8,8);
    printf("%d\n",t);
    return 0;
}
