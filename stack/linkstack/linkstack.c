#include <stdio.h>
#include <malloc.h>
#include "linkstack.h"
#include "list.h"

typedef struct _tag_LinkStackNode {
	LinkListNode_t header;   
	void  *item;			// 栈地址保存 
} LinkStack_Node_t;


// 1.创建栈 
LinkStack *LinkStack_Create()
{
	return LinkList_Create();
} 

// 2. 摧毁栈 
int LinkStack_Destroy(LinkStack *stack)
{
	int ret = (stack != NULL);
	
	if (ret) {
		LinkStack_Clear(stack);
		LinkList_Destroy(stack);
		return OK;
	} 
	// 先清空栈 
	return ERROR;
}

// 3.清空栈
int LinkStack_Clear(LinkStack *stack)
{
	int ret = (stack != NULL) ;
	
	if (ret) {
			// 必须先弹栈 否则会内存溢出 
		while (LinkStack_Size(stack) > 0) {
			LinkStack_Pop(stack);
		}
		return OK;
	} 

	return ERROR;
}

// 4.压栈
// 得先申请一个空间，然后压栈 
int LinkStack_Push(LinkStack* stack, void *item)
{
	LinkStack_Node_t *node = (LinkStack_Node_t *)malloc(sizeof(LinkStack_Node_t));
	int ret = (node != NULL) && (item != NULL) && (stack != NULL);
	
	if (ret) {
		node->item = item; // 保存的item 
		//压栈 
		ret = LinkList_Insert(stack, (LinkListNode_t *)node, 0);
	}
	
	// 压栈失败 释放空间 
	if (!ret) {
		free (node);
	} 
	return ret; 
}

// 5.弹栈
// 删除第一个元素 
LinkStack *LinkStack_Pop(LinkStack *stack)
{
	// 删除第一个元素 
	LinkStack_Node_t *node = (LinkStack_Node_t *)LinkList_Delete(stack, 0);
	void *ret  = NULL;
	
	// 第一个元素删除成功 
	if (node != NULL) {
		ret = node->item;
		
		// 释放空间 
		free(node);
	} 
	return ret;
}

// 6.栈顶 
LinkStack *LinkStack_Top(LinkStack *stack)
{
	LinkStack_Node_t *node = (LinkStack_Node_t *)LinkList_Get(stack, 0);
	void *ret  = NULL;
	
	if (node != NULL) {
		ret = node->item;
	} 
	return ret;
}

// 7.栈大小
int LinkStack_Size(LinkStack *stack)
{
	return LinkList_Length_Get(stack); 
} 

