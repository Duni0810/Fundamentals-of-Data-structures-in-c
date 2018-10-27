#include <stdio.h>
#include <stdlib.h>
#include "btree.h"


struct Node
{
    BTreeNode header;
    char v;
};

void printf_data(BTreeNode* node)
{
    if( node != NULL )
    {
        printf("%c", ((struct Node*)node)->v);
    }
}

int main(int argc, char *argv[])
{
    BTree* tree = BTree_Create();
    
    struct Node n1 = {{NULL, NULL}, 'A'};
    struct Node n2 = {{NULL, NULL}, 'B'};
    struct Node n3 = {{NULL, NULL}, 'C'};
    struct Node n4 = {{NULL, NULL}, 'D'};
    struct Node n5 = {{NULL, NULL}, 'E'};
    struct Node n6 = {{NULL, NULL}, 'F'};
    
    BTree_Insert(tree, (BTreeNode*)&n1, 0, 0, 0);		// A 
    BTree_Insert(tree, (BTreeNode*)&n2, 0x00, 1, 0);	// B
    BTree_Insert(tree, (BTreeNode*)&n3, 0x01, 1, 0);	// C
    BTree_Insert(tree, (BTreeNode*)&n4, 0x00, 2, 0);	// D
    BTree_Insert(tree, (BTreeNode*)&n5, 0x00, 1, 0);	// E
    BTree_Insert(tree, (BTreeNode*)&n6, 0x02, 3, 0);	// F

    BTree_Display(tree, printf_data, 4, '-');
    
    printf("Height: %d\n", BTree_Height(tree));
    printf("Degree: %d\n", BTree_Degree(tree));
    printf("Count: %d\n", BTree_Count(tree));
    printf("Position At (0x02, 2): %c\n", ((struct Node*)BTree_Get(tree, 0x02, 2))->v);
    
    BTree_Delete(tree, 0x00, 1);
    
    printf("After Delete B: \n");
    printf("Height: %d\n", BTree_Height(tree));
    printf("Degree: %d\n", BTree_Degree(tree));
    printf("Count: %d\n", BTree_Count(tree));
    printf("Full Tree: \n");
    BTree_Display(tree, printf_data, 4, '-');
    
    BTree_Clear(tree);
    
    printf("After Clear: \n");
    printf("Height: %d\n", BTree_Height(tree));
    printf("Degree: %d\n", BTree_Degree(tree));
    printf("Count: %d\n", BTree_Count(tree));
    
    BTree_Display(tree, printf_data, 4, '-');
    
    BTree_Destroy(tree);
    
	return 0;
}


















