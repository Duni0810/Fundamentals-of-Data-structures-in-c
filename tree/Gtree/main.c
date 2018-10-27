#include <stdio.h>
#include <stdlib.h>
#include "GTree.h"

void printf_data(GTreeData *data)
{
	printf("%c", (int)data);	
}


int main(int argc, char *argv[]) {
	
	GTree* tree = GTree_Create();
    int i = 0;

    GTree_Insert(tree, (GTreeData*)'A', -1);
    GTree_Insert(tree, (GTreeData*)'B', 0);
    GTree_Insert(tree, (GTreeData*)'C', 0);
    GTree_Insert(tree, (GTreeData*)'D', 0);
    GTree_Insert(tree, (GTreeData*)'E', 1);
    GTree_Insert(tree, (GTreeData*)'F', 1);
    GTree_Insert(tree, (GTreeData*)'H', 3);
    GTree_Insert(tree, (GTreeData*)'I', 3);
    GTree_Insert(tree, (GTreeData*)'J', 3);
	
	printf("Tree Height: %d\n", GTree_Hight_Get(tree));
    printf("Tree Degree: %d\n", GTree_Degree_Get(tree));
  	printf("index:%d",GTree_Search(tree, (GTreeData *)'J', printf_data));
    
    printf("Full Tree:\n");
	GTree_Display(tree, printf_data, 2, '-');
	
	printf("^^^^^^^ \n");
	for (i = 0; i < GTree_Count_Get(tree); i++) {
		printf("%c \n", (int)GTree_Get(tree, i));
	} 
	
	// É¾³ýº¯Êý²âÊÔ 
	GTree_Delete(tree, 2);
	printf("***** \n");
	GTree_Display(tree, printf_data, 2, '-');
	
	printf("root :%c \n", (int)GTree_Root_Get(tree));
	
	
	
	
	GTree_Clear(tree); 
	GTree_Destroy(tree);
	
	return 0;
}
