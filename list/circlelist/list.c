#include <stdio.h>
#include <malloc.h>
#include "list.h"

// 内部信息结构体 
typedef struct _tag_circlelist {
	circlelist_node_t	header;   // 保存链表头信息 
	circlelist_node_t	*slider;  // 游标 
	int 				length;   // 链表长度 
} circlelist_t;


// 创建链表 
// 1. malloc 申请空间 
// 2. 给链表信息赋初值 
CircleList *CircleList_Creat()
{
	circlelist_t *ret = (circlelist_t *)malloc(sizeof(circlelist_t));
	
	if (ret != NULL) {
		ret->header.next	= NULL;
		ret->slider			= NULL; 
		ret->length			= 0;
	} 
	return ret;
}

// 摧毁链表 
// 1. free 释放内存 
int CircleList_Destroy(CircleList *list)
{
	if (NULL != NULL) {
		free(list);
		return OK;
	}
	return ERROR;
}

// 清空链表
// 1.断链，将第一个元素的指针指向空 
int CircleList_clear(CircleList *list)
{
	circlelist_t *slist = (circlelist_t *)list;
	
	if (slist != NULL) {
		slist->header.next	= NULL;
		slist->slider		= NULL;
		slist->length		= 0;
		return OK;
	}
	return ERROR;
}

// 获取链表的长度
// 返回链表长度信息 
int CircleList_Length_Get(CircleList *list)
{
	int ret = -1; 
	circlelist_t *slist = (circlelist_t *)list;
	if (slist != NULL) {
		ret = slist->length;	
	}
	
	return ret;
}

// 插入节点 
// 1.参数合法性判断
// 2.找到插入位置
// 3.实施插入算法，并将链表信息的长度加 1 
// 4.插入有几个比较特殊的地方：如果是空；
//		(1)链表插入的话，游标指向第一个元素；
//		(2)如果是插入在第一个元素的话,我们得找到链表的最后一个元素，将他的next指向插入的元素 
int CircleList_Insert(CircleList *list, circlelist_node_t *node, int pos)
{
	int i 				= 0;
	circlelist_t *slist = (circlelist_t *)list;  // 类型解封装 
	int ret 			= ((slist != NULL) && (node != NULL) && (pos >= 0));
	
	// 参数合法
	if (ret) {  
		circlelist_node_t *current = (circlelist_node_t *)slist;
		 
		 // 遍历链表的位置 
		 for (i = 0; (i < pos) && (current->next != NULL); i++) {
		 	current = current->next; 
		 }
		 
		 // 找到位置之后 插入链表  node 就是我们要插入的链表
		 // 这里的操作和单链表一致 
		 node->next    = current->next;
		 current->next = node; 
		 
		 // 如果是第一次插入的话要让 node 指向自己
		 if (slist->length == 0) {
		 	slist->slider = node;
		 } 
		 
		 // 插入一个节点位置自然要加 1 处理 
		 slist->length++;
		  
		 // 这里我们做的是循环链表 所以有几个特殊的位置需要单独的处理
		 // 例如  如果是插入第一个位置的话 
		 if (current == (circlelist_node_t *)slist) {
			// 如果插入的位置在头指针，那么要找到最后一个元素，
			//然后将最后一个元素的下一个位置指向current的下一个 
		 	circlelist_node_t *last = CircleListNode_Get(slist, slist->length - 1);
		 	last->next = current->next;
		 }
	}	
	return ret;
}

// 删除位置节点 
// 1. 合法性判断 
// 2. 找到要删除的节点位置
// 3. 实施删除算法，并且链表长度 -1 
// 4. 删除也有几个比较重要的点，特别是：如果删除的是第一个节点 
//		(1) 为了提高代码的效率问题，如果我们要删除的是第一个节点，应该是先找到最后一个节点，
//			保存节点，这可以在第 3 步之前实施判断,避免每次都要循环找到最后一个节点。
//		(2) 如果真的是删除第一个节点，我们将最后一个节点指向删除节点的下一个节点，并且游标也移动。
//		(3) 如果节点都被删除完(节点的长度为0)，那么一切回 0 
circlelist_node_t *CircleList_Delete(CircleList *list, int pos)
{
	// 解封装 
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL;
	int i = 0;
	 
	// 合法性判断 
	if ((slist != NULL) && (pos >= 0) && (slist->length > 0)) {
		circlelist_node_t *current = (circlelist_node_t *)slist;
		circlelist_node_t *last = NULL; // 定义最后一个节点 
			
		for(i = 0; i < pos; i++) {
			current = current->next;
		}
		// 如果删除的是第一个节点
		if(current == (circlelist_node_t *)slist) {
			last = CircleListNode_Get(slist, slist->length - 1);
		} 
		
		// 删除节点操作 
		ret = current->next;
		current->next = ret->next;
		slist->length--;
		
		// 删除的是第一个节点 
		//将头节点的指向删除节点的下一个节点，最后一个节点也指向删除节点的下一个节点 
		if (last != NULL) {
			slist->header.next = ret->next;
			last->next = ret->next; 
		}
		
		// 如果游标所在的位置被删除，那么游标也顺表下移一位 
		if (slist->slider == ret) {
			slist->slider = ret->next;
		}
		// 如果节点被删完了，让头节点指向NULL，游标也指向NULL 
		if (slist->length == 0) {
			slist->header.next	= NULL;
			slist->slider		= NULL;
		} 
	} 
	return ret;
}

//删除信息节点
// 1.合法性判断
// 2.找到要删除的节点位置 
// 3.如果找到节点，调用之前的删除函数；若没到到返回 NULl  
circlelist_node_t *CricleListNode_delete(CircleList *list, circlelist_node_t *node)
{
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL;	
	int i = 0;
	
	// 合法性判断 
	if ((slist != NULL) && (node != NULL)){
		circlelist_node_t *current = (circlelist_node_t *)slist;
		for(i = 0; i < slist->length; i++) {
			
			// 判断位置，找到位置，保存位置退出 for 
			if (node == current->next) {
				ret = current->next; 
				break;
			}
			current = current->next;
		} // 找位置的for 循环 
		
		// 找到位置后调用之前的函数删除 
		if (ret != NULL) {
			CircleList_Delete(slist, i);
		} 
	}
	
	return ret;
}
 
// 获取节点
// 1. 合法性判断
// 2. 找到待找的节点并返回 
circlelist_node_t *CircleListNode_Get(CircleList *list, int pos)
{
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL; 
	int i = 0;
	
	// 合法性判断 
	if ((slist != NULL) && (pos >= 0) && (slist->length > 0)) {
		
		circlelist_node_t *current = (circlelist_node_t *)slist; 
		for (i = 0; i < pos; i++) {
			current = current->next;
		} // 查找pos位置 
		ret = current->next; 
	}
	
	return ret;
}


// 9. 复位循环链表游标
// 1.合法性判断
// 2.游标指向第一个位置 
circlelist_node_t *CircleList_reset(CircleList *list)
{
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL;
	
	
	if (slist != NULL) {
		slist->slider = slist->header.next;
		ret = slist->slider;	
	}
	return ret;
}

// 10.获取游标位置
// 1.合法性判断
// 2.返回游标的当前位置 
circlelist_node_t *CircleList_Current_Get(CircleList *list)
{
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL;
	
	if (slist != NULL) {
		ret = slist->slider;
	}
	return ret; 
}

// 11.获取游标下一个位置
// 1.合法性判断
// 2.下移一个游标位 
circlelist_node_t *CircleList_Next_Get(CircleList *list)
{
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL;
	
	if ((slist != NULL) && (slist->slider != NULL)) {
		ret = slist->slider;
		slist->slider = ret->next;
	}
	
	return ret;
}
