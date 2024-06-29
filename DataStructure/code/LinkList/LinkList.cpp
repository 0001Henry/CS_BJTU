#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
// 定义单链表的节点类型
typedef struct LNode
{
	int val;          // 值域
	struct LNode* next; // 指针域
} LNode, * LinkList;

void SelectSort(LinkList& L)
{
	if (L->next->next == NULL || L->next == NULL)
	{
		return;
	}
	LinkList p = L->next;// p以及p之后的为待排序序列
	while (p)
	{
		LinkList q = p, r = p;// 工作指针q用于遍历，r用于存关键字最小的节点
		while (q)// 在待排序序列中选择关键字最小的节点
		{
			if (q->val < r->val)
			{
				r = q;
			} 
			q = q->next;
		}
		if (p != r)
		{
			// 交换 p,r 节点
			int t = p->val;
			p->val = r->val;
			r->val = t;
		}
		p = p->next;
	}
}

//删除函数
void myDelete(LinkList& L, int mink, int maxk)
{
	LNode* p, *q;
	p = L;
	q = L;// 从第一个节点开始
	LNode* pre = L;     // pre 指向 p 的前一个节点
	while (p->next != NULL && p->next->val <= mink)
	{
		p = p->next;
	}
	if (p->next) {
		q = p->next;
		while (q!=NULL && q->val <= maxk)q = q->next;
		p->next = q;// 删除操作
	}
}

//根据数组创建带头节点head的单链表
LinkList createList(int n, int* a)
{
	LNode* head, * rear;
	//创建头指针
	head = (LNode*)malloc(sizeof(LNode));
	head->next = NULL;
	rear = head;

	for (int i = 0; i < n; i++)
	{
		LNode* p = (LNode*)malloc(sizeof(LNode));
		p->next = NULL;
		p->val = a[i];
		//尾插法
		rear->next = p;
		rear = p;
	}
	return head;
}


//遍历函数并打印输出
void printList(const LinkList L)
{
	LNode* p = L->next;
	while (p)
	{
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
	return;
}

int main()
{
	//测试样例
	int a[10] = { 6,7,10,1,2,3,4,5,8,9 };
	LinkList L = createList(10, a);
	printList(L);

	SelectSort(L);
	printList(L);

	myDelete(L, 4, 8);
	printList(L);




	return 0;
}



//
//
//
//
//#include<stdio.h>
//#include<stdlib.h>
//// 定义单链表的节点类型
//typedef struct LNode
//{
//	int val;          // 值域
//	struct LNode* next; // 指针域
//} LNode, * LinkList;
//
//
////删除函数
//void myDelete(LinkList& L, int mink, int maxk)
//{
//	LNode* p = L->next; // 从第一个节点开始
//	LNode* pre = L;     // pre 指向 p 的前一个节点
//
//	while (p)
//	{
//		if (p->val > mink && p->val < maxk)
//		{
//			pre->next = p->next; // 从链表中删除节点
//			free(p);             // 释放节点内存
//			p = pre->next;       // 移动 p 到下一个节点
//		}
//		else
//		{
//			pre = p;     // 更新 pre 和 p
//			p = p->next;
//		}
//	}
//}
//
////根据数组创建带头节点head的单链表
//LinkList createList(int n, int* a)
//{
//	LNode* head, * rear;
//	//创建头指针
//	head = (LNode*)malloc(sizeof(LNode));
//	head->next = NULL;
//	rear = head;
//
//	for (int i = 0; i < n; i++)
//	{
//		LNode* p = (LNode*)malloc(sizeof(LNode));
//		p->next = NULL;
//		p->val = a[i];
//		//尾插法
//		rear->next = p;
//		rear = p;
//	}
//	return head;
//}
//
//
////遍历函数并打印输出
//void printList(const LinkList L)
//{
//	LNode* p = L->next;
//	while (p)
//	{
//		printf("%d ", p->val);
//		p = p->next;
//	}
//	printf("\n");
//	return;
//}
//
//int main()
//{
//	//测试样例
//	int a[10] = { 3,2,1,4,6,4,10,11,9,8 };
//	LinkList L = createList(10, a);
//	printList(L);
//
//	myDelete(L, 3, 10);
//	printList(L);
//
//	return 0;
//}













