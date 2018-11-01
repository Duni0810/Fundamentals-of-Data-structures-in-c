#ifndef __MGRAPH_H
#define __MGRAPH_H

typedef void   MGraph;	// 图 
typedef void   MVertex; // 顶点 
typedef void (MGraph_Printf)(MVertex*); // 打印函数 

// 创建 n个顶点的图  定点数据为 v 
MGraph *MGraph_Create(MVertex **v, int n);

//  摧毁图 
void MGraph_Destroy(MGraph* graph);

// 清空图 也就是清空顶点之间的连接 
void MGraph_Clear(MGraph* graph);

// 添加顶点之间的连接 这里我们使用的是有向图 
int MGraph_AddEdge(MGraph* graph, int v1, int v2, int w);

// 移除顶点间联系 
int MGraph_RemoveEdge(MGraph* graph, int v1, int v2);

// 获取两个顶点之间的权值  v1->v2 
int MGraph_GetEdge(MGraph* graph, int v1, int v2);

// 获取顶点的度 
int MGraph_TD(MGraph* graph, int v);

// 获取顶点数 
int MGraph_VertexCount(MGraph* graph);

// 获取图中的所有连接边数 
int MGraph_EdgeCount(MGraph* graph);

// 深度优先搜索 
void MGraph_DFS(MGraph* graph, int v, MGraph_Printf* pFunc);

// 广度优先搜索 
void MGraph_BFS(MGraph* graph, int v, MGraph_Printf* pFunc);

// 打印图 
void MGraph_Display(MGraph* graph, MGraph_Printf* pFunc);


#endif

