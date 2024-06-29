//致老师：题目中没有要求实现 删除 操作，但是我想练习一下，所以把删除操作也实现了
#include<stdio.h>
#include<stdlib.h>

typedef struct BiTNode // 结点结构
{
    int data;
    struct BiTNode* lchild, * rchild;
    // 左右孩子指针
} BiTNode, * BiTree;


int SearchBST(BiTree T, int key, BiTree f, BiTree& p)
{
	if (!T)	//  查找不成功
	{
		p = f;
		return 0;
	}
	else if (key == T->data) // 查找成功
	{
		p = T;
		return 1;
	}
	else if (key < T->data)
		return SearchBST(T->lchild, key, T, p);  // 在左子树中继续找
	else
		return SearchBST(T->rchild, key, T, p);  // 在右子树中继续找
}


int InsertBST(BiTree& T, int key) 
{
	BiTree p;
	if (!SearchBST(T, key, NULL, p)) 
	{
		// 为新结点分配空间
		BiTree s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		
		if (!p)T = s;// 插入 s 为新的根结点
		else if (key < p->data)
		{
			p->lchild = s;
		}
		else
		{
			p->rchild = s;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

// 中序遍历（非递归）
void inorderTraversal(const BiTree T) 
{
	BiTree myStack[1000];
	int top = -1;

	BiTree p = T;// 工作指针开始指向根结点

	while (p || top != -1) 
	{
		while (p)
		{
			myStack[++top] = p;// 入栈
			p = p->lchild;
		}
		p = myStack[top--];// 出栈
		printf("%d ", p->data);

		p = p->rchild;
	}
}

// 从二叉排序树中删除结点p，并重接它的左右子树
int Delete(BiTree& p)
{
	BiTree q;
	if (p->lchild == NULL)
	{
		q = p; p = p->rchild; free(q);
	}
	else if (p->rchild == NULL)
	{
		q = p; p = p->lchild; free(q);
	}
	else // 左右子树均不空
	{
		q = p; BiTree s = p->lchild;
		//找p的前驱
		while (s->rchild)//转左，然后一路向右
		{
			q = s;// q 始终指向 s 的父亲
			s = s->rchild;
		}
		// 用被删结点前驱的值取代被删结点的值
		p->data = s->data;
		if (q == p)
		{
			q->lchild = s->lchild;
		}
		else
		{
			q->rchild = s->lchild;
		}
	}
	return 1;
}

int DeleteBST(BiTree& T, int key)
{
	if (!T)
	{
		return 0;
	}
	else
	{
		if (key == T->data)
		{
			return Delete(T);
		}
		else if (key < T->data)
		{
			DeleteBST(T->lchild, key);
		}
		else
		{
			DeleteBST(T->rchild, key);
		}
	}
}
int main()
{
	BiTree T = NULL;
	printf("输入一组无序关键字（整数）序列:\n");
	printf("输入关键字个数: ");
	int num = 0;
	scanf("%d", &num);

	// 建树
	for (int i = 0; i < num; i++)
	{
		printf("输入第%d个关键字: ", i + 1);
		int a = 0;
		scanf("%d", &a);
		InsertBST(T, a);

	}

	// 中序遍历输出
	printf("当前中序遍历输出: ");
	inorderTraversal(T);
	printf("\n");


	BiTree p = NULL;
	int find;
	printf("请输入待查找的关键字：");
	scanf("%d", &find);
	if (SearchBST(T, find, NULL, p))
	{
		printf("存在%d\n", find);
	}
	else
	{
		printf("不存在%d\n", find);
		InsertBST(T, find);

		printf("当前中序遍历输出: ");
		inorderTraversal(T);
		printf("\n");
	}


	printf("请输入待删除的关键字：");
	scanf("%d", &find);
	if (!DeleteBST(T, find))
	{
		printf("不存在 %d ,删除失败！\n", find);
	}
	else
	{
		
		printf("删除成功！");
		printf("当前中序遍历输出: ");
		inorderTraversal(T);
		printf("\n");
	}

	return 0;
}
