#include <stdio.h>
#include <malloc.h>
#include "list.h" 

/** \brief 链表信息 */
typedef struct _tag_ListNode {
	LinkListNode_t hander; /* 链表的头指针 */ 
	int length;            /* 链表长度     */ 
} TListNode_t;

/**
 * \brief 创建一个节点 
 *
 * \ret  节点的地址 
 */ 
LinkList* LinkList_Create (void)
{
    TListNode_t *ret = (TListNode_t *)malloc(sizeof(TListNode_t));
	
	if (ret != NULL) { /* 申请空间成功赋初值 */
		ret->hander.next = NULL;
		ret->length = 0; 
	} 
	return ret;
}

/**
 * \brief 摧毁整个链表 
 *
 * \param list[in]   节点的地址 
 */ 
void LinkList_Destroy (LinkList* list)
{
	free(list);  /* 释放整个空间 */ 
}

/**
 * \brief 清空整个链表 
 *
 * \param list[in]  链表的表头 
 */ 
void LinkList_Clear (LinkList* list)
{
	TListNode_t *slist = (TListNode_t *)list;
	 if (NULL != slist) {
	 	slist->hander.next = NULL;
	 	slist->length = 0;
	 }
}

/**
 * \brief 获取链表长度 
 *
 * \param list[in]  链表的头节点 
 *
 * \ret 链表的长度 
 */ 
int LinkList_Length_Get (LinkList* list)
{
	TListNode_t *slist = (TListNode_t *)list;
	
	int ret = -1;
	
	if (NULL != slist) {
		ret = slist->length;
	}
	
	return ret;
}

/**
 * \brief 插入链表 
 *
 * \param list[in]  链表的表头 
 * \param node[in]  待插入的链表
 * \param pos[in]   待插入的位置  
 *
 * \ret 1 ok  else error 
 */ 
int LinkList_Insert (LinkList* list, LinkListNode_t* node, int pos)
{
	int i              = 0;
    TListNode_t *slist = (TListNode_t *)list; /* 保存头节点 */
	int ret            = (NULL != slist) && 
	                     (NULL != node)  && 
						 (pos >= 0);
	
	/* 合法判断 */
	if (ret != 0) {
		
		LinkListNode_t *current = (LinkListNode_t *)slist; 
		
		/* 先找到待位置 要多一个条件判断保证下一个节点不能为NULL */
		for (i = 0; (i < pos) && (slist->hander.next != NULL); i++) {
			current = current->next;
		} 
		
		node->next    = current->next; /* 将新节点的指针直线下一个节点 */
		current->next = node;          /* 将上一个节点的位置指向新节点 */ 
	
        (slist->length)++;	
	} /* ret */
	
	return ret;
}

/**
 * \brief 获取链表节点信息
 * 
 * \param list[in]
 * \param pos[in]
 *
 * \ret 返回节点的地址 
 */
LinkListNode_t* LinkList_Get (LinkList* list, int pos)
{
	int             i     = 0; 
	LinkListNode_t *ret   = NULL;
	TListNode_t    *slist = (TListNode_t *)list; /* 头节点信息保存 */ 
	
	if ((NULL != slist) && (pos >= 0) && (pos < (slist->length))) {
		LinkListNode_t *current = (LinkListNode_t *)slist;
		
		/* 找到待搜索的节点 */
		for (i = 0; i < pos; i++) {
			current = current->next;
		}
		ret = current->next; 
	}
	return ret;
}

/**
 * \brief 删除一个节点 
 * 
 * \param list[in]  头节点
 * \param pos[in]   待删除的节点位置 
 * 
 * \ret 要删除的节点地址 
 */ 
LinkListNode_t* LinkList_Delete (LinkList* list, int pos)
{
	int            i       = 0;
	LinkListNode_t *ret    = NULL;
	TListNode_t    *slist  = (TListNode_t *)list;
	
	/* 合法判断 */
	if ((slist != NULL) && (pos >= 0) && (slist->length > pos)) {
		
		LinkListNode_t *current = (LinkListNode_t *)slist;
		
		/* 找到要删除的节点 */
		for(i = 0; i < pos; i++) {
			current = current->next;
		}
		ret = current->next;  /* 指向要删除的节点 */
		current->next = ret->next;        /* 上一个节点对接下一个节点 */ 
		
		ret->next = NULL;
		
		(slist->length)--;              /* 长度减一 */
	}
	return ret;
}




