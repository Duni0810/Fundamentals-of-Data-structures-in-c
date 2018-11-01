#include <stdio.h>
#include <stdlib.h>
#include "graph.h" 
#include <string.h>

// 打印函数定义 
void print_data(MVertex* v)
{
    printf("%s", (char *)v);
}

int main(int argc, char *argv[]) {
	
	// 定点数据 
	MVertex* v[] = {"A", "B", "C", "D", "E", "F"};
	
	// 初始化定点 
    MGraph* graph = MGraph_Create(v, 6);
    
    MGraph_AddEdge(graph, 0, 1, 1);
    MGraph_AddEdge(graph, 0, 2, 1);
    MGraph_AddEdge(graph, 0, 3, 1);
    MGraph_AddEdge(graph, 1, 5, 1);
    MGraph_AddEdge(graph, 1, 4, 2);
    MGraph_AddEdge(graph, 2, 1, 1);
    MGraph_AddEdge(graph, 3, 4, 1);
    MGraph_AddEdge(graph, 4, 2, 1);
    
    MGraph_Display(graph, print_data);
    
    //MGraph_DFS(graph, 0, print_data);
    
    MGraph_BFS(graph, 0, print_data);
    MGraph_Destroy(graph);
}
