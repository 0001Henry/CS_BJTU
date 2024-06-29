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

int dfs(ALGraph* G, int x, int y, int k)
{
	if (x == y && k == 0)return 1;//找到了
	else if (k > 0)
	{
		visited[x] = 1;
		for (ArcNode* p = G->vertices[x].firstarc; p != NULL; p = p->nextarc)
		{
			int v = p->adjvex;
			if (visited[v])continue;
			else if (dfs(G, v, y, k - 1))
			{
				return 1;
			}
		}
		visited[x] = 0;// 回溯
	}
	return 0;
}

void findPath(ALGraph* G, int x, int y, int k) {
	for (int i = 0; i < MAX_VEX_NUM; i++) visited[i] = 0;
	if (dfs(G, x, y, k)) printf("%d 和 %d 之间 存在 长为 %d 的路径\n", x, y,k);
	else printf("%d 和 %d 之间 不存在 长为%d的路径\n", x, y, k);
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
		{8,2},
		//无向图
		{1,0},
		{2,1},
		{2,3},
		{3,4},
		{5,2},
		{6,5},
		{7,6},
		{2,8}
	};
	createALGraph(&G,input,9,8);
	
	findPath(&G, 0, 1, 1);
	findPath(&G, 0, 1, 2);
	findPath(&G, 2, 7, 3);
	findPath(&G, 4, 0, 4);

	return 0;
}