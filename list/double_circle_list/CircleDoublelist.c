#include <stdio.h>
#include <malloc.h>
#include "CircleDoubleList.h"

// 内部结构体 
typedef struct _tag_DoubleList {
	circle_doublelist_node_t	header;   // 头节点信息 
	circle_doublelist_node_t	*slider;  // 游标
	int					length;           // 链表长度 
}Dcirclelist_t;

// 1.创建链表 
Circle_Double_List* Circle_Double_List_Create()
{
	Dcirclelist_t *ret = (Dcirclelist_t *)malloc(sizeof(Dcirclelist_t));
	if (ret != NULL) {
		ret->length = 0;
		ret->slider = NULL;
		ret->header.next = NULL;
		ret->header.pre  = NULL;
	} 
	return ret;
}

// 2.摧毁链表，释放空间 
int Circle_Double_List_Destroy(Circle_Double_List* list)
{
	if(list != NULL) {
		free(list);
		return OK;
	}
	return ERROR;
}

// 3.清空链表 
int Circle_Double_List_Clear(Circle_Double_List* list)
{
	Dcirclelist_t *slist  = (Dcirclelist_t *)list;
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
int Circle_Double_List_Length_Get(Circle_Double_List* list)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	int ret = -1;
	if(slist != NULL) {
		ret = slist->length;
	} 
	return ret;
} 

// 5. 插入链表 
int Circle_Double_List_Insert(Circle_Double_List* list, circle_doublelist_node_t* node, int pos)
{
	int i = 0;
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	int ret = ((slist != NULL) && (node != NULL) && (pos >= 0));
	
	// 合法性判断 
	if (ret) {
		circle_doublelist_node_t *current = (circle_doublelist_node_t *)slist;
		circle_doublelist_node_t *next = NULL; 
		 
		for(i = 0; (i < pos) && (current->next != NULL); i++) {
			current = current->next; 
		}
		next = current->next; // 保存下一个节点
		
		// 执行插入算法
		current->next = node;
		node->next = next; 
		
		// 下一个节点不为 NULL 也就是不为空链表 
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
		if(current == (circle_doublelist_node_t *)slist) {
			// 找到最后一个元素 
			circle_doublelist_node_t* last = Circle_Double_List_Get(slist, slist->length -1);
			
			last->next = current->next;
			node->pre = last;
		} 
	}
	return ret;
}

// 6. 获取链表节点 
circle_doublelist_node_t* Circle_Double_List_Get(Circle_Double_List* list, int pos)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	int i = 0;
	
	if ((slist != NULL) && (pos >= 0) && (slist->length > 0)) {
		circle_doublelist_node_t *current = (circle_doublelist_node_t *)slist;
		for (i = 0; i < pos; i++) {
			current = current->next; 
		}
		ret = current->next; 
	}
	return ret;
}

// 7. 删除某个位置链表节点 
circle_doublelist_node_t* Circle_Double_List_Delete(Circle_Double_List* list, int pos)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	int i = 0;
	
	// 合法性判断 
	if ((slist != NULL) && (pos >= 0) && (pos < slist->length)) {
		
		circle_doublelist_node_t *current = (circle_doublelist_node_t *)slist;
		circle_doublelist_node_t *next = NULL;
		circle_doublelist_node_t *last = NULL; 
		
		for (i = 0; i < pos; i++) {
			current = current->next;
		}
		ret  = current->next; // 待删除的元素 
		next = ret->next;     // 下一个元素
		
		// 执行删除算法
		current->next = next;
		next->pre = current;
			
		// 如果删除的是第一个元素 
		if (current = (circle_doublelist_node_t *)slist) {
			
			// 先找到最后一个元素 
			last = Circle_Double_List_Get(slist, slist->length -1);
			last->next = next;
			next->pre = last;
		}
		slist->length--;
		
		// 如果游标所在的位置被删除，顺移一位 
		if (slist->slider = ret) {
			slist->slider = next;	
		} 
		
		// 如果链表为空 
		if (slist->length == 0)  {
			current->next = NULL;
			current->pre = NULL; 
			slist->slider = NULL;
		}
	}

	return ret;
}

// 8. 删除链表的某一个节点 
circle_doublelist_node_t* Circle_Double_List_DeleteNode(Circle_Double_List* list, circle_doublelist_node_t* node)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	int i = 0;
	
	if ((slist != NULL) && (node != NULL)) {
		
		circle_doublelist_node_t *current = (circle_doublelist_node_t *)slist;
		for (i = 0; i < slist->length; i++) {
			if (node == current->next) {
				ret = current->next;
				break;
			}
			current = current->next;
		}
		
		if (ret != NULL) {
			Circle_Double_List_Delete(slist, i);
		}
	}
	
	return ret;
} 

// 9. 游标复位 
circle_doublelist_node_t* Circle_Double_List_Reset(Circle_Double_List* list)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	
	if (slist != NULL) {
		slist->slider = slist->header.next;
		ret = slist->slider;
	}
	return ret;
}

// 10. 获取当前位置的游标 
circle_doublelist_node_t* Circle_Double_List_Current(Circle_Double_List* list)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	
	if(slist != NULL) {
		ret = slist->slider;
	}
	return ret;
}

// 11. 游标后移 
circle_doublelist_node_t* Circle_Double_List_Next(Circle_Double_List* list)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	
	if ((slist != NULL) && (slist->slider != NULL)) {
		ret = slist->slider;
		slist->slider = ret->next;
	}
	return ret;
}

// 12. 游标前移 
circle_doublelist_node_t* Circle_Double_List_Pre(Circle_Double_List* list)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	
	if ((slist != NULL) && (slist->slider != NULL)) {
		ret = slist->slider;
		slist->slider = ret->pre;
	}
	return ret;
}
