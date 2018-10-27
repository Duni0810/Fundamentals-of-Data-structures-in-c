#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	//printf("void *%d ,int :%d  long: %d int * :%d\r\n",sizeof(void *),sizeof(int),sizeof(long), sizeof(int *));

	int i = 0;
	int j = 1;
	int k = 2;
	
	int index = 0;

	StaticList *list = StaticList_Create(10); 
	
	StaticList_Insert(list, &i, 0);
	StaticList_Insert(list, &j, 0);
	StaticList_Insert(list, &k, 0);
	
	for(index = 0; index < StaticList_Length_Get(list); index++)
    {
        unsigned long long * p = (unsigned long long * )StaticList_Get(list, index);
//        
//        printf("%d\n", *p);
    }
    
	StaticList_Clear(list);     // 清空链表
	 
	StaticList_Destroy(list);   // 摧毁链表 释放内存空间 
	return 0;
} 
