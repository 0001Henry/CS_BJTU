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

int dfs(ALGraph* G, int x, int y, int k)
{
	if (x == y && k == 0)return 1;//�ҵ���
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
		visited[x] = 0;// ����
	}
	return 0;
}

void findPath(ALGraph* G, int x, int y, int k) {
	for (int i = 0; i < MAX_VEX_NUM; i++) visited[i] = 0;
	if (dfs(G, x, y, k)) printf("%d �� %d ֮�� ���� ��Ϊ %d ��·��\n", x, y,k);
	else printf("%d �� %d ֮�� ������ ��Ϊ%d��·��\n", x, y, k);
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
		//����ͼ
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