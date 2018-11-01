#include <stdio.h>
#include <malloc.h>
#include "graph.h"
#include "link_queue.h" 

//  头指针信息 
typedef struct _tag_MGraph {
	int count;  	// 顶点数
	MVertex **v; 	// 顶点相关数据
	int **matrix; 	// 邻接矩阵 
}MGraph_t; 


static void Recursive_dfs(MGraph_t *graph, int v, int visit[], MGraph_Printf* pFunc)
{
	int i = 0;
	
	pFunc(graph->v[v]); // 打印数据
	visit[v] = 1;		// 标记已读 
	printf(",");
	
	for(i = 0; i < graph->count; i++) {
		if(!visit[i] && (graph->matrix[v][i])) {
			Recursive_dfs(graph, i, visit, pFunc);
		}
	} 
}

static void Recursive_bfs(MGraph_t *graph, int v, int visit[], MGraph_Printf* pFunc)
{
	LinkQueue *queue = LinkQueue_Create(); // 申请队列 
	
	if (queue != NULL) {
		// 因为 V 可能是0 我们实现的数据结构不支持0 
		//所以这里我们加上 一个地址 之后出队列去掉就是 
		LinkQueue_Append(queue, graph->v + v); 
		
		visit[v] = 1;
		
		while (LinkQueue_Length(queue) > 0) {
			int i = 0;
			
			// 出列减去之前添加的数据 
			v = (MVertex**)LinkQueue_Poll(queue) - graph->v;
			pFunc(graph->v[v]); 
			printf(",");
			
			for(i = 0; i< graph->count; i++) {
				if((graph->matrix[v][i] != 0) && !visit[i]) {
					LinkQueue_Append(queue, graph->v + i); 
					visit[i] = 1;	
				}
			}
		}
	}
	
	LinkQueue_Destroy(queue); 
}



// 创建 n个顶点的图  顶点数据为 v 
MGraph *MGraph_Create(MVertex **v, int n)
{
	MGraph_t *ret = NULL;
	
	if ((NULL != v) && (n > 0)) { //因为图是有穷非空集合 
		ret = (MGraph_t *)malloc(sizeof(MGraph_t));
		if (ret != NULL) {
			ret->count = n;
			
			int *p = NULL; 
			// 申请数据保存节点空间 
			ret->v = (MVertex **)malloc(sizeof(MVertex *) * n);
			
			//动态申请二维数组空间 用于保存邻接链表 
			ret->matrix = (int **)malloc(sizeof(int *) * n);
			p = (int *)calloc(n * n, sizeof(int)); 
			
			// 合法性判断 
			if ((NULL != ret->v) && (NULL != ret->matrix) && (NULL != p)) {
				int i = 0;
				
				// 构建二维数组
				for(i = 0; i < n; i++) {
					ret->v[i] = v[i]; // 数据保存 
					ret->matrix[i] = p + i * n; // 构建二维数组 
				} 
				
			} else { // 失败 
				free(p);
				free(ret->matrix);
				free(ret->v); 
				free(ret);
			}
		}
	}

	return ret;
} 

//  摧毁图 
void MGraph_Destroy(MGraph* graph)
{
	MGraph_t *ret = (MGraph_t *)graph;
	
	if (ret != NULL) {
		free(ret->v);			// 清空定点数据指针 
		free(ret->matrix[0]);	// 清空数据域 
		free(ret->matrix);		// 清空邻接数组 
		free(ret);				// 最后清空头节点数据 
	} 
}

// 清空图 也就是清空顶点之间的连接 
void MGraph_Clear(MGraph* graph)
{
	MGraph_t *ret = (MGraph_t *)graph;
	
	if(ret != NULL) {
		int i = 0;
		int j = 0;
		
		// 让邻接矩阵数据清空 
		for (i = 0; i < ret->count; i++) {
			for (j = 0; j < ret->count; j++) {
				ret->matrix[i][j] = 0;
			}
		}
	} 
}

// 添加顶点之间的连接 这里我们使用的是有向图 
int MGraph_AddEdge(MGraph* graph, int v1, int v2, int w)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int ret = (tgraph != NULL);
	
	ret = ret && (v1 >= 0) && (v1 <= tgraph->count);
	ret = ret && (v2 >= 0) && (v2 <= tgraph->count);
	ret = ret && (w >= 0);
	
	// 插入只需要将邻接矩阵相应的位置的值置为权值就可以了 
	if (ret) {
		tgraph->matrix[v1][v2] = w;
	}
	
	return ret;
} 

// 移除顶点间联系 
int MGraph_RemoveEdge(MGraph* graph, int v1, int v2)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int ret = MGraph_GetEdge(graph, v1, v2);
	
	// 插入只需要将邻接矩阵相应的位置的值置为权值就可以了 
	if (ret != 0) {
		tgraph->matrix[v1][v2] = 0;
	}
	
	return ret;
} 

// 获取两个顶点之间的权值  v1->v2 
int MGraph_GetEdge(MGraph* graph, int v1, int v2)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int flag = (tgraph != NULL);
	int ret = 0;
	
	flag = flag && (v1 >= 0) && (v1 <= tgraph->count);
	flag = flag && (v2 >= 0) && (v2 <= tgraph->count);
	
	// 插入只需要将邻接矩阵相应的位置的值置为权值就可以了 
	if (flag) {
		ret = tgraph->matrix[v1][v2];
	}
	
	return ret;
}

// 获取顶点的度  顶点的度 = 入度 + 出度 
int MGraph_TD(MGraph* graph, int v)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int flag = (tgraph != NULL);
	int ret = 0;
	
	flag = flag && (v >= 0) && (v < tgraph->count); 
	
	if (flag) {
		int i = 0;
		
		// 遍历数据域就可以 
		for (i = 0; i < tgraph->count; i++) {
			// 出度
			if (tgraph->matrix[v][i] != 0) {
				ret++; 
			} 
			
			if (tgraph->matrix[i][v] != 0) {
				ret++;
			}
		}
	}	
	return ret;
} 

// 获取顶点数 
int MGraph_VertexCount(MGraph* graph)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int ret = 0;
	
	// 直接返回头节点信息中数据 
	if (tgraph != NULL) {
		ret = tgraph->count;
	} 
	return ret;
}

// 获取图中的所有连接边数 
int MGraph_EdgeCount(MGraph* graph)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int ret = 0;
	
	if (tgraph != NULL) {
		int i = 0;
		int j = 0;
		
		for (i = 0; i < tgraph->count; i++) {
			for (j = 0; j < tgraph->count; j++) {
				// 只要邻接链表中的数据不为1 即可
				if (tgraph->matrix[i][j] != 0) {
					ret++;
				} 
			}
		}	
	}
	
	return ret;
}

// 深度优先搜索 
// 深度优先遍历 从节点 v 开始遍历
// 深度优先类似树的前序遍历，节点一个一个找连接  利用递归实现 
void MGraph_DFS(MGraph* graph, int v, MGraph_Printf* pFunc)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int *visited = (int *)calloc(tgraph->count, sizeof(int));  // 标记空间
	
	int flag = (tgraph != NULL);
	flag = flag && (v >= 0) && (v <= tgraph->count);
	flag = flag && (pFunc != NULL);
	flag = flag && (visited != NULL); 
	
	if (flag) {
		int i = 0;
		
		Recursive_dfs(tgraph, v, visited, pFunc);
		
		for (i = 0; i < tgraph->count; i++) {
			if (!visited[i]) {
				Recursive_dfs(tgraph, i, visited, pFunc);
			}
		}
		
		printf("\n");
	}
	free(visited);
}

// 广度优先搜索 
// 广度优先类似层次遍历  所以需要用到队列 
void MGraph_BFS(MGraph* graph, int v, MGraph_Printf* pFunc)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int *visited = (int *)calloc(tgraph->count, sizeof(int));  // 标记空间
	
	int flag = (tgraph != NULL);
	flag = flag && (v >= 0) && (v <= tgraph->count);
	flag = flag && (pFunc != NULL);
	flag = flag && (visited != NULL); 
	
	if (flag) {
		int i = 0;
		
		Recursive_bfs(tgraph, v, visited, pFunc);
		
		for (i = 0; i < tgraph->count; i++) {
			if (!visited[i]) {
				Recursive_bfs(tgraph, i, visited, pFunc);
			}
		}
		
		printf("\n");
	}
	
	free(visited);
}

// 打印图 
void MGraph_Display(MGraph* graph, MGraph_Printf* pFunc)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	
	if ((tgraph != NULL) && (pFunc != NULL)) {
		int i = 0;
		int j = 0;
		
		// 先打印顶点信息 
		for(i = 0; i < tgraph->count; i++) {
			printf("%d:", i);
			pFunc(tgraph->v[i]);
			printf(" ");
		}	
		
		printf("\n");
		
		// 打印顶点之间的关系 
		for(i = 0; i < tgraph->count; i++) {
			for(j = 0; j< tgraph->count; j++) {
				
				// 直接邻接链表中的数据不为 0 表示有关系 
				if(tgraph->matrix[i][j] != 0) {
					
					// 我们一般用<> 表示有向图
					// 用（） 表示五相图 
					printf("<"); 
					pFunc(tgraph->v[i]);
					printf(",");
					pFunc(tgraph->v[j]);
					printf(", %d", tgraph->matrix[i][j]); // 权值
					printf(">");
					printf(" "); 
				} 
			}
		}
		printf("\n");	 
	}
	
}






