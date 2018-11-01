#ifndef __LGRAPH_H
#define __LGRAPH_H


typedef void LGraph;  //  �ڽ����� 
typedef void LVertex; //  �������� 
typedef void (LGraph_Printf)(LVertex*);  // ��ӡ���� 

// ���� n �����㣬���ݷֱ�Ϊ v��ͼ 
LGraph* LGraph_Create(LVertex** v, int n);

// �ݻ�ͼ 
void LGraph_Destroy(LGraph* graph);

// ���ͼ 
void LGraph_Clear(LGraph* graph);

// ��Ӷ���֮����ϵ��Ȩ 
int LGraph_AddEdge(LGraph* graph, int v1, int v2, int w);

// �Ƴ��� 
int LGraph_RemoveEdge(LGraph* graph, int v1, int v2);

// ��ȡ v1->v2 ��Ȩ  
int LGraph_GetEdge(LGraph* graph, int v1, int v2);

// ��ȡĳ������Ķ� 
int LGraph_TD(LGraph* graph, int v);

// ��ȡͼ�Ķ����� 
int LGraph_VertexCount(LGraph* graph);

// ��ȡͼ�ı��� 
int LGraph_EdgeCount(LGraph* graph);

// ������� 
void LGraph_DFS(LGraph* graph, int v, LGraph_Printf* pFunc);

// ������� 
void LGraph_BFS(LGraph* graph, int v, LGraph_Printf* pFunc);

// ��ʾ 
void LGraph_Display(LGraph* graph, LGraph_Printf* pFunc);
#endif

