#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_VEX_NUM 50 // 最大顶点数
#define MAX_W 999999 // 最大边权

// 邻接矩阵
typedef struct {
	char vexs[MAX_VEX_NUM]; // 顶点表 
	int arc[MAX_VEX_NUM][MAX_VEX_NUM]; // 邻接矩阵，即边表 
	int vexnum, arcnum; // 顶点数和边数 
}MGraph;

// 辅助数组
typedef struct {
	int adjvex;// U集中的顶点序号
	int lowcost;// 边的权值
}CLOSEDGE;

int total = 0;// 总里程

void init(MGraph* G, int anum, int vnum)
{
	total = 0;
	G->arcnum = anum;
	G->vexnum = vnum;
	for (int i = 0; i < vnum; i++)
	{
		G->vexs[i] = 'A' + i;
		for (int j = 0; j < vnum; j++)
		{
			G->arc[i][j] = MAX_W;
		}
	}
}

int minimum(CLOSEDGE* closedge, int vnum)
{
	int k = -1;
	int arcmin = MAX_W;
	for (int i = 0; i < vnum; i++)
	{
		if (closedge[i].lowcost != 0 && closedge[i].lowcost < arcmin)
		{
			arcmin = closedge[i].lowcost;
			k = i;
		}
	}
	if (arcmin == MAX_W)return -1;
	else
	{
		total += arcmin;
		return k;
	}
}

void MiniSpanTree_Prime(MGraph* G, int u)
{
	int k = u;	
	CLOSEDGE closedge[MAX_VEX_NUM];

	// 辅助数组初始化
	for (int i = 0; i < G->vexnum; i++)
	{
		if (i != k)
		{
			closedge[i].adjvex = k;
			closedge[i].lowcost = G->arc[i][k];
		}
	}

	closedge[k].lowcost = 0; // 初始，U＝{u}

	// 选择其余N-1个顶点
	for (int i = 1; i < G->vexnum; i++)
	{
		k = minimum(closedge, G->vexnum); // 求出加入U集的下一个顶点k
		if (k == -1)return;
		closedge[k].lowcost = 0;// 顶点k加入U集

		printf(" %c - %c\t代价：%d\n", G->vexs[closedge[k].adjvex], G->vexs[k],G->arc[k][closedge[k].adjvex]);// 输出这条边
		//printf(" %d - %d\t代价：%d\n",closedge[k].adjvex, k, G->arc[k][closedge[k].adjvex]);// 输出这条边
																									
		// 更新各点到U集的距离和所连U中的顶点
		for (int j = 0; j < G->vexnum; j++)
		{
			//if (closedge[j].lowcost == 0)continue;
			if (k != j && G->arc[k][j] < closedge[j].lowcost)
			{
				closedge[j].lowcost = G->arc[k][j];
				closedge[j].adjvex = k;
			}
		}
	}
}

int main()
{
	MGraph G;
	int input[14][3] = {
		{0,1,4},
		{0,7,8},
		{1,7,11},
		{1,2,8},
		{2,3,7},
		{2,8,2},
		{2,5,4},
		{3,5,14},
		{3,4,9},
		{4,5,10},
		{5,6,2},
		{6,8,6},
		{6,7,1},
		{7,8,7}
	};
	int vnum = 9, anum = 14;
	total = 0;

	init(&G, vnum, anum);

	// 建立无向图
	for (int i = 0; i < anum; i++) {
		G.arc[input[i][0]][input[i][1]] = G.arc[input[i][1]][input[i][0]] = input[i][2];
	}

	MiniSpanTree_Prime(&G, 0);
	printf("总代价：%d\n", total);
	return 0;
}