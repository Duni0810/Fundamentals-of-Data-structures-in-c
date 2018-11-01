#include <stdio.h>
#include <malloc.h>
#include "list.h"
#include "lgraph.h"
#include "link_queue.h"


/**
 * 图是先创建一定数量的顶点  然后将判断是否添加点与点之间的联系，这里利用的是邻接链表的方式，对于定点个数少的结构，他的效率还是挺高的 
 *
 *
 */
 
// 头节点信息 
typedef struct _tag_LGraph {
	int count; 		// 顶点数量 
	LVertex **v;	// 定点数据
	LinkList **la;	// 邻接链表信息  和邻接矩阵类似 
} LGraph_t;
 
// 各个节点邻接链表信息 
typedef struct _tag_ListNode {
 	LinkListNode_t header;	//	链表节点 
 	int				v;		// 节点下标 
 	int 			w;		// 权值 
 } ListNode_t; 
 

static void Recursive_dfs(LGraph_t* graph, int v, int visited[], LGraph_Printf* pFunc)
{
	int i = 0;
	pFunc(graph->v[v]); // 打印顶点信息 
    visited[v] = 1;
    
    printf(",");
    
    for(i = 0; i < LinkList_Length_Get(graph->la[v]); i++) {
    	ListNode_t *node = (ListNode_t *)LinkList_Get(graph->la[v], i);
    	
    	if (!visited[node->v]) {
    		Recursive_dfs(graph, node->v, visited, pFunc);
		}
	} 
    
}

static void Recursive_bfs(LGraph_t* graph, int v, int visited[], LGraph_Printf* pFunc)
{
    LinkQueue* queue = LinkQueue_Create();
    if (queue != NULL) {
    	// 入队 
    	LinkQueue_Append(queue, graph->v + v);
    	
    	// 标记 
    	visited[v] = 1;
    	
    	//  队长 
    	while(LinkQueue_Length(queue) > 0) {
    		int i = 0;
			
			// 出队 
			v = (LVertex**)LinkQueue_Poll(queue) - graph->v; 
			pFunc(graph->v[v]);
			
			printf(",");

			for (i = 0; i < LinkList_Length_Get(graph->la[v]); i++) {
    			ListNode_t *node = (ListNode_t *)LinkList_Get(graph->la[v], i);
    			
    			if(!visited[node->v]) {
    				LinkQueue_Append(queue, graph->v + node->v);
    				visited[node->v] = 1;
				}
			}
		}
	}
    LinkQueue_Destroy(queue);
}

// 创建 n 个顶点，数据分别为 v的图 
LGraph* LGraph_Create(LVertex **v, int n)
{
	LGraph_t *ret = NULL;
	int flag = 1;
	
	// 定点个数必须大于0 
	if ((v != NULL) && (n > 0)) {
		// 申请顶点信息存储空间 
		ret = (LGraph_t *)malloc(sizeof(LGraph_t));
		
		if(ret != NULL) {
			ret->count = n;
			ret->v = (LVertex **)calloc(n, sizeof(LVertex *)); // 顶点信息
			ret->la = (LinkList **)calloc(n, sizeof(LinkList *));
			
			flag = (ret->la != NULL) && (ret->v != NULL);
			
			if (flag) {
				int i = 0;
				
				for (i = 0; i < n; i++) { // 赋值节点信息 
					ret->v[i] = v[i]; 
				}
				
				for (i = 0; (i < n) && flag; i++) { // 创建 n 个链表 
					 flag = flag && ((ret->la[i] = LinkList_Create()) != NULL); 
				} 	 
			}
		} 
		// 只要创建链表失败 就是不成功 得销毁所有节点 
		if (!flag) {
			if (ret->la != NULL) {
				int i = 0;
				
				// 逐个释放空间
				for (i = 0; i < n; i++) {
					LinkList_Destroy(ret->la[i]);
				} 
			}
			
			free(ret->la);
			free(ret->v);
			free(ret);
			
			ret = NULL;	
		} 
	}
	
	return ret; 
} 

// 摧毁图 
void LGraph_Destroy(LGraph* graph)
{
	LGraph_t *tgraph = (LGraph_t *)graph;
	LGraph_Clear(tgraph);
	
	if (tgraph != NULL) {
		int i = 0;
		// 逐个释放空间
		for (i = 0; i < tgraph->count; i++) {
			LinkList_Destroy(tgraph->la[i]);
		} 
		
		free(tgraph->la);
		free(tgraph->v);
		free(tgraph);
	}
}

// 清空图 将邻接链表中的数据清空 
void LGraph_Clear(LGraph* graph)
{
	LGraph_t *tgraph = (LGraph_t *)graph;
	
	if(tgraph != NULL) {
		int i = 0;
		
		for (i = 0; i < tgraph->count; i++) {
			
			// 释放所有空间 
			while (LinkList_Length_Get(tgraph->la[i]) > 0) {
				free(LinkList_Delete(tgraph->la[i], 0));
			}
		}
	}
}

// 添加顶点之间联系和权 
int LGraph_AddEdge(LGraph* graph, int v1, int v2, int w)
{
	LGraph_t *tgraph = (LGraph_t *)graph;
	ListNode_t * node = NULL;
	int ret = (tgraph != NULL);
	
	ret = ret && (v1 >= 0) && (v1 <= tgraph->count);
	ret = ret && (v2 >= 0) && (v2 <= tgraph->count);
	ret = ret && (w > 0);
	ret = ret && ((node = (ListNode_t *)malloc(sizeof(ListNode_t))) != NULL);  
	
	if (ret) {
		// 赋值 
		node->v = v2;
		node->w = w;
		
		// 插入相应位置的链表 表头位置 
		LinkList_Insert(tgraph->la[v1], (LinkListNode_t *)node, 0);
	}

	return ret;
} 

// 移除边  返回权值 
int LGraph_RemoveEdge(LGraph* graph, int v1, int v2)
{
	LGraph_t *tgraph = (LGraph_t *)graph;
	int ret = 0;
	int flag = (tgraph != NULL);
	
	flag = flag && (v1 >= 0) && (v1 <= tgraph->count);
	flag = flag && (v2 >= 0) && (v2 <= tgraph->count);

	if (flag) {
		ListNode_t * node = NULL;
		int i = 0;
		
		// 遍历对应位置链表长度 
		for (i = 0; i < LinkList_Length_Get(tgraph->la[v1]); i++) {
			node = (ListNode_t *)LinkList_Get(tgraph->la[v1], i);
			
			if(node->v == v2) {
				ret = node->w;  // 保持权值
				LinkList_Delete(tgraph->la[v1], i); // 从链表中删除 
				free(node); // 释放空间 
				
				break;
			}
		}
	}

	return ret;
} 

// 获取 v1->v2 的权  
int LGraph_GetEdge(LGraph* graph, int v1, int v2)
{
	LGraph_t *tgraph = (LGraph_t *)graph;
	int ret = 0;
	int flag = (tgraph != NULL);
	
	flag = flag && (v1 >= 0) && (v1 <= tgraph->count);
	flag = flag && (v2 >= 0) && (v2 <= tgraph->count);
	if (flag) {
		ListNode_t * node = NULL;
		int i = 0;
		
		for (i = 0; i < LinkList_Length_Get(tgraph->la[v1]); i++) {
			node = (ListNode_t *)LinkList_Get(tgraph->la[v1], i);
			
			if (node->v == v2) {
				ret = node->w;
				break;
			}
		}
	} 
	
	return ret;
}

// 获取某个顶点的度 
int LGraph_TD(LGraph* graph, int v)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	int flag = (tgraph != NULL) && (v >= 0) && (v <= tgraph->count);
	int ret = 0;
	
	if (flag) {
		int i = 0;
		int j = 0;
		
		for (i = 0; i < tgraph->count; i++) {
			for(j = 0; j < LinkList_Length_Get(tgraph->la[i]); j++) {
				ListNode_t *node = (ListNode_t *)LinkList_Get(tgraph->la[i], j);
				if (node->v == v) {  // 入度 获取 
					ret++;
				}
			}
		}
		ret += LinkList_Length_Get(tgraph->la[v]);
	}
	
}

// 获取图的顶点数 
int LGraph_VertexCount(LGraph* graph)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	int ret = 0;
	
	// 直接返回头节点信息 
	if (tgraph != NULL) {
		ret = tgraph->count;
	}
	return ret;
}

// 获取图的边数 
int LGraph_EdgeCount(LGraph* graph)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	int ret = 0;
	
	if(tgraph != NULL) {
		int i = 0;
		
		// 叠加数据链表个数 
		for (i = 0; i < tgraph->count; i++) {
			ret += LinkList_Length_Get(tgraph->la[i]);
		}
	} 
	
	return ret;
} 

// 深度搜索 
void LGraph_DFS(LGraph* graph, int v, LGraph_Printf* pFunc)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	int *visited = (int *)calloc(tgraph->count, sizeof(int));
	int flag = (tgraph != NULL) && (pFunc != NULL);
	flag = flag && (v >= 0) && (v < tgraph->count);
	flag = flag && (visited != NULL);
	
	if(flag) {
		int i = 0;
		Recursive_dfs(tgraph, v, visited, pFunc);
		
		for(i = 0; i < tgraph->count; i++) {
			if (!visited[i]) {
				Recursive_dfs(tgraph, i, visited, pFunc);
			}
		}
		printf("\n");
	}

	free(visited); 
}

// 广度搜索 
void LGraph_BFS(LGraph* graph, int v, LGraph_Printf* pFunc)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	
	int *visited = (int *)calloc(tgraph->count, sizeof(int));
	int flag = (tgraph != NULL) && (pFunc != NULL);
	
	flag = flag && (v >= 0) && (v < tgraph->count);
	flag = flag && (visited != NULL);
	
	if(flag) {
		int i = 0;
		Recursive_bfs(tgraph, v, visited, pFunc);
		
		for(i = 0; i < tgraph->count; i++) {
			if (!visited[i]) {
				Recursive_bfs(tgraph, i, visited, pFunc);
			}
		}
		printf("\n");
	}

	free(visited); 
}

// 显示 
void LGraph_Display(LGraph* graph, LGraph_Printf* pFunc)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	
	if((tgraph != NULL) && (pFunc != NULL)) {
		int i = 0;
		int j = 0;
		
		// 打印顶点信息 
		for(i = 0; i < tgraph->count; i++) {
            printf("%d:", i);
            pFunc(tgraph->v[i]);
            printf(" ");
		}
		printf("\n");
		
		// 打印边信息
		for(i = 0; i < tgraph->count; i++) {
			for (j = 0; j < LinkList_Length_Get(tgraph->la[i]); j++) {
				ListNode_t *node = (ListNode_t *)LinkList_Get(tgraph->la[i], j);
				printf("<");
                pFunc(tgraph->v[i]);
                printf(", ");
                pFunc(tgraph->v[node->v]);
                printf(", %d", node->w);
                printf(">");
                printf(" ");     
			}	
		} 
		printf("\n");
	} 
} 
 
 
 
 
 
 
 
