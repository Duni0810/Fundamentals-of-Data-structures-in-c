#ifndef __LGRAPH_H
#define __LGRAPH_H


typedef void LGraph;  //  邻接链表 
typedef void LVertex; //  顶点数据 
typedef void (LGraph_Printf)(LVertex*);  // 打印函数 

// 创建 n 个顶点，数据分别为 v的图 
LGraph* LGraph_Create(LVertex** v, int n);

// 摧毁图 
void LGraph_Destroy(LGraph* graph);

// 清空图 
void LGraph_Clear(LGraph* graph);

// 添加顶点之间联系和权 
int LGraph_AddEdge(LGraph* graph, int v1, int v2, int w);

// 移除边 
int LGraph_RemoveEdge(LGraph* graph, int v1, int v2);

// 获取 v1->v2 的权  
int LGraph_GetEdge(LGraph* graph, int v1, int v2);

// 获取某个顶点的度 
int LGraph_TD(LGraph* graph, int v);

// 获取图的顶点数 
int LGraph_VertexCount(LGraph* graph);

// 获取图的边数 
int LGraph_EdgeCount(LGraph* graph);

// 深度搜索 
void LGraph_DFS(LGraph* graph, int v, LGraph_Printf* pFunc);

// 广度搜索 
void LGraph_BFS(LGraph* graph, int v, LGraph_Printf* pFunc);

// 显示 
void LGraph_Display(LGraph* graph, LGraph_Printf* pFunc);
#endif

