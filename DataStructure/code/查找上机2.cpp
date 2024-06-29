#include<stdio.h>
#include<stdlib.h>


#define HASHSIZE 12 // 散列表表长
#define NULLKEY -32768 

typedef struct
{
	int* elem; // 数据元素存储基址，动态分配数组
	int count; //  当前数据元素个数 
}HashTable;

int m = HASHSIZE; 


int InitHashTable(HashTable* H)
{
	int i;
	H->count = 0;
	H->elem = (int*)malloc(m * sizeof(int));
	for (i = 0; i < m; i++)
	{
		H->elem[i] = NULLKEY;
	}
	return 1;
}

// 散列函数 
int Hash(int key)
{
	return key % m; 
}

// 插入关键字进散列表 
void InsertHash(HashTable* H, int key)
{
	int addr = Hash(key); // 求散列地址 
	while (H->elem[addr] != NULLKEY) //  如果不为空，则冲突 
	{
		addr = (addr + 1) % m; // 开放定址法的线性探测 
	}
	H->elem[addr] = key; // 直到有空位后插入关键字 
	H->count++;
}

// 散列表查找关键字
int SearchHash(HashTable H, int key, int* addr)
{
	int searchCount = 1;
	*addr = Hash(key);  // 求散列地址
	while (H.elem[*addr] != key) // 如果不为空，则冲突 
	{
		++searchCount;
		*addr = (*addr + 1) % m; //开放定址法的线性探测
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key)) 
			return 0;	//关键字不存在 
	}
	return searchCount;
}

void printHash(HashTable H)
{
	for (int i = 0; i < m; i++)
	{
		if (H.elem[i] != NULLKEY)
		{
			printf("%d ", H.elem[i]);
		}
	}
	printf("\n");
}

int main()
{
	int arr[100000];
	HashTable H;	
	
	int n;
	printf("输入关键字个数: ");
	scanf("%d", &n);

	InitHashTable(&H);

	// 建表
	for (int i = 0; i < n; i++)
	{
		printf("输入第%d个关键字: ", i + 1);
		int a = 0;
		scanf("%d", &arr[i]);
		InsertHash(&H, arr[i]);

	}

	int p,key = 24;
	int result = SearchHash(H, key, &p);
	if (result)
	{
		printf("查找 %d 的地址为：%d \n", key, p);
		printf("查找次数为：%d \n", result);
	}	
	else
	{
		printf("查找 %d 失败。\n", key);
		InsertHash(&H, key);
	}

    printf("当前散列表为:\n");
	printHash(H);
	printf("\n");

	for (int i = 0; i < n; i++)
	{
		key = arr[i];
		SearchHash(H, key, &p);
		printf("查找 %d 的地址为：%d \n", key, p);
	}

	return 0;
}
