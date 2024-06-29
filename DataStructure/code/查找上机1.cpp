//����ʦ����Ŀ��û��Ҫ��ʵ�� ɾ�� ����������������ϰһ�£����԰�ɾ������Ҳʵ����
#include<stdio.h>
#include<stdlib.h>

typedef struct BiTNode // ���ṹ
{
    int data;
    struct BiTNode* lchild, * rchild;
    // ���Һ���ָ��
} BiTNode, * BiTree;


int SearchBST(BiTree T, int key, BiTree f, BiTree& p)
{
	if (!T)	//  ���Ҳ��ɹ�
	{
		p = f;
		return 0;
	}
	else if (key == T->data) // ���ҳɹ�
	{
		p = T;
		return 1;
	}
	else if (key < T->data)
		return SearchBST(T->lchild, key, T, p);  // ���������м�����
	else
		return SearchBST(T->rchild, key, T, p);  // ���������м�����
}


int InsertBST(BiTree& T, int key) 
{
	BiTree p;
	if (!SearchBST(T, key, NULL, p)) 
	{
		// Ϊ�½�����ռ�
		BiTree s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		
		if (!p)T = s;// ���� s Ϊ�µĸ����
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

// ����������ǵݹ飩
void inorderTraversal(const BiTree T) 
{
	BiTree myStack[1000];
	int top = -1;

	BiTree p = T;// ����ָ�뿪ʼָ������

	while (p || top != -1) 
	{
		while (p)
		{
			myStack[++top] = p;// ��ջ
			p = p->lchild;
		}
		p = myStack[top--];// ��ջ
		printf("%d ", p->data);

		p = p->rchild;
	}
}

// �Ӷ�����������ɾ�����p�����ؽ�������������
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
	else // ��������������
	{
		q = p; BiTree s = p->lchild;
		//��p��ǰ��
		while (s->rchild)//ת��Ȼ��һ·����
		{
			q = s;// q ʼ��ָ�� s �ĸ���
			s = s->rchild;
		}
		// �ñ�ɾ���ǰ����ֵȡ����ɾ����ֵ
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
	printf("����һ������ؼ��֣�����������:\n");
	printf("����ؼ��ָ���: ");
	int num = 0;
	scanf("%d", &num);

	// ����
	for (int i = 0; i < num; i++)
	{
		printf("�����%d���ؼ���: ", i + 1);
		int a = 0;
		scanf("%d", &a);
		InsertBST(T, a);

	}

	// ����������
	printf("��ǰ����������: ");
	inorderTraversal(T);
	printf("\n");


	BiTree p = NULL;
	int find;
	printf("����������ҵĹؼ��֣�");
	scanf("%d", &find);
	if (SearchBST(T, find, NULL, p))
	{
		printf("����%d\n", find);
	}
	else
	{
		printf("������%d\n", find);
		InsertBST(T, find);

		printf("��ǰ����������: ");
		inorderTraversal(T);
		printf("\n");
	}


	printf("�������ɾ���Ĺؼ��֣�");
	scanf("%d", &find);
	if (!DeleteBST(T, find))
	{
		printf("������ %d ,ɾ��ʧ�ܣ�\n", find);
	}
	else
	{
		
		printf("ɾ���ɹ���");
		printf("��ǰ����������: ");
		inorderTraversal(T);
		printf("\n");
	}

	return 0;
}
