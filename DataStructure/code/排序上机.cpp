#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10000
typedef struct
{
	int r[MAXSIZE + 1];
	int length;
}SqList;

void mSwap(SqList& L, int i,int j)
{
	int t = L.r[i];
	L.r[i] = L.r[j];
	L.r[j] = t;
}


// 折半插入排序
void BiInsertionSort(SqList& L)
{
	for (int i = 2; i <= L.length; i++)
	{
		L.r[0] = L.r[i];// 暂存
		// 二分查找第一个大于r[i]的关键字的位置
		// 注：这里我的二分查找的写法和PPT上的不太一样，找到的插入位置为high（不是 high + 1）
		int low = 0, high = i;
		while (low + 1 < high)
		{
			int m = (low + high) >> 1;
			if (L.r[0] < L.r[m])
			{
				high = m;
			}
			else
			{
				low = m;
			}
		}
		// 后移
		for (int j = i - 1; j >= high; j--)
		{
			L.r[j + 1] = L.r[j];
		}		
		// 插入
		L.r[high] = L.r[0];
	}
}

// 冒泡排序
void BubbleSort(SqList& L)
{
	int n = L.length;
	int flag = 1;
	for (int i = 1; i <= n&&flag == 1; i++)
	{
		flag = 0;
		for (int j = 1; j <= n - i; j++)
		{
			if (L.r[j] > L.r[j + 1])
			{
				mSwap(L, j, j+1);
				flag = 1;
			}
		}
	}
}

// 一趟快速排序
int Partition(SqList& L, int s, int t)
{
	int low = s, high = t;
	L.r[0] = L.r[low];
	int ptk = L.r[low];// 枢轴
	while (low < high)
	{
		while (low<high && L.r[high]>ptk)
		{
			--high;
		}
		L.r[low] = L.r[high];
		while (low < high && L.r[low] < ptk)
		{
			++low;
		}
		L.r[high] = L.r[low];
	}
	L.r[low] = L.r[0];
	return low;
}

// 快速排序
void QSort(SqList& L,int s,int t)
{
	if (s < t)
	{
		int pt = Partition(L, s, t);
		QSort(L, s, pt - 1);
		QSort(L, pt + 1, t);
	}
}
void QuickSort(SqList& L)
{
	QSort(L, 1, L.length);
}

// 简单选择排序
void SelectSort(SqList& L)
{
	int n = L.length;
	for (int i = 1; i < n; i++)// 选择第 i 小的记录
	{
		int res = i; // 在 r[i..n] 中选择关键字最小的记录
		for (int j = i; j <= n; j++)
		{
			if (L.r[j] < L.r[res])
			{
				res = j;
			}
		}
		if (i != res)mSwap(L, i, res);
	}
}


// 调整L.r[s]的关键字,使L.r[s..m]成为一个大顶堆
void HeapAdjust(SqList& L, int s, int m)
{
	int temp, j;
	temp = L.r[s];
	for (j = 2 * s; j <= m; j *= 2) // 沿关键字较大的孩子结点向下筛选 
	{
		if (j < m && L.r[j] < L.r[j + 1])
		{
			++j;
		}
		if (temp >= L.r[j])
		{
			break;
		}
		L.r[s] = L.r[j];
		s = j;
	}
	L.r[s] = temp; // 插入
}
// 堆排序
void HeapSort(SqList& L)
{
	// 把L中的r构建成一个大顶堆,（L.length / 2 为最后一个非叶子节点）
	for (int i = L.length / 2; i > 0; i--) 
	{
		HeapAdjust(L, i, L.length);
	}
	for (int i = L.length; i > 1; i--)
	{
		
		mSwap(L, 1, i);// 将堆顶和未经排序子序列的最后一个交换
		HeapAdjust(L, 1, i - 1);// 将L->r[1..i-1]重新调整为大顶堆
	}
}


// 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
void Merge(int SR[], int TR[], int i, int m, int n)
{
	int j = m + 1,k;
	for (k = i; i <= m && j <= n; k++)
	{
		if (SR[i] < SR[j])
		{
			TR[k] = SR[i++];
		}
		else
		{
			TR[k] = SR[j++];
		}
	}
	if (i <= m)
	{
		for (int l = 0; l <= m - i; l++)
		{
			TR[k + l] = SR[i + l];
		}
	}
	if (j <= n)
	{
		for (int l = 0; l <= n - j; l++)
		{
			TR[k + l] = SR[j + l];
		}
	}
}	
	
// 递归,将SR[s..t]归并排序为TR1[s..t] 
void MSort(int SR[], int TR1[], int s, int t)
{	
	int* TR2 = (int*)malloc(t*sizeof(int));
	if (s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		int m = (s + t) >> 1;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR1,s,m,t);
	}
}
// 归并排序
void MergeSort(SqList& L)
{
	MSort(L.r, L.r, 1, L.length);
}

void myPrint(SqList& L)
{
	int i;
	for (i = 1; i < L.length; i++)
	{
		printf("%d,", L.r[i]);
	}
	printf("%d\n", L.r[i]);
}

void init(SqList& L,int* input)
{
	L.length = 20;
	for (int i = 1; i <= 20; i++)
	{
		L.r[i] = input[i - 1];
	}
}

int main()
{
	int input[] = { 12,23,1,100,424,1123,2,56,87,6,45,879,99,756,123454,867,5,90,67,55 };
	SqList L;
	init(L, input);
	printf("排序前：\n");
	myPrint(L);

	init(L, input);
	printf("简单插入排序：\n");
	BiInsertionSort(L);
	myPrint(L);

	init(L, input);
	printf("冒泡排序：\n");
	BubbleSort(L);
	myPrint(L);

	init(L, input);
	printf("快速排序：\n");
	QuickSort(L);
	myPrint(L);

	init(L, input);
	printf("简单选择排序：\n");
	SelectSort(L);
	myPrint(L);

	init(L, input);
	printf("堆排序：\n");
	HeapSort(L);
	myPrint(L);

	init(L, input);
	printf("归并排序：\n");
	MergeSort(L);
	myPrint(L);
	return 0;
}