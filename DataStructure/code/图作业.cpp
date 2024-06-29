#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char VertexType; //�����������û�����
typedef int EdgeType; // ���ϵ�Ȩֵ�������û�����

#define MAX_VEX_NUM 20 // ��󶥵���


// ���Ľ��ṹ(����)
typedef struct ArcNode {
	int  adjvex;     // �û���ָ��Ķ����λ��
	//int w; // Ȩֵ
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
	if (visited[y]) printf("%d �� %d ֮�����·��\n",x,y);
	else  printf("%d �� %d ֮�䲻����·��\n", x, y);
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