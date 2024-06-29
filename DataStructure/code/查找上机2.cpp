#include<stdio.h>
#include<stdlib.h>


#define HASHSIZE 12 // ɢ�б��
#define NULLKEY -32768 

typedef struct
{
	int* elem; // ����Ԫ�ش洢��ַ����̬��������
	int count; //  ��ǰ����Ԫ�ظ��� 
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

// ɢ�к��� 
int Hash(int key)
{
	return key % m; 
}

// ����ؼ��ֽ�ɢ�б� 
void InsertHash(HashTable* H, int key)
{
	int addr = Hash(key); // ��ɢ�е�ַ 
	while (H->elem[addr] != NULLKEY) //  �����Ϊ�գ����ͻ 
	{
		addr = (addr + 1) % m; // ���Ŷ�ַ��������̽�� 
	}
	H->elem[addr] = key; // ֱ���п�λ�����ؼ��� 
	H->count++;
}

// ɢ�б���ҹؼ���
int SearchHash(HashTable H, int key, int* addr)
{
	int searchCount = 1;
	*addr = Hash(key);  // ��ɢ�е�ַ
	while (H.elem[*addr] != key) // �����Ϊ�գ����ͻ 
	{
		++searchCount;
		*addr = (*addr + 1) % m; //���Ŷ�ַ��������̽��
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key)) 
			return 0;	//�ؼ��ֲ����� 
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
	printf("����ؼ��ָ���: ");
	scanf("%d", &n);

	InitHashTable(&H);

	// ����
	for (int i = 0; i < n; i++)
	{
		printf("�����%d���ؼ���: ", i + 1);
		int a = 0;
		scanf("%d", &arr[i]);
		InsertHash(&H, arr[i]);

	}

	int p,key = 24;
	int result = SearchHash(H, key, &p);
	if (result)
	{
		printf("���� %d �ĵ�ַΪ��%d \n", key, p);
		printf("���Ҵ���Ϊ��%d \n", result);
	}	
	else
	{
		printf("���� %d ʧ�ܡ�\n", key);
		InsertHash(&H, key);
	}

    printf("��ǰɢ�б�Ϊ:\n");
	printHash(H);
	printf("\n");

	for (int i = 0; i < n; i++)
	{
		key = arr[i];
		SearchHash(H, key, &p);
		printf("���� %d �ĵ�ַΪ��%d \n", key, p);
	}

	return 0;
}
