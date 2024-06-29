#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//孩子兄弟链表表示法
typedef struct CSNode 
{
    char data;
    struct CSNode* firstchild, * nextsibling;
} CSNode, * CSTree;


//创建空节点
CSNode* createCSNode(char ch)
{
    CSNode* p = (CSNode*)malloc(sizeof(CSNode));
    if (!p)
    {
        exit(0);
    }
    p->data = ch;
    p->firstchild = NULL;
    p->nextsibling = NULL;
    return p;
}


//建树1：自上而下输入树中每条边（例如#A,AB,AC,BD,##）
void buildCSTree_v1(CSTree &T,char *str) 
{
    //删掉字符串中的逗号','
    char input[1000];
    int idx = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ',')input[idx++] = str[i];
    }
    input[idx] = '\0';

    int i = 0;//字符串下标索引
    CSNode* map[1000];//哈希表：节点地址到data的映射
    memset(map, 0, sizeof(map));

    while (input[i + 1] != '#')
    {
        if (i == 0)//如果是头节点
        {
            T = createCSNode(input[i + 1]);
            map[input[i + 1]] = T;
        }
        else
        {
            char ch1 = input[i];//当前父节点
            char ch2 = input[i + 1];//当前孩子

            //创建新节点
            CSNode* newNode = createCSNode(ch2);
            map[ch2] = newNode;

            //取当前父节点的地址
            CSTree currentParent = map[ch1];
            if (!currentParent->firstchild) //没有孩子,则加入孩子
            {
                currentParent->firstchild = newNode;
            }
            else //有孩子，则加入兄弟
            {
                
                CSTree pHead = currentParent->firstchild;
                while (pHead->nextsibling)
                {
                    pHead = pHead->nextsibling;
                }
                pHead->nextsibling = newNode;
            }
        }
        i += 2;
    }

}

//建树2：按树中由根至叶子结点层次遍历顺序，输入结点序列及每个结点的度
void buildCSTree_v2(CSTree& T,const char* input)
{
    int len = strlen(input);
    T = createCSNode(input[0]);//创建头节点

    CSNode** parentQueue = (CSNode**)malloc((len + 1) * sizeof(CSNode*));//创建队列，用于存父节点地址
    int top = 0, end = 0;//队头，队尾
    parentQueue[end++] = T;//头节点入队    

    int index = 0;//字符串下标索引
    while (top != end)
    {
        CSTree currentParent = parentQueue[top];//取当前父节点的地址
        top++;//出队

        int currentDegree = input[index + 1]-'0';//当前父节点的度

        for (int i = 0; i < currentDegree; i++)
        {
            CSNode* newNode = createCSNode(input[index + i * 2]);
            parentQueue[end++] = newNode;

            if (NULL == currentParent->firstchild)//没有孩子,则加入孩子
            {
                currentParent->firstchild = newNode;
            }
            else //有孩子，则加入兄弟
            {
                CSTree pHead = currentParent->firstchild;
                while (pHead->nextsibling)
                {
                    pHead = pHead->nextsibling;
                }
                pHead->nextsibling = newNode;
            }
        }    
        index += 2;
    }
    
}

//求深度
int TreeDepth(CSTree T)
{
    if (!T)  return 0;
    else
    {
        int h1 = TreeDepth(T->firstchild);
        int h2 = TreeDepth(T->nextsibling);
        return(((h1 + 1) > h2) ? (h1 + 1) : h2);
    }
}

void test1()
{

    CSTree root = NULL;
    char input[1000]; // 输入字符串
    printf("请输入树的边（例如#A,AB,AC,BD,##）：");
    scanf("%s", input);
    //样例：#A,AB,AC,BD,BE,CF,DG,DH,EI,IJ,##
    /*
           A
      B            C
   D      E       F
 G  H       I
          J
    */

    buildCSTree_v1(root, input); // 构建树
    int depth = TreeDepth(root); // 计算树的深度
    printf("test1:树的深度为：%d\n", depth);

}

void test2() 
{
    CSTree root = NULL;
    char input[1000]; // 输入字符串
    printf("请从左至右输入结点序列及每个结点的度（例如A2B2C1D0E0F0）：");
    scanf("%s", input);

    //样例：A2B2C1D2E1F0G0H0I1J0
    /*
           A
      B            C
   D      E       F
 G  H       I
          J
    */
    buildCSTree_v2(root, input); // 构建树
    int depth = TreeDepth(root); // 计算树的深度
    printf("test2:树的深度为：%d\n", depth);

}

int main() {

    test1();

    test2();

    return 0;
}