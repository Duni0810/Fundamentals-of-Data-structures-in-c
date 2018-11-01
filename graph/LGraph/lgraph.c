#include <stdio.h>
#include <malloc.h>
#include "list.h"
#include "lgraph.h"
#include "link_queue.h"


/**
 * ͼ���ȴ���һ�������Ķ���  Ȼ���ж��Ƿ���ӵ����֮�����ϵ���������õ����ڽ�����ķ�ʽ�����ڶ�������ٵĽṹ������Ч�ʻ���ͦ�ߵ� 
 *
 *
 */
 
// ͷ�ڵ���Ϣ 
typedef struct _tag_LGraph {
	int count; 		// �������� 
	LVertex **v;	// ��������
	LinkList **la;	// �ڽ�������Ϣ  ���ڽӾ������� 
} LGraph_t;
 
// �����ڵ��ڽ�������Ϣ 
typedef struct _tag_ListNode {
 	LinkListNode_t header;	//	����ڵ� 
 	int				v;		// �ڵ��±� 
 	int 			w;		// Ȩֵ 
 } ListNode_t; 
 

static void Recursive_dfs(LGraph_t* graph, int v, int visited[], LGraph_Printf* pFunc)
{
	int i = 0;
	pFunc(graph->v[v]); // ��ӡ������Ϣ 
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
    	// ��� 
    	LinkQueue_Append(queue, graph->v + v);
    	
    	// ��� 
    	visited[v] = 1;
    	
    	//  �ӳ� 
    	while(LinkQueue_Length(queue) > 0) {
    		int i = 0;
			
			// ���� 
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

// ���� n �����㣬���ݷֱ�Ϊ v��ͼ 
LGraph* LGraph_Create(LVertex **v, int n)
{
	LGraph_t *ret = NULL;
	int flag = 1;
	
	// ��������������0 
	if ((v != NULL) && (n > 0)) {
		// ���붥����Ϣ�洢�ռ� 
		ret = (LGraph_t *)malloc(sizeof(LGraph_t));
		
		if(ret != NULL) {
			ret->count = n;
			ret->v = (LVertex **)calloc(n, sizeof(LVertex *)); // ������Ϣ
			ret->la = (LinkList **)calloc(n, sizeof(LinkList *));
			
			flag = (ret->la != NULL) && (ret->v != NULL);
			
			if (flag) {
				int i = 0;
				
				for (i = 0; i < n; i++) { // ��ֵ�ڵ���Ϣ 
					ret->v[i] = v[i]; 
				}
				
				for (i = 0; (i < n) && flag; i++) { // ���� n ������ 
					 flag = flag && ((ret->la[i] = LinkList_Create()) != NULL); 
				} 	 
			}
		} 
		// ֻҪ��������ʧ�� ���ǲ��ɹ� ���������нڵ� 
		if (!flag) {
			if (ret->la != NULL) {
				int i = 0;
				
				// ����ͷſռ�
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

// �ݻ�ͼ 
void LGraph_Destroy(LGraph* graph)
{
	LGraph_t *tgraph = (LGraph_t *)graph;
	LGraph_Clear(tgraph);
	
	if (tgraph != NULL) {
		int i = 0;
		// ����ͷſռ�
		for (i = 0; i < tgraph->count; i++) {
			LinkList_Destroy(tgraph->la[i]);
		} 
		
		free(tgraph->la);
		free(tgraph->v);
		free(tgraph);
	}
}

// ���ͼ ���ڽ������е�������� 
void LGraph_Clear(LGraph* graph)
{
	LGraph_t *tgraph = (LGraph_t *)graph;
	
	if(tgraph != NULL) {
		int i = 0;
		
		for (i = 0; i < tgraph->count; i++) {
			
			// �ͷ����пռ� 
			while (LinkList_Length_Get(tgraph->la[i]) > 0) {
				free(LinkList_Delete(tgraph->la[i], 0));
			}
		}
	}
}

// ��Ӷ���֮����ϵ��Ȩ 
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
		// ��ֵ 
		node->v = v2;
		node->w = w;
		
		// ������Ӧλ�õ����� ��ͷλ�� 
		LinkList_Insert(tgraph->la[v1], (LinkListNode_t *)node, 0);
	}

	return ret;
} 

// �Ƴ���  ����Ȩֵ 
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
		
		// ������Ӧλ�������� 
		for (i = 0; i < LinkList_Length_Get(tgraph->la[v1]); i++) {
			node = (ListNode_t *)LinkList_Get(tgraph->la[v1], i);
			
			if(node->v == v2) {
				ret = node->w;  // ����Ȩֵ
				LinkList_Delete(tgraph->la[v1], i); // ��������ɾ�� 
				free(node); // �ͷſռ� 
				
				break;
			}
		}
	}

	return ret;
} 

// ��ȡ v1->v2 ��Ȩ  
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

// ��ȡĳ������Ķ� 
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
				if (node->v == v) {  // ��� ��ȡ 
					ret++;
				}
			}
		}
		ret += LinkList_Length_Get(tgraph->la[v]);
	}
	
}

// ��ȡͼ�Ķ����� 
int LGraph_VertexCount(LGraph* graph)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	int ret = 0;
	
	// ֱ�ӷ���ͷ�ڵ���Ϣ 
	if (tgraph != NULL) {
		ret = tgraph->count;
	}
	return ret;
}

// ��ȡͼ�ı��� 
int LGraph_EdgeCount(LGraph* graph)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	int ret = 0;
	
	if(tgraph != NULL) {
		int i = 0;
		
		// ��������������� 
		for (i = 0; i < tgraph->count; i++) {
			ret += LinkList_Length_Get(tgraph->la[i]);
		}
	} 
	
	return ret;
} 

// ������� 
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

// ������� 
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

// ��ʾ 
void LGraph_Display(LGraph* graph, LGraph_Printf* pFunc)
{
	LGraph_t *tgraph = (LGraph_t*)graph;
	
	if((tgraph != NULL) && (pFunc != NULL)) {
		int i = 0;
		int j = 0;
		
		// ��ӡ������Ϣ 
		for(i = 0; i < tgraph->count; i++) {
            printf("%d:", i);
            pFunc(tgraph->v[i]);
            printf(" ");
		}
		printf("\n");
		
		// ��ӡ����Ϣ
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
 
 
 
 
 
 
 
