#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    int data;
    struct BTreeNode* left;
    struct BTreeNode* right;
}BTreeNode;

#define M 32
char coding[M][M];

//根据数组 a 中 n 个权值建立一棵哈夫曼树，返回树根指针
BTreeNode* CreateHuffman(int a[], int n)
{
    int i, j;
    BTreeNode **b, *q;
    b = malloc(n*sizeof(BTreeNode));
    for (i = 0; i < n; i++) //初始化b指针数组，使每个指针元素指向a数组中对应的元素结点
    {
        b[i] = malloc(sizeof(BTreeNode));
        b[i]->data  = a[i];
        b[i]->left  = NULL;
        b[i]->right = NULL;
    }
    for (i = 1; i < n; i++)//进行 n-1 次循环建立哈夫曼树
    {
        //k1表示森林中具有最小权值的树根结点的下标，k2为次最小的下标
        int k1 = -1, k2;
        for (j = 0; j < n; j++)//让k1初始指向森林中第一棵树，k2指向第二棵
        {
            if (b[j] != NULL && k1 == -1)
            {
                k1 = j;
                continue;
            }
            if (b[j] != NULL)
            {
                k2 = j;
                break;
            }
        }
        for (j = k2; j < n; j++)//从当前森林中求出最小权值树和次最小
        {
            if (b[j] != NULL)
            {
                if (b[j]->data < b[k1]->data)
                {
                    k2 = k1;
                    k1 = j;
                }
                else if (b[j]->data < b[k2]->data)
                    k2 = j;
            }
        }
        //由最小权值树和次最小权值树建立一棵新树，q指向树根结点
        q = malloc(sizeof(BTreeNode));
        q->data = b[k1]->data + b[k2]->data;
        q->left = b[k1];
        q->right = b[k2];

        b[k1] = q;//将指向新树的指针赋给b指针数组中k1位置
        b[k2] = NULL;//k2位置为空
    }
    free(b); //删除动态建立的数组b
    return q; //返回整个哈夫曼树的树根指针
}

//3、求哈夫曼树的带权路径长度
double WeightPathLength(BTreeNode* FBT, int len)//len初始为0
{
    if (FBT == NULL) //空树返回0
        return 0;
    else
    {
        if (FBT->left == NULL && FBT->right == NULL)//访问到叶子结点
            return FBT->data * len;
        else //访问到非叶子结点，进行递归调用，返回左右子树的带权路径长度之和，len递增
            return WeightPathLength(FBT->left,len+1)+WeightPathLength(FBT->right,len+1);
    }
}

static int index = 0;
char *c;
//4、哈夫曼编码（可以根据哈夫曼树带权路径长度的算法基础上进行修改）   
void HuffManCoding(FILE *fp, BTreeNode* FBT, int len)//len初始值为0
{
    static int a[10];   //定义静态数组a，保存每个叶子的编码，数组长度至少是树深度减一
    if (FBT != NULL)    //访问到叶子结点时输出其保存在数组a中的0和1序列编码
    {
        if (FBT->left == NULL && FBT->right == NULL)
        {
            int i;
            fprintf(fp,"%c %d:",c[index++],FBT->data);
            for (i = 0; i < len; i++)
                fprintf(fp,"%d", a[i]);
           fprintf(fp,"\n");
        }
        else//访问到非叶子结点时分别向左右子树递归调用，并把分支上的0、1编码保存到数组a
        {   //的对应元素中，向下深入一层时len值增1
            a[len] = 0;
            HuffManCoding(fp, FBT->left, len + 1);
            a[len] = 1;
            HuffManCoding(fp, FBT->right, len + 1);
        }
    }
}

void append(char *str, char ch) {
    int i;
    for (i = 0; str[i];i++);
    str[i] = ch;
    str[i+1] = '\0';
}

int main()
{
    int i, j, k, n, t;
    int* arr;
    char ch, in[M] = {'\0'}, code[M*M] = {'\0'}, out[M] = {'\0'};
    BTreeNode* fbt;
    FILE *fp;

    //Input
    freopen("test.in","r",stdin);
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));
    c   = (char *)malloc(n * sizeof(char));
    arr[0] = 186;
    c[0] = ' ';
    for (i = 1; i < n; i++) {
        getchar();
        scanf("%c %d",&c[i],&arr[i]);
    }

    //huffman coding
    fbt = CreateHuffman(arr, n);
    fp = fopen("code.txt","w");
    HuffManCoding(fp, fbt, 0);
    fflush(fp);

    //Encoding
    fp = fopen("code.txt","r");
    for (i = 0; i < n; i++) {
       fgetc(fp);
       fscanf(fp,"%c %d:%s", &t, &ch, &coding[i]);
    }
    fp = fopen("src.in","r");
    fscanf(fp, "%s", in);
    for (i = 0; in[i]; i++) {
        for (j = 0; j < n; j++) {
            if (c[j] == in[i]) {
                strcat(code,coding[j]);
            }
        }
    }
    printf("%s\n",code);

    //Decoding
    for(i = 0; code[i]; i++) {
        for (j = 0; j < n; j++) {
            t = 1;
            for (k = 0; coding[j][k]; k++) {
                if (code[i + k] != coding[j][k]) {
                    t = 0;
                    break;
                }
            }
            if (t == 1) {
                append(out,c[j]);
                i = i + k - 1;
                break;
            }
        }
    }
    printf("%s\n",out);
    return 0;
}
