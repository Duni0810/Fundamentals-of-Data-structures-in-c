#ifndef __MGRAPH_H
#define __MGRAPH_H

typedef void   MGraph;	// ͼ 
typedef void   MVertex; // ���� 
typedef void (MGraph_Printf)(MVertex*); // ��ӡ���� 

// ���� n�������ͼ  ��������Ϊ v 
MGraph *MGraph_Create(MVertex **v, int n);

//  �ݻ�ͼ 
void MGraph_Destroy(MGraph* graph);

// ���ͼ Ҳ������ն���֮������� 
void MGraph_Clear(MGraph* graph);

// ��Ӷ���֮������� ��������ʹ�õ�������ͼ 
int MGraph_AddEdge(MGraph* graph, int v1, int v2, int w);

// �Ƴ��������ϵ 
int MGraph_RemoveEdge(MGraph* graph, int v1, int v2);

// ��ȡ��������֮���Ȩֵ  v1->v2 
int MGraph_GetEdge(MGraph* graph, int v1, int v2);

// ��ȡ����Ķ� 
int MGraph_TD(MGraph* graph, int v);

// ��ȡ������ 
int MGraph_VertexCount(MGraph* graph);

// ��ȡͼ�е��������ӱ��� 
int MGraph_EdgeCount(MGraph* graph);

// ����������� 
void MGraph_DFS(MGraph* graph, int v, MGraph_Printf* pFunc);

// ����������� 
void MGraph_BFS(MGraph* graph, int v, MGraph_Printf* pFunc);

// ��ӡͼ 
void MGraph_Display(MGraph* graph, MGraph_Printf* pFunc);


#endif

