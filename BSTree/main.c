#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

struct Node
{
    BSTreeNode header;
    char v;
};

void printf_data(BSTreeNode* node)
{
    if( node != NULL )
    {
        printf("%c", ((struct Node*)node)->v);
    }
}

int compare_key(BSKey* k1, BSKey* k2)
{
    return (int)k1 - (int)k2;
}

int main(int argc, char *argv[])
{
    BSTree* tree = BSTree_Create();
    
    struct Node n1 = {{(BSKey*)1, NULL, NULL}, 'A'};
    struct Node n2 = {{(BSKey*)2, NULL, NULL}, 'B'};
    struct Node n3 = {{(BSKey*)3, NULL, NULL}, 'C'};
    struct Node n4 = {{(BSKey*)4, NULL, NULL}, 'D'};
    struct Node n5 = {{(BSKey*)5, NULL, NULL}, 'E'};
    struct Node n6 = {{(BSKey*)6, NULL, NULL}, 'F'};
    
    BSTree_Insert(tree, (BSTreeNode*)&n4, compare_key);
    BSTree_Insert(tree, (BSTreeNode*)&n1, compare_key);
    BSTree_Insert(tree, (BSTreeNode*)&n3, compare_key);
    BSTree_Insert(tree, (BSTreeNode*)&n6, compare_key);
    BSTree_Insert(tree, (BSTreeNode*)&n2, compare_key);
    BSTree_Insert(tree, (BSTreeNode*)&n5, compare_key);
    
    printf("Height: %d\n", BSTree_Height(tree));
    printf("Degree: %d\n", BSTree_Degree(tree));
    printf("Count: %d\n", BSTree_Count(tree));
    printf("Search Key 5: %c\n", ((struct Node*)BSTree_Get(tree, (BSKey*)5, compare_key))->v);
    printf("Full Tree: \n");
    
    BSTree_Display(tree, printf_data, 4, '-');
    
    BSTree_Delete(tree, (BSKey*)4, compare_key);
    
    printf("After Delete Key 4: \n");
    printf("Height: %d\n", BSTree_Height(tree));
    printf("Degree: %d\n", BSTree_Degree(tree));
    printf("Count: %d\n", BSTree_Count(tree));
    printf("Full Tree: \n");
    
    BSTree_Display(tree, printf_data, 4, '-');
    
    BSTree_Destroy(tree);
    
	return 0;
}
