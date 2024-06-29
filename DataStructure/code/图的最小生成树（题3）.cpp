#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_VEX_NUM 50 // ��󶥵���
#define MAX_W 999999 // ����Ȩ

// �ڽӾ���
typedef struct {
	char vexs[MAX_VEX_NUM]; // ����� 
	int arc[MAX_VEX_NUM][MAX_VEX_NUM]; // �ڽӾ��󣬼��߱� 
	int vexnum, arcnum; // �������ͱ��� 
}MGraph;

// ��������
typedef struct {
	int adjvex;// U���еĶ������
	int lowcost;// �ߵ�Ȩֵ
}CLOSEDGE;

int total = 0;// �����

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

	// ���������ʼ��
	for (int i = 0; i < G->vexnum; i++)
	{
		if (i != k)
		{
			closedge[i].adjvex = k;
			closedge[i].lowcost = G->arc[i][k];
		}
	}

	closedge[k].lowcost = 0; // ��ʼ��U��{u}

	// ѡ������N-1������
	for (int i = 1; i < G->vexnum; i++)
	{
		k = minimum(closedge, G->vexnum); // �������U������һ������k
		if (k == -1)return;
		closedge[k].lowcost = 0;// ����k����U��

		printf(" %c - %c\t���ۣ�%d\n", G->vexs[closedge[k].adjvex], G->vexs[k],G->arc[k][closedge[k].adjvex]);// ���������
		//printf(" %d - %d\t���ۣ�%d\n",closedge[k].adjvex, k, G->arc[k][closedge[k].adjvex]);// ���������
																									
		// ���¸��㵽U���ľ��������U�еĶ���
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

	// ��������ͼ
	for (int i = 0; i < anum; i++) {
		G.arc[input[i][0]][input[i][1]] = G.arc[input[i][1]][input[i][0]] = input[i][2];
	}

	MiniSpanTree_Prime(&G, 0);
	printf("�ܴ��ۣ�%d\n", total);
	return 0;
}