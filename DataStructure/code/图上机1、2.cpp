#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char VertexType; //顶点类型由用户定义
typedef int EdgeType; // 边上的权值类型由用户定义

#define MAXSIZE 100 // 存储空间初始分配量 
#define MAX_VEX_NUM 20 // 最大顶点数

// 邻接矩阵
typedef struct
{
	VertexType vexs[MAX_VEX_NUM]; // 顶点表 
	EdgeType arc[MAX_VEX_NUM][MAX_VEX_NUM]; // 邻接矩阵，即边表 
	int vexnum, arcnum; // 图中当前的顶点数和边数 
}MGraph;


// 弧的结点结构(表结点)
typedef struct ArcNode {
	int  adjvex;     // 该弧所指向的顶点的位置
	struct ArcNode* nextarc;// 指向下一条弧的指针
} ArcNode;

// 顶点的结点结构(头结点)
typedef struct VNode {
	VertexType  data;   // 顶点信息
	ArcNode* firstarc;// 指向第一条依附该顶点的弧
} VNode, AdjList[MAX_VEX_NUM];

// 邻接表
typedef struct {
	AdjList vertices;   // 表头结点向量
	int vexnum, arcnum;// 图的当前顶点数和弧数
} ALGraph;



// 队列结构与相关函数

// 循环队列的顺序存储结构
typedef struct
{
	int data[MAXSIZE];
	int front;    	// 头指针 
	int rear;		// 尾指针，若队列不空，指向队列尾元素的下一个位置 
}Queue;

// 初始化空队列Q 
int InitQueue(Queue* Q)
{
	Q->front = 0;
	Q->rear = 0;
	return 1;
}

// 若队列Q为空队列,则返回TRUE,否则返回FALSE 
int QueueEmpty(Queue Q)
{
	if (Q.front == Q.rear) /* 队列空的标志 */
		return 1;
	else
		return 0;
}

// 若队列未满，则插入元素e为Q新的队尾元素 
int EnQueue(Queue* Q, int e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)	/* 队列满的判断 */
		return 0;
	Q->data[Q->rear] = e;			/* 将元素e赋值给队尾 */
	Q->rear = (Q->rear + 1) % MAXSIZE;/* rear指针向后移一位置， */
								/* 若到最后则转到数组头部 */
	return 1;
}

// 若队列不空，则删除Q中队头元素，用e返回其值 
int DeQueue(Queue* Q, int* e)
{
	if (Q->front == Q->rear)			/* 队列空的判断 */
		return 0;
	*e = Q->data[Q->front];				/* 将队头元素赋值给e */
	Q->front = (Q->front + 1) % MAXSIZE;	/* front指针向后移一位置， */
									/* 若到最后则转到数组头部 */
	return 1;
}


//构建邻接矩阵 建立无向图
void CreateMGraph(MGraph* G,int input[][3],int vexn,int arcn)
{
	memset(G->arc, 0, sizeof G->arc);// 初始化图 
	G->arcnum = arcn;
	G->vexnum = vexn;

	// 读入顶点信息，建立顶点表
	for (int i = 0; i < G->vexnum; i++)
	{
		G->vexs[i] = 'A' + i;
	}
	
	// 读入边，建立边表
	for (int i = 0; i < G->arcnum; i++) {
		G->arc[input[i][0]][input[i][1]] = G->arc[input[i][1]][input[i][0]] = input[i][2];
	}
}

//构建邻接表 建立无向图
void CreateALGraph(MGraph& G, ALGraph& GL)
{
	GL.arcnum = G.arcnum;
	GL.vexnum = G.vexnum;

	// 建立顶点表
	for (int i = 0; i < G.vexnum; i++)
	{
		GL.vertices[i].data = G.vexs[i];
		GL.vertices[i].firstarc = NULL;
	}

	// 建立边表
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = G.vexnum; j >= 0; j--)
		{
			if (G.arc[i][j] != 0)
			{
				// 头插法
				ArcNode* newArc = (ArcNode*)malloc(sizeof(ArcNode));
				newArc->adjvex = j;
				newArc->nextarc = GL.vertices[i].firstarc;

				GL.vertices[i].firstarc = newArc;
			}
		}
	}
}

// 用于记录顶点是否访问过
int visited[MAX_VEX_NUM];

void DFS(MGraph G, int i)
{
	visited[i] = 1;// 设置当前顶点访问过 
	printf("%c ", G.vexs[i]);// 访问
	for (int j = 0; j < G.vexnum; j++)
	{
		if (G.arc[i][j] == 1 && !visited[j])// 顶点若与当前顶点存在边且未访问过 
			DFS(G, j);
	}
}

//深度遍历,初始节点下标为u(邻接矩阵)
void DFSTraverse(MGraph G, int u) 
{
	// 初始化
	memset(visited, 0, sizeof visited);

	// 从初始节点开始DFS
	DFS(G, u);

	// 再对未访问过的顶点调用DFS
	for (int i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
			DFS(G, i);
	}
}

//广度遍历,初始节点下标为u(邻接矩阵)
void BFSTraverse(MGraph G, int u)
{
	//初始化
	memset(visited, 0, sizeof visited);

	Queue Q;
	InitQueue(&Q);

	int i = u;
	visited[i] = 1;		// 设置当前顶点访问过 
	printf("%c ", G.vexs[i]);// 访问
	EnQueue(&Q, i);		// 将此顶点入队
	while (!QueueEmpty(Q))	// 若当前队列不为空 
	{
		DeQueue(&Q, &i);	// 将队头元素出队列，赋值给i 
		for (int j = 0; j < G.vexnum; j++)
		{
			// 顶点若与当前顶点存在边且未访问过 
			if (G.arc[i][j] != 0 && !visited[j])
			{
				visited[j] = 1;			// 设置当前顶点访问过 
				printf("%c ", G.vexs[j]); // 访问
				EnQueue(&Q, j);	// 将此顶点入队
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

// 深度遍历, 初始节点下标为u(邻接表)
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

// 广度遍历, 初始节点下标为u(邻接表)
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
	printf("邻接矩阵：\n");
	printf("深度遍历:");
	DFSTraverse(G, 1);
	printf("\n广度遍历:");
	BFSTraverse(G, 1);

	printf("\n邻接表：\n");
	CreateALGraph(G, GL);
	printf("深度遍历:");
	DFSTraverse_AL(GL, 1);
	printf("\n广度遍历:");
	BFSTraverse_AL(GL, 1);
	return 0;
}