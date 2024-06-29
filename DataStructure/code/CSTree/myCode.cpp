//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
////�����ֵ������ʾ��
//typedef struct CSNode
//{
//    char data;
//    struct CSNode* firstchild, * nextsibling;
//} CSNode, * CSTree;
//
//
////�����սڵ�
//CSNode* createCSNode(char ch)
//{
//    CSNode* p = (CSNode*)malloc(sizeof(CSNode));
//    if (!p)
//    {
//        exit(0);
//    }
//    p->data = ch;
//    p->firstchild = NULL;
//    p->nextsibling = NULL;
//    return p;
//}
//
//
////����1�����϶�����������ÿ���ߣ�����#A,AB,AC,BD,##��
//void buildCSTree_v1(CSTree& T, const char* input)
//{
//    int i = 0;//�ַ����±�����
//    CSNode* map[1000];//��ϣ���ڵ��ַ��data��ӳ��
//    memset(map, 0, sizeof(map));
//
//    while (input[i + 1] != '#')
//    {
//        if (i == 0)//�����ͷ�ڵ�
//        {
//            T = createCSNode(input[i + 1]);
//            map[input[i + 1]] = T;
//        }
//        else
//        {
//            char ch1 = input[i];//��ǰ���ڵ�
//            char ch2 = input[i + 1];//��ǰ����
//
//            //�����½ڵ�
//            CSNode* newNode = createCSNode(ch2);
//            map[ch2] = newNode;
//
//            //ȡ��ǰ���ڵ�ĵ�ַ
//            CSTree currentParent = map[ch1];
//            if (!currentParent->firstchild) //û�к���,����뺢��
//            {
//                currentParent->firstchild = newNode;
//            }
//            else //�к��ӣ�������ֵ�
//            {
//
//                CSTree pHead = currentParent->firstchild;
//                while (pHead->nextsibling)
//                {
//                    pHead = pHead->nextsibling;
//                }
//                pHead->nextsibling = newNode;
//            }
//        }
//        i += 2;
//    }
//
//}
//
////����2���������ɸ���Ҷ�ӽ���α���˳�����������м�ÿ�����Ķ�
//void buildCSTree_v2(CSTree& T, const char* input)
//{
//    int len = strlen(input);
//    T = createCSNode(input[0]);//����ͷ�ڵ�
//
//    CSNode** parentQueue = (CSNode**)malloc((len + 1) * sizeof(CSNode*));//�������У����ڴ游�ڵ��ַ
//    int top = 0, end = 0;//��ͷ����β
//    parentQueue[end++] = T;//ͷ�ڵ����    
//
//    int index = 0;//�ַ����±�����
//    while (top != end)
//    {
//        CSTree currentParent = parentQueue[top];//ȡ��ǰ���ڵ�ĵ�ַ
//        top++;//����
//
//        int currentDegree = input[index + 1] - '0';//��ǰ���ڵ�Ķ�
//
//        for (int i = 0; i < currentDegree; i++)
//        {
//            CSNode* newNode = createCSNode(input[index + i * 2]);
//            parentQueue[end++] = newNode;
//
//            if (NULL == currentParent->firstchild)//û�к���,����뺢��
//            {
//                currentParent->firstchild = newNode;
//            }
//            else //�к��ӣ�������ֵ�
//            {
//                CSTree pHead = currentParent->firstchild;
//                while (pHead->nextsibling)
//                {
//                    pHead = pHead->nextsibling;
//                }
//                pHead->nextsibling = newNode;
//            }
//        }
//        index += 2;
//    }
//
//}
//
////�����
//int TreeDepth(CSTree T)
//{
//    if (!T)  return 0;
//    else
//    {
//        int h1 = TreeDepth(T->firstchild);
//        int h2 = TreeDepth(T->nextsibling);
//        return(((h1 + 1) > h2) ? (h1 + 1) : h2);
//    }
//}
//int getDepthNoTree(char* input)
//{
//    int len = strlen(input);
//    int arr[100];
//    for (int i = 0; i < len / 2; i++)
//    {
//        arr[i] = input[2 * i + 1] - '0';
//    }
//    int cen = arr[0];
//    int i = 0, res = 0;
//    while (cen != 0) {
//        res++;
//        int ncen = 0;
//
//        for (int j = i + 1; j < i + 1 + cen; j++)
//        {
//            ncen += arr[j];
//        }
//
//        i += cen;
//        cen = ncen;
//    }
//    return res + 1;
//}
//
//void test1()
//{
//
//    CSTree root = NULL;
//    char input[1000]; // �����ַ���
//    printf("���������ıߣ�����#AABACBD##����");
//    scanf("%s", input);
//    //������#AABACBDBECFDGDHEIIJ##
//    /*
//           A
//      B            C
//   D      E       F
// G  H       I
//          J
//    */
//
//    buildCSTree_v1(root, input); // ������
//    int depth = TreeDepth(root); // �����������
//    printf("test1:�������Ϊ��%d\n", depth);
//
//}
//
//void test2()
//{
//    CSTree root = NULL;
//    char input[1000]; // �����ַ���
//    printf("������������������м�ÿ�����Ķȣ�����A2B2C1D0E0F0����");
//    scanf("%s", input);
//
//    //������A2B2C1D2E1F0G0H0I1J0
//    /*
//           A
//      B            C
//   D      E       F
// G  H       I
//          J
//    */
//    buildCSTree_v2(root, input); // ������
//    int depth = TreeDepth(root); // �����������
//    printf("test2:�������Ϊ��%d\n", depth);
//
//}
//
//
//void testNoTree()
//{
//    /*
//        A
//     B     C
//   D  E  F
// G
//
//*/
//    CSTree root = NULL;
//    char input[1000] = "A2B2C1D1E0F0G0";
//    buildCSTree_v2(root, input); // ������
//
//    int depth = TreeDepth(root); // �����������
//    printf("test1:�������Ϊ��%d\n", depth);
//
//    depth = getDepthNoTree(input);
//    printf("test2:�������Ϊ��%d\n", depth);
//}
//
//
