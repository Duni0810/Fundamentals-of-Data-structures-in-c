#include <stdio.h>
#include <malloc.h>
#include "graph.h"
#include "link_queue.h" 

//  ͷָ����Ϣ 
typedef struct _tag_MGraph {
	int count;  	// ������
	MVertex **v; 	// �����������
	int **matrix; 	// �ڽӾ��� 
}MGraph_t; 


static void Recursive_dfs(MGraph_t *graph, int v, int visit[], MGraph_Printf* pFunc)
{
	int i = 0;
	
	pFunc(graph->v[v]); // ��ӡ����
	visit[v] = 1;		// ����Ѷ� 
	printf(",");
	
	for(i = 0; i < graph->count; i++) {
		if(!visit[i] && (graph->matrix[v][i])) {
			Recursive_dfs(graph, i, visit, pFunc);
		}
	} 
}

static void Recursive_bfs(MGraph_t *graph, int v, int visit[], MGraph_Printf* pFunc)
{
	LinkQueue *queue = LinkQueue_Create(); // ������� 
	
	if (queue != NULL) {
		// ��Ϊ V ������0 ����ʵ�ֵ����ݽṹ��֧��0 
		//�����������Ǽ��� һ����ַ ֮�������ȥ������ 
		LinkQueue_Append(queue, graph->v + v); 
		
		visit[v] = 1;
		
		while (LinkQueue_Length(queue) > 0) {
			int i = 0;
			
			// ���м�ȥ֮ǰ��ӵ����� 
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



// ���� n�������ͼ  ��������Ϊ v 
MGraph *MGraph_Create(MVertex **v, int n)
{
	MGraph_t *ret = NULL;
	
	if ((NULL != v) && (n > 0)) { //��Ϊͼ������ǿռ��� 
		ret = (MGraph_t *)malloc(sizeof(MGraph_t));
		if (ret != NULL) {
			ret->count = n;
			
			int *p = NULL; 
			// �������ݱ���ڵ�ռ� 
			ret->v = (MVertex **)malloc(sizeof(MVertex *) * n);
			
			//��̬�����ά����ռ� ���ڱ����ڽ����� 
			ret->matrix = (int **)malloc(sizeof(int *) * n);
			p = (int *)calloc(n * n, sizeof(int)); 
			
			// �Ϸ����ж� 
			if ((NULL != ret->v) && (NULL != ret->matrix) && (NULL != p)) {
				int i = 0;
				
				// ������ά����
				for(i = 0; i < n; i++) {
					ret->v[i] = v[i]; // ���ݱ��� 
					ret->matrix[i] = p + i * n; // ������ά���� 
				} 
				
			} else { // ʧ�� 
				free(p);
				free(ret->matrix);
				free(ret->v); 
				free(ret);
			}
		}
	}

	return ret;
} 

//  �ݻ�ͼ 
void MGraph_Destroy(MGraph* graph)
{
	MGraph_t *ret = (MGraph_t *)graph;
	
	if (ret != NULL) {
		free(ret->v);			// ��ն�������ָ�� 
		free(ret->matrix[0]);	// ��������� 
		free(ret->matrix);		// ����ڽ����� 
		free(ret);				// ������ͷ�ڵ����� 
	} 
}

// ���ͼ Ҳ������ն���֮������� 
void MGraph_Clear(MGraph* graph)
{
	MGraph_t *ret = (MGraph_t *)graph;
	
	if(ret != NULL) {
		int i = 0;
		int j = 0;
		
		// ���ڽӾ���������� 
		for (i = 0; i < ret->count; i++) {
			for (j = 0; j < ret->count; j++) {
				ret->matrix[i][j] = 0;
			}
		}
	} 
}

// ��Ӷ���֮������� ��������ʹ�õ�������ͼ 
int MGraph_AddEdge(MGraph* graph, int v1, int v2, int w)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int ret = (tgraph != NULL);
	
	ret = ret && (v1 >= 0) && (v1 <= tgraph->count);
	ret = ret && (v2 >= 0) && (v2 <= tgraph->count);
	ret = ret && (w >= 0);
	
	// ����ֻ��Ҫ���ڽӾ�����Ӧ��λ�õ�ֵ��ΪȨֵ�Ϳ����� 
	if (ret) {
		tgraph->matrix[v1][v2] = w;
	}
	
	return ret;
} 

// �Ƴ��������ϵ 
int MGraph_RemoveEdge(MGraph* graph, int v1, int v2)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int ret = MGraph_GetEdge(graph, v1, v2);
	
	// ����ֻ��Ҫ���ڽӾ�����Ӧ��λ�õ�ֵ��ΪȨֵ�Ϳ����� 
	if (ret != 0) {
		tgraph->matrix[v1][v2] = 0;
	}
	
	return ret;
} 

// ��ȡ��������֮���Ȩֵ  v1->v2 
int MGraph_GetEdge(MGraph* graph, int v1, int v2)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int flag = (tgraph != NULL);
	int ret = 0;
	
	flag = flag && (v1 >= 0) && (v1 <= tgraph->count);
	flag = flag && (v2 >= 0) && (v2 <= tgraph->count);
	
	// ����ֻ��Ҫ���ڽӾ�����Ӧ��λ�õ�ֵ��ΪȨֵ�Ϳ����� 
	if (flag) {
		ret = tgraph->matrix[v1][v2];
	}
	
	return ret;
}

// ��ȡ����Ķ�  ����Ķ� = ��� + ���� 
int MGraph_TD(MGraph* graph, int v)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int flag = (tgraph != NULL);
	int ret = 0;
	
	flag = flag && (v >= 0) && (v < tgraph->count); 
	
	if (flag) {
		int i = 0;
		
		// ����������Ϳ��� 
		for (i = 0; i < tgraph->count; i++) {
			// ����
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

// ��ȡ������ 
int MGraph_VertexCount(MGraph* graph)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int ret = 0;
	
	// ֱ�ӷ���ͷ�ڵ���Ϣ������ 
	if (tgraph != NULL) {
		ret = tgraph->count;
	} 
	return ret;
}

// ��ȡͼ�е��������ӱ��� 
int MGraph_EdgeCount(MGraph* graph)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int ret = 0;
	
	if (tgraph != NULL) {
		int i = 0;
		int j = 0;
		
		for (i = 0; i < tgraph->count; i++) {
			for (j = 0; j < tgraph->count; j++) {
				// ֻҪ�ڽ������е����ݲ�Ϊ1 ����
				if (tgraph->matrix[i][j] != 0) {
					ret++;
				} 
			}
		}	
	}
	
	return ret;
}

// ����������� 
// ������ȱ��� �ӽڵ� v ��ʼ����
// ���������������ǰ��������ڵ�һ��һ��������  ���õݹ�ʵ�� 
void MGraph_DFS(MGraph* graph, int v, MGraph_Printf* pFunc)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int *visited = (int *)calloc(tgraph->count, sizeof(int));  // ��ǿռ�
	
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

// ����������� 
// ����������Ʋ�α���  ������Ҫ�õ����� 
void MGraph_BFS(MGraph* graph, int v, MGraph_Printf* pFunc)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	int *visited = (int *)calloc(tgraph->count, sizeof(int));  // ��ǿռ�
	
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

// ��ӡͼ 
void MGraph_Display(MGraph* graph, MGraph_Printf* pFunc)
{
	MGraph_t *tgraph = (MGraph_t *)graph; 
	
	if ((tgraph != NULL) && (pFunc != NULL)) {
		int i = 0;
		int j = 0;
		
		// �ȴ�ӡ������Ϣ 
		for(i = 0; i < tgraph->count; i++) {
			printf("%d:", i);
			pFunc(tgraph->v[i]);
			printf(" ");
		}	
		
		printf("\n");
		
		// ��ӡ����֮��Ĺ�ϵ 
		for(i = 0; i < tgraph->count; i++) {
			for(j = 0; j< tgraph->count; j++) {
				
				// ֱ���ڽ������е����ݲ�Ϊ 0 ��ʾ�й�ϵ 
				if(tgraph->matrix[i][j] != 0) {
					
					// ����һ����<> ��ʾ����ͼ
					// �ã��� ��ʾ����ͼ 
					printf("<"); 
					pFunc(tgraph->v[i]);
					printf(",");
					pFunc(tgraph->v[j]);
					printf(", %d", tgraph->matrix[i][j]); // Ȩֵ
					printf(">");
					printf(" "); 
				} 
			}
		}
		printf("\n");	 
	}
	
}






