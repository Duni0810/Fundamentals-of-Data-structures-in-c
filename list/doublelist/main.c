#include <stdio.h>
#include <stdlib.h>
#include "Doublelist.h"

typedef struct value {
	doublelist_node_t header;
	int value;	
}value_t;

// 打印链表 
void DoubleList_Print(DoubleList *list)
{
	int i = 0;
	value_t *pv = NULL;
	for (i = 0; i < DoubleList_Length_Get(list); i++) {
		pv = (value_t *)DoubleList_Get(list, i);
		printf("dat：%d \n", pv->value);	
	}
	 
}

// 函数入口 
int main(int argc, char *argv[]) {
	DoubleList *list = DoubleList_Create();
	
	value_t v1; 
	value_t v2; 
	value_t v3; 
	value_t v4; 
	value_t v5; 
	
	v1.value = 1;
	v2.value = 2;
	v3.value = 3;
	v4.value = 4;
	v5.value = 5;
	
	// 头插法 
	DoubleList_Insert(list, (doublelist_node_t *)&v1, 0);
	DoubleList_Insert(list, (doublelist_node_t *)&v2, 0);
	DoubleList_Insert(list, (doublelist_node_t *)&v3, 0);
	
	// 删除第一个元素 
	DoubleList_Delete(list, 1); 
	
	// 打印链表 
	DoubleList_Print(list);
	
	// 清空链表 
	DoubleList_Clear(list);
	
	// 游标测试
	printf("\n======slider test ======\n");
	
	// 尾插法 
	DoubleList_Insert(list, (doublelist_node_t *)&v1, DoubleList_Length_Get(list));
	DoubleList_Insert(list, (doublelist_node_t *)&v2, DoubleList_Length_Get(list));
	DoubleList_Insert(list, (doublelist_node_t *)&v3, DoubleList_Length_Get(list));
	DoubleList_Insert(list, (doublelist_node_t *)&v4, DoubleList_Length_Get(list));
	DoubleList_Insert(list, (doublelist_node_t *)&v5, DoubleList_Length_Get(list));
	
	// 打印链表 
	DoubleList_Print(list);
	
	DoubleList_Reset(list);
	
	value_t *pv = (value_t *)DoubleList_Current(list);
	printf("1.slider : %d \n", pv->value);
	
	// 后移 2 位 上移一位 
	DoubleList_Next(list);
	DoubleList_Next(list);
	DoubleList_Pre(list);
	 
	pv = (value_t *)DoubleList_Current(list);
	printf("2.slider : %d \n", pv->value);
		
	DoubleList_Destroy(list);

	return 0;
}
