#include <stdio.h>
#include <malloc.h>
#include "linkstack.h"
#include "list.h"

typedef struct _tag_LinkStackNode {
	LinkListNode_t header;   
	void  *item;			// ջ��ַ���� 
} LinkStack_Node_t;


// 1.����ջ 
LinkStack *LinkStack_Create()
{
	return LinkList_Create();
} 

// 2. �ݻ�ջ 
int LinkStack_Destroy(LinkStack *stack)
{
	int ret = (stack != NULL);
	
	if (ret) {
		LinkStack_Clear(stack);
		LinkList_Destroy(stack);
		return OK;
	} 
	// �����ջ 
	return ERROR;
}

// 3.���ջ
int LinkStack_Clear(LinkStack *stack)
{
	int ret = (stack != NULL) ;
	
	if (ret) {
			// �����ȵ�ջ ������ڴ���� 
		while (LinkStack_Size(stack) > 0) {
			LinkStack_Pop(stack);
		}
		return OK;
	} 

	return ERROR;
}

// 4.ѹջ
// ��������һ���ռ䣬Ȼ��ѹջ 
int LinkStack_Push(LinkStack* stack, void *item)
{
	LinkStack_Node_t *node = (LinkStack_Node_t *)malloc(sizeof(LinkStack_Node_t));
	int ret = (node != NULL) && (item != NULL) && (stack != NULL);
	
	if (ret) {
		node->item = item; // �����item 
		//ѹջ 
		ret = LinkList_Insert(stack, (LinkListNode_t *)node, 0);
	}
	
	// ѹջʧ�� �ͷſռ� 
	if (!ret) {
		free (node);
	} 
	return ret; 
}

// 5.��ջ
// ɾ����һ��Ԫ�� 
LinkStack *LinkStack_Pop(LinkStack *stack)
{
	// ɾ����һ��Ԫ�� 
	LinkStack_Node_t *node = (LinkStack_Node_t *)LinkList_Delete(stack, 0);
	void *ret  = NULL;
	
	// ��һ��Ԫ��ɾ���ɹ� 
	if (node != NULL) {
		ret = node->item;
		
		// �ͷſռ� 
		free(node);
	} 
	return ret;
}

// 6.ջ�� 
LinkStack *LinkStack_Top(LinkStack *stack)
{
	LinkStack_Node_t *node = (LinkStack_Node_t *)LinkList_Get(stack, 0);
	void *ret  = NULL;
	
	if (node != NULL) {
		ret = node->item;
	} 
	return ret;
}

// 7.ջ��С
int LinkStack_Size(LinkStack *stack)
{
	return LinkList_Length_Get(stack); 
} 

