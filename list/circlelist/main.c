#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct value {
	circlelist_node_t header;
	int               value;	
} value_t;

// 打印链表 
void CircleList_print(CircleList *list)
{
	int i = 0;
	// 遍历结构体 
	for (i = 0; i < CircleList_Length_Get(list); i++) {
		value_t *pv = (value_t *)CircleListNode_Get(list, i);
		printf("data:%d \n", pv->value);
	} 
} 


// 函数测试程序 
int test1() 
{
	printf("\n*************test1*****************\n");
	// 创建链表（init） 
	CircleList *list = CircleList_Creat();
	
	value_t v1;
	value_t v2;
	value_t v3;
	value_t v4;
	value_t v5;
	value_t v6;
	value_t v7;
	value_t v8;
	
	v1.value = 1;
	v2.value = 2;
	v3.value = 3;
	v4.value = 4;
	v5.value = 5;
	v6.value = 6;
	v7.value = 7;
	v8.value = 8;
	
	// 头插法 
	CircleList_Insert(list, (circlelist_node_t *)&v1, 0);
	CircleList_Insert(list, (circlelist_node_t *)&v2, 0);
	CircleList_Insert(list, (circlelist_node_t *)&v3, 0);
	CircleList_Insert(list, (circlelist_node_t *)&v4, 0);
	
	// 打印结构体成员 
	CircleList_print(list);
	
	// 删除第一个元素 
    CircleList_Delete(list, 0);

    CircleList_print(list);

    printf("===========slider test===============\n");
    CircleList_clear(list);
    
    CircleList_Insert(list, (circlelist_node_t *)&v5, 0);
	CircleList_Insert(list, (circlelist_node_t *)&v6, 0);
	CircleList_Insert(list, (circlelist_node_t *)&v7, 0);
	CircleList_Insert(list, (circlelist_node_t *)&v8, 0);
	
	
	//  游标测试
	value_t *pv = (value_t *)CircleList_Current_Get(list); 
	printf("1.slider:%d\n", pv->value);
	
	// 移动2次游标 
	CircleList_Next_Get(list);
	CircleList_Next_Get(list);
	
	pv = (value_t *)CircleList_Current_Get(list); 
	printf("2.slider:%d\n", pv->value);
	
	//复位游标 
	pv = (value_t *)CircleList_reset(list);
	printf("3.slider:%d\n", pv->value);
	
	CircleList_Destroy(list);
	printf("\n---===function test1 success!===---\n"); 
	return 0;
}


#define  NUM    3 
//约瑟夫环问题 函数测试 
void test2()
{
	printf("\n*************test2*****************\n");
	// 创建链表（init） 
	CircleList *list = CircleList_Creat();
	
	value_t v1;
	value_t v2;
	value_t v3;
	value_t v4;
	value_t v5;
	value_t v6;
	value_t v7;
	value_t v8;
	
	v1.value = 1;
	v2.value = 2;
	v3.value = 3;
	v4.value = 4;
	v5.value = 5;
	v6.value = 6;
	v7.value = 7;
	v8.value = 8;
	
	// 尾插法 
	CircleList_Insert(list, (circlelist_node_t *)&v1, CircleList_Length_Get(list));
	CircleList_Insert(list, (circlelist_node_t *)&v2, CircleList_Length_Get(list));
	CircleList_Insert(list, (circlelist_node_t *)&v3, CircleList_Length_Get(list));
	CircleList_Insert(list, (circlelist_node_t *)&v4, CircleList_Length_Get(list));
	CircleList_Insert(list, (circlelist_node_t *)&v5, CircleList_Length_Get(list));
	CircleList_Insert(list, (circlelist_node_t *)&v6, CircleList_Length_Get(list));
	CircleList_Insert(list, (circlelist_node_t *)&v7, CircleList_Length_Get(list));
	CircleList_Insert(list, (circlelist_node_t *)&v8, CircleList_Length_Get(list));
	
	// 打印链表 
	//CircleList_print(list); 
	CircleList_reset(list);
	 
	// 循环删除 
	while ( CircleList_Length_Get(list) > 0) {
		value_t *pv = NULL;
		int i = 0;
		
		// 循环3次  每次提取第 NUM 位置的元素删除 
		for(i = 1; i < NUM; i++) {
			CircleList_Next_Get(list);
		} 
		pv = (value_t *)CircleList_Current_Get(list);
		printf("data: %d\n",pv->value);
		CricleListNode_delete(list, (circlelist_node_t *)pv);
	} 
	CircleList_Destroy(list);
	printf("\n---===function test2 success!===---\n"); 
}

// 主函数 
int main(int argc, char *argv[])
{
	// 函数测试程序 
	test1(); 
	
	test2();
	return 0;
}
