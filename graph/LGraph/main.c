#include <stdio.h>
#include <stdlib.h>
#include "lgraph.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void print_data(LVertex* v)
{
    printf("%s", (char*)v);
}

int main(int argc, char *argv[]) {
	
    LVertex* v[] = {"A", "B", "C", "D", "E", "F"};
    LGraph* graph = LGraph_Create(v, 6);
    
    LGraph_AddEdge(graph, 0, 1, 1);
    LGraph_AddEdge(graph, 0, 2, 1);
    LGraph_AddEdge(graph, 0, 3, 1);
    LGraph_AddEdge(graph, 1, 5, 1);
    LGraph_AddEdge(graph, 1, 4, 1);
    LGraph_AddEdge(graph, 2, 1, 1);
    LGraph_AddEdge(graph, 3, 4, 1);
    LGraph_AddEdge(graph, 4, 2, 1);
    
    LGraph_Display(graph, print_data);
    
    LGraph_DFS(graph, 0, print_data);
    LGraph_BFS(graph, 0, print_data);
    
    LGraph_Destroy(graph);
	return 0;
}
