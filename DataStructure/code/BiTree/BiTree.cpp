#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 1000

typedef struct BiTNode {
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode,*BiTree;


// 按先序遍历的扩展序列 建立二叉树
void buildBiTree(BiTNode*& tree, const char* input, int& index)
{
    char c = input[index++];
    if (c == '*')
        tree = NULL;
    else
    {
        if (!(tree = (BiTNode*)malloc(sizeof(BiTNode))))
        {
            printf("建树失败！\n");
            exit(1);
        }
        tree->data = c;
        buildBiTree(tree->lchild, input, index);
        buildBiTree(tree->rchild, input, index);
    }
}


// 先序遍历二叉树 递归
void Preorder(const BiTree T)
{
    if (T)
    {
        printf("%c ", T->data);// 访问根结点
        Preorder(T->lchild);// 遍历左子树
        Preorder(T->rchild);// 遍历右子树
    }
}

// 中序遍历二叉树 递归
void Inorder(const BiTree T)
{
    if (T)
    {
        Inorder(T->lchild);// 遍历左子树
        printf("%c ", T->data);// 访问根结点
        Inorder(T->rchild);// 遍历右子树
    }
}

// 后序遍历二叉树 递归
void Postorder(const BiTree T)
{
    if (T)
    {
        Postorder(T->lchild);// 遍历左子树
        Postorder(T->rchild);// 遍历右子树
        printf("%c ", T->data);// 访问根结点
    }
}

// 前序遍历二叉树 非递归
void Preorder_nonRecursive(const BiTree T)
{
    BiTNode* mStack[MAX_SIZE];//自定义栈
    int top = -1;//top指向栈顶元素,-1代表栈为空

    BiTNode* p = T;//工作指针p

    while (p || top != -1) 
    {
        while (p) //p指针一路向左
        {
            printf("%c ", p->data);//访问结点
            mStack[++top] = p;//入栈
            p = p->lchild;
        }

        //p向左走到头了，栈顶元素出栈
        p = mStack[top];
        --top;//出栈

        p = p->rchild;
    }
}

// 中序遍历二叉树 非递归
void Inorder_nonRecursive(const BiTree T)
{
    BiTNode* mStack[MAX_SIZE];//自定义栈
    int top = -1;//top指向栈顶元素,-1代表栈为空

    BiTNode* p = T;//工作指针p

    while (p || top != -1)
    {
        while (p) //p指针一路向左
        {
            
            mStack[++top] = p;//入栈
            p = p->lchild;
        }

        //p向左走到头了，栈顶元素出栈
        p = mStack[top];
        --top;//出栈
        printf("%c ", p->data);//访问结点

        p = p->rchild;
    }
}


// 后序遍历二叉树 非递归
void Postorder_nonRecursive(const BiTree T)
{
    BiTNode* mStack[MAX_SIZE];//自定义栈
    int top = -1;//top指向栈顶元素,-1代表栈为空

    BiTNode* p = T;//工作指针p
    BiTNode* r = NULL;//指针r记录上一个访问的节点，用于判断是否为当前节点的右孩子

    while (p || top != -1)
    {
        while (p) //p指针一路向左
        {
            mStack[++top] = p;//入栈
            p = p->lchild;
        }

        //p向左走到头了，访问栈顶元素
        p = mStack[top];

        //当前节点的右孩子已被访问过，或当前节点的右孩子为空，则访问
        if (p->rchild==NULL||r == p->rchild)
        {
            printf("%c ", p->data);//访问结点
            --top;//出栈
            r = p;
            p = NULL;
        }
        else//否则指向右孩子
        {
            p = p->rchild;
        }
      
    }
}

//层次遍历
void levelOrder(const BiTree T)
{
    if (!T)
    {
        return;
    }

    BiTNode* mqueue[MAX_SIZE];
    int top = 0, end = 0;//队头，队尾

    mqueue[end++] = T;//根节点入队

    while (top != end)
    {
        BiTNode* p = mqueue[top];
        ++top;//出队
        printf("%c ", p->data);//访问结点

        if (p->lchild)
        {
            mqueue[end++] = p->lchild;//左孩子入队
        }
        if (p->rchild)
        {
            mqueue[end++] = p->rchild;//右孩子入队
        }
    }
}

// 统计二叉树中结点的个数
int countNode(const BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    return 1 + countNode(T->lchild) + countNode(T->rchild);
}

//求二叉树的深度
int getDepth(const BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    int dl = getDepth(T->lchild);
    int dr = getDepth(T->rchild);
    return 1 + (dl > dr ? dl : dr);
}

void test1()
{
    char input[200] = "124*6***3*57**8**"; // 先序遍历的扩展序列
    printf("测试1:\n先序遍历的扩展序列为：124*6***3*57**8**\n");
     //      1
     //   2     3
     //4           5
     //   6      7   8  
     //                      
    int index = 0;
    BiTree root = NULL;
    buildBiTree(root,input, index);

    printf("先序遍历结果(递归):\t");
    Preorder(root);
    printf("\n");

    printf("中序遍历结果(递归):\t");
    Inorder(root);
    printf("\n");

    printf("后序遍历结果(递归):\t");
    Postorder(root);
    printf("\n");

    printf("先序遍历结果(非递归):\t");
    Preorder_nonRecursive(root);
    printf("\n");

    printf("中序遍历结果(非递归):\t");
    Inorder_nonRecursive(root);
    printf("\n");

    printf("后序遍历结果(非递归):\t");
    Postorder_nonRecursive(root);
    printf("\n");

    printf("层序遍历结果(非递归):\t");
    levelOrder(root);
    printf("\n");

    printf("二叉树中结点的个数:\t");
    printf("%d\n",countNode(root)); 

    printf("二叉树的深度:\t");
    printf("%d\n\n", getDepth(root));
}


void test2()
{
    char input[200]; // 先序遍历的扩展序列
    printf("测试2:\n");
    printf("请输入先序遍历的扩展序列：");
    scanf("%s", input);

    //输入示例:abd*fi****c*egjkmn****l***h**
    //        a
    //     b     c
    //  d           e
    //     f      g   h  
    //   i      j 
    //        k   l
    //     m
    //  n

    int index = 0;
    BiTree root = NULL;
    buildBiTree(root, input, index);

    printf("先序遍历结果(递归):\t");
    Preorder(root);
    printf("\n");

    printf("中序遍历结果(递归):\t");
    Inorder(root);
    printf("\n");

    printf("后序遍历结果(递归):\t");
    Postorder(root);
    printf("\n");

    printf("先序遍历结果(非递归):\t");
    Preorder_nonRecursive(root);
    printf("\n");

    printf("中序遍历结果(非递归):\t");
    Inorder_nonRecursive(root);
    printf("\n");

    printf("后序遍历结果(非递归):\t");
    Postorder_nonRecursive(root);
    printf("\n");

    printf("层序遍历结果(非递归):\t");
    levelOrder(root);
    printf("\n");

    printf("二叉树中结点的个数:\t");
    printf("%d\n", countNode(root));

    printf("二叉树的深度:\t");
    printf("%d\n", getDepth(root));
}


int main()
{
    test1();
    test2();
	return 0;
}