#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char VertexType; //�����������û�����
typedef int EdgeType; // ���ϵ�Ȩֵ�������û�����

#define MAXSIZE 100 // �洢�ռ��ʼ������ 
#define MAX_VEX_NUM 20 // ��󶥵���

// �ڽӾ���
typedef struct
{
	VertexType vexs[MAX_VEX_NUM]; // ����� 
	EdgeType arc[MAX_VEX_NUM][MAX_VEX_NUM]; // �ڽӾ��󣬼��߱� 
	int vexnum, arcnum; // ͼ�е�ǰ�Ķ������ͱ��� 
}MGraph;


// ���Ľ��ṹ(����)
typedef struct ArcNode {
	int  adjvex;     // �û���ָ��Ķ����λ��
	struct ArcNode* nextarc;// ָ����һ������ָ��
} ArcNode;

// ����Ľ��ṹ(ͷ���)
typedef struct VNode {
	VertexType  data;   // ������Ϣ
	ArcNode* firstarc;// ָ���һ�������ö���Ļ�
} VNode, AdjList[MAX_VEX_NUM];

// �ڽӱ�
typedef struct {
	AdjList vertices;   // ��ͷ�������
	int vexnum, arcnum;// ͼ�ĵ�ǰ�������ͻ���
} ALGraph;



// ���нṹ����غ���

// ѭ�����е�˳��洢�ṹ
typedef struct
{
	int data[MAXSIZE];
	int front;    	// ͷָ�� 
	int rear;		// βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ�� 
}Queue;

// ��ʼ���ն���Q 
int InitQueue(Queue* Q)
{
	Q->front = 0;
	Q->rear = 0;
	return 1;
}

// ������QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE 
int QueueEmpty(Queue Q)
{
	if (Q.front == Q.rear) /* ���пյı�־ */
		return 1;
	else
		return 0;
}

// ������δ���������Ԫ��eΪQ�µĶ�βԪ�� 
int EnQueue(Queue* Q, int e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)	/* ���������ж� */
		return 0;
	Q->data[Q->rear] = e;			/* ��Ԫ��e��ֵ����β */
	Q->rear = (Q->rear + 1) % MAXSIZE;/* rearָ�������һλ�ã� */
								/* ���������ת������ͷ�� */
	return 1;
}

// �����в��գ���ɾ��Q�ж�ͷԪ�أ���e������ֵ 
int DeQueue(Queue* Q, int* e)
{
	if (Q->front == Q->rear)			/* ���пյ��ж� */
		return 0;
	*e = Q->data[Q->front];				/* ����ͷԪ�ظ�ֵ��e */
	Q->front = (Q->front + 1) % MAXSIZE;	/* frontָ�������һλ�ã� */
									/* ���������ת������ͷ�� */
	return 1;
}


//�����ڽӾ��� ��������ͼ
void CreateMGraph(MGraph* G,int input[][3],int vexn,int arcn)
{
	memset(G->arc, 0, sizeof G->arc);// ��ʼ��ͼ 
	G->arcnum = arcn;
	G->vexnum = vexn;

	// ���붥����Ϣ�����������
	for (int i = 0; i < G->vexnum; i++)
	{
		G->vexs[i] = 'A' + i;
	}
	
	// ����ߣ������߱�
	for (int i = 0; i < G->arcnum; i++) {
		G->arc[input[i][0]][input[i][1]] = G->arc[input[i][1]][input[i][0]] = input[i][2];
	}
}

//�����ڽӱ� ��������ͼ
void CreateALGraph(MGraph& G, ALGraph& GL)
{
	GL.arcnum = G.arcnum;
	GL.vexnum = G.vexnum;

	// ���������
	for (int i = 0; i < G.vexnum; i++)
	{
		GL.vertices[i].data = G.vexs[i];
		GL.vertices[i].firstarc = NULL;
	}

	// �����߱�
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = G.vexnum; j >= 0; j--)
		{
			if (G.arc[i][j] != 0)
			{
				// ͷ�巨
				ArcNode* newArc = (ArcNode*)malloc(sizeof(ArcNode));
				newArc->adjvex = j;
				newArc->nextarc = GL.vertices[i].firstarc;

				GL.vertices[i].firstarc = newArc;
			}
		}
	}
}

// ���ڼ�¼�����Ƿ���ʹ�
int visited[MAX_VEX_NUM];

void DFS(MGraph G, int i)
{
	visited[i] = 1;// ���õ�ǰ������ʹ� 
	printf("%c ", G.vexs[i]);// ����
	for (int j = 0; j < G.vexnum; j++)
	{
		if (G.arc[i][j] == 1 && !visited[j])// �������뵱ǰ������ڱ���δ���ʹ� 
			DFS(G, j);
	}
}

//��ȱ���,��ʼ�ڵ��±�Ϊu(�ڽӾ���)
void DFSTraverse(MGraph G, int u) 
{
	// ��ʼ��
	memset(visited, 0, sizeof visited);

	// �ӳ�ʼ�ڵ㿪ʼDFS
	DFS(G, u);

	// �ٶ�δ���ʹ��Ķ������DFS
	for (int i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
			DFS(G, i);
	}
}

//��ȱ���,��ʼ�ڵ��±�Ϊu(�ڽӾ���)
void BFSTraverse(MGraph G, int u)
{
	//��ʼ��
	memset(visited, 0, sizeof visited);

	Queue Q;
	InitQueue(&Q);

	int i = u;
	visited[i] = 1;		// ���õ�ǰ������ʹ� 
	printf("%c ", G.vexs[i]);// ����
	EnQueue(&Q, i);		// ���˶������
	while (!QueueEmpty(Q))	// ����ǰ���в�Ϊ�� 
	{
		DeQueue(&Q, &i);	// ����ͷԪ�س����У���ֵ��i 
		for (int j = 0; j < G.vexnum; j++)
		{
			// �������뵱ǰ������ڱ���δ���ʹ� 
			if (G.arc[i][j] != 0 && !visited[j])
			{
				visited[j] = 1;			// ���õ�ǰ������ʹ� 
				printf("%c ", G.vexs[j]); // ����
				EnQueue(&Q, j);	// ���˶������
			}
		}
	}
}


void DFS_AL(ALGraph& GL,int i)
{
	visited[i] = 1;
	printf(" %c", GL.vertices[i].data);
	ArcNode* p = GL.vertices[i].firstarc;
	while (p)
	{
		if (!visited[p->adjvex])
		{
			DFS_AL(GL, p->adjvex);
		}
		p = p->nextarc;
	}
}

// ��ȱ���, ��ʼ�ڵ��±�Ϊu(�ڽӱ�)
void DFSTraverse_AL(ALGraph& GL,int u)
{
	memset(visited, 0, sizeof visited);
	DFS_AL(GL, u);
	for (int i = 0; i < GL.vexnum; i++)
	{
		if (!visited[i])
		{
			DFS_AL(GL, i);
		}
	}
}

// ��ȱ���, ��ʼ�ڵ��±�Ϊu(�ڽӱ�)
void BFSTraverse_AL(ALGraph& GL, int u)
{
	memset(visited, 0, sizeof visited);
	Queue Q;
	InitQueue(&Q);

	visited[u] = 1;
	printf(" %c", GL.vertices[u].data);
	EnQueue(&Q, u);
	while (!QueueEmpty(Q))
	{
		int e;
		DeQueue(&Q, &e);
		ArcNode* p = GL.vertices[e].firstarc;
		while (p)
		{
			if (!visited[p->adjvex])
			{
				visited[p->adjvex] = 1;
				printf(" %c", GL.vertices[p->adjvex].data);
				EnQueue(&Q, p->adjvex);
			}
			p = p->nextarc;
		}
	}
}


int main()
{
	MGraph G;
	ALGraph GL;
	int input[][3] = {
	{0,1,4},
//	{0,7,8},
//	{1,7,11},
	{1,2,8},
	{2,3,7},
	{2,8,2},
	{2,5,4},
//	{3,5,14},
	{3,4,9},
	{4,5,10},
	{5,6,2},
	{6,8,6},
	{6,7,1},
	{7,8,7}
	};
	CreateMGraph(&G,input,9,11);
	printf("�ڽӾ���\n");
	printf("��ȱ���:");
	DFSTraverse(G, 1);
	printf("\n��ȱ���:");
	BFSTraverse(G, 1);

	printf("\n�ڽӱ�\n");
	CreateALGraph(G, GL);
	printf("��ȱ���:");
	DFSTraverse_AL(GL, 1);
	printf("\n��ȱ���:");
	BFSTraverse_AL(GL, 1);
	return 0;
}