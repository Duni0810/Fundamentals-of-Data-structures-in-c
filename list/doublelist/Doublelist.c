#include <stdio.h>
#include <malloc.h>
#include "DoubleList.h"

// 内部结构体 
typedef struct _tag_DoubleList {
	doublelist_node_t	header;   // 头节点信息 
	doublelist_node_t	*slider;  // 游标
	int					length;   // 链表长度 
}doublelist_t;

// 1.创建链表 
DoubleList* DoubleList_Create()
{
	doublelist_t *ret = (doublelist_t *)malloc(sizeof(doublelist_t));
	if (ret != NULL) {
		ret->length = 0;
		ret->slider = NULL;
		ret->header.next = NULL;
		ret->header.pre  = NULL;
	} 
	return ret;
}

// 2.摧毁链表，释放空间 
int DoubleList_Destroy(DoubleList* list)
{
	if(list != NULL) {
		free(list);
		return OK;
	}
	return ERROR;
}

// 3.清空链表 
int DoubleList_Clear(DoubleList* list)
{
	doublelist_t *slist  = (doublelist_t *)list;
	if (slist != NULL) {
		slist->length = 0;
		slist->slider = NULL;
		slist->header.next = NULL;
		slist->header.pre = NULL;
		return OK;
	}
	return ERROR;
}

// 4. 获取链表大小 
int DoubleList_Length_Get(DoubleList* list)
{
	doublelist_t *slist = (doublelist_t *)list;
	int ret = -1;
	if(slist != NULL) {
		ret = slist->length;
	} 
	return ret;
} 

// 5. 插入链表 
int DoubleList_Insert(DoubleList* list, doublelist_node_t* node, int pos)
{
	int i = 0;
	doublelist_t *slist = (doublelist_t *)list;
	int ret = ((slist != NULL) && (node != NULL) && (pos >= 0));
	
	// 合法性判断 
	if (ret) {
		doublelist_node_t *current = (doublelist_node_t *)slist;
		doublelist_node_t *next = NULL; 
		 
		for(i = 0; (i < pos) && (current->next != NULL); i++) {
			current = current->next; 
		}
		next = current->next; // 保存下一个节点
		
		// 执行插入算法
		current->next = node;
		node->next = next; 
		
		// 下一个节点不为 NULL 
		if (next != NULL) {
			next->pre = node;
		}
		node->pre = current;

		// 如果是一个空链表
		if (slist->length == 0) {
			slist->slider = node;
		} 
		
		slist->length++;
		
		// 如果插入第一个节点
		if(current == (doublelist_node_t *)slist) {
			node->pre = NULL;
		} 
	}
	return ret;
}

// 6. 获取链表节点 
doublelist_node_t* DoubleList_Get(DoubleList* list, int pos)
{
	doublelist_t *slist = (doublelist_t *)list;
	doublelist_node_t * ret = NULL;
	int i = 0;
	
	if ((slist != NULL) && (pos >= 0) && (pos < slist->length)) {
		doublelist_node_t *current = (doublelist_node_t *)slist;
		for (i = 0; i < pos; i++) {
			current = current->next; 
		}
		ret = current->next; 
	}
	return ret;
}

// 7. 删除某个位置链表节点 
doublelist_node_t* DoubleList_Delete(DoubleList* list, int pos)
{
	doublelist_t *slist = (doublelist_t *)list;
	doublelist_node_t * ret = NULL;
	int i = 0;
	if ((slist != NULL) && (pos >= 0) && (pos < slist->length)) {
		
		doublelist_node_t *current = (doublelist_node_t *)slist;
		doublelist_node_t *next = NULL;
		for (i = 0; i < pos; i++) {
			current = current->next;
		}
		ret  = current->next; // 待删除的元素 
		next = ret->next;     // 下一个元素
		
		// 执行删除算法
		current->next = next;
		if (next != NULL) {
			next->pre = current;
			// 如果删除的是第一个元素 
			if (current = (doublelist_node_t *)slist) {
				next->pre = NULL; 
			}
		}
		slist->length--;
		
		// 如果游标所在的位置被删除，瞬移一位 
		if (slist->slider = ret) {
			slist->slider = next;	
		} 
	}

	return ret;
}

// 8. 删除链表的某一个节点 
doublelist_node_t* DoubleList_DeleteNode(DoubleList* list, doublelist_node_t* node)
{
	doublelist_t *slist = (doublelist_t *)list;
	doublelist_node_t * ret = NULL;
	int i = 0;
	
	if ((slist != NULL) && (node != NULL)) {
		
		doublelist_node_t *current = (doublelist_node_t *)slist;
		for (i = 0; i < slist->length; i++) {
			if (node == current->next) {
				ret = current->next;
				break;
			}
			current = current->next;
		}
		
		if (ret != NULL) {
			DoubleList_Delete(slist, i);
		}
	}
	
	return ret;
} 

// 9. 游标复位 
doublelist_node_t* DoubleList_Reset(DoubleList* list)
{
	doublelist_t *slist = (doublelist_t *)list;
	doublelist_node_t * ret = NULL;
	
	if (slist != NULL) {
		slist->slider = slist->header.next;
		ret = slist->slider;
	}
	return ret;
}

// 10. 获取当前位置的游标 
doublelist_node_t* DoubleList_Current(DoubleList* list)
{
	doublelist_t *slist = (doublelist_t *)list;
	doublelist_node_t * ret = NULL;
	
	if(slist != NULL) {
		ret = slist->slider;
	}
	return ret;
}

// 11. 游标后移 
doublelist_node_t* DoubleList_Next(DoubleList* list)
{
	doublelist_t *slist = (doublelist_t *)list;
	doublelist_node_t * ret = NULL;
	
	if ((slist != NULL) && (slist->slider != NULL)) {
		ret = slist->slider;
		slist->slider = ret->next;
	}
	return ret;
}

// 12. 游标前移 
doublelist_node_t* DoubleList_Pre(DoubleList* list)
{
	doublelist_t *slist = (doublelist_t *)list;
	doublelist_node_t * ret = NULL;
	
	if ((slist != NULL) && (slist->slider != NULL)) {
		ret = slist->slider;
		slist->slider = ret->pre;
	}
	return ret;
}
