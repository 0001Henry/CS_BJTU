#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char VertexType; //顶点类型由用户定义
typedef int EdgeType; // 边上的权值类型由用户定义

#define MAX_VEX_NUM 20 // 最大顶点数


// 弧的结点结构(表结点)
typedef struct ArcNode {
	int  adjvex;     // 该弧所指向的顶点的位置
	//int w; // 权值
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



int visited[MAX_VEX_NUM];
void dfs(ALGraph* G, int x)
{
	visited[x] = 1;
	ArcNode* p = G->vertices[x].firstarc;
	while (p)
	{
		if (!visited[p->adjvex])
		{
			dfs(G, p->adjvex);
		}
		p = p->nextarc;
	}
}

void findFunc(ALGraph* G, int x, int y) {
	for (int i = 0; i < MAX_VEX_NUM; i++) visited[i] = 0;
	dfs(G, x);
	if (visited[y]) printf("%d 和 %d 之间存在路径\n",x,y);
	else  printf("%d 和 %d 之间不存在路径\n", x, y);
}


void createALGraph(ALGraph* G, int input[][2], int vexn, int arcn)
{
	G->arcnum = arcn;
	G->vexnum = vexn;

	for (int i = 0; i < G->vexnum; i++)
	{
		G->vertices[i].data = i;
		G->vertices[i].firstarc = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		int x = input[i][0], y = input[i][1];
		ArcNode* e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = y;
		e->nextarc = G->vertices[x].firstarc;
		G->vertices[x].firstarc = e;
	}
}


int main()
{
	ALGraph G;
	int input[][2] = {
		{0,1},
		{1,2},
		{3,2},
		{4,3},
		{2,5},
		{5,6},
		{6,7},
		{8,2}
	};
	createALGraph(&G,input,9,8);
	
	findFunc(&G, 0, 1);
	findFunc(&G, 2, 7);
	findFunc(&G, 0, 8);
	findFunc(&G, 4, 0);
	return 0;
}