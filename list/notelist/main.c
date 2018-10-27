#include <stdio.h>
#include <stdlib.h>
#include "list.h" 

struct Value {
	LinkListNode_t header;
	int            data; 
}; 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int i = 0;
	LinkList *list = LinkList_Create(); /* 创建头节点 */ 
	
    struct Value v1;
    struct Value v2;
    struct Value v3;
    struct Value v4;
    struct Value v5;
    
    v1.data = 1;
    v2.data = 2;
    v3.data = 3;
    v4.data = 4;
    v5.data = 5;
    LinkList_Insert(list, (LinkListNode_t *)&v1, LinkList_Length_Get(list));
    LinkList_Insert(list, (LinkListNode_t *)&v2, LinkList_Length_Get(list));
    LinkList_Insert(list, (LinkListNode_t *)&v3, LinkList_Length_Get(list));
    LinkList_Insert(list, (LinkListNode_t *)&v4, LinkList_Length_Get(list));
    LinkList_Insert(list, (LinkListNode_t *)&v5, LinkList_Length_Get(list));

    LinkList_Delete(list, 2);
    for(i = 0; i < LinkList_Length_Get(list); i++)
    {
        struct Value* pv = (struct Value*)LinkList_Get(list, i);  /* 首地址赋值，因为他们的首地址是一样的 */  
        
        printf("%d \n", pv->data);
    }
    
//        while( LinkList_Length_Get(list) > 0 )
//    {
//        struct Value* pv = (struct Value *)LinkList_Delete(list, 0);
//        
//        printf("%d\n", pv->data);
//    }
    
    LinkList_Destroy(list);
	
	return 0;
}
