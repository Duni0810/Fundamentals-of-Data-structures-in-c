#include <stdio.h>
#include <malloc.h>
#include "CircleDoubleList.h"

// �ڲ��ṹ�� 
typedef struct _tag_DoubleList {
	circle_doublelist_node_t	header;   // ͷ�ڵ���Ϣ 
	circle_doublelist_node_t	*slider;  // �α�
	int					length;           // ������ 
}Dcirclelist_t;

// 1.�������� 
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

// 2.�ݻ������ͷſռ� 
int Circle_Double_List_Destroy(Circle_Double_List* list)
{
	if(list != NULL) {
		free(list);
		return OK;
	}
	return ERROR;
}

// 3.������� 
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

// 4. ��ȡ�����С 
int Circle_Double_List_Length_Get(Circle_Double_List* list)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	int ret = -1;
	if(slist != NULL) {
		ret = slist->length;
	} 
	return ret;
} 

// 5. �������� 
int Circle_Double_List_Insert(Circle_Double_List* list, circle_doublelist_node_t* node, int pos)
{
	int i = 0;
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	int ret = ((slist != NULL) && (node != NULL) && (pos >= 0));
	
	// �Ϸ����ж� 
	if (ret) {
		circle_doublelist_node_t *current = (circle_doublelist_node_t *)slist;
		circle_doublelist_node_t *next = NULL; 
		 
		for(i = 0; (i < pos) && (current->next != NULL); i++) {
			current = current->next; 
		}
		next = current->next; // ������һ���ڵ�
		
		// ִ�в����㷨
		current->next = node;
		node->next = next; 
		
		// ��һ���ڵ㲻Ϊ NULL Ҳ���ǲ�Ϊ������ 
		if (next != NULL) {
			next->pre = node;
		}
		node->pre = current;
		
		// �����һ��������
		if (slist->length == 0) {
			slist->slider = node;
		} 
		
		slist->length++;
		
		// ��������һ���ڵ�
		if(current == (circle_doublelist_node_t *)slist) {
			// �ҵ����һ��Ԫ�� 
			circle_doublelist_node_t* last = Circle_Double_List_Get(slist, slist->length -1);
			
			last->next = current->next;
			node->pre = last;
		} 
	}
	return ret;
}

// 6. ��ȡ����ڵ� 
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

// 7. ɾ��ĳ��λ������ڵ� 
circle_doublelist_node_t* Circle_Double_List_Delete(Circle_Double_List* list, int pos)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	int i = 0;
	
	// �Ϸ����ж� 
	if ((slist != NULL) && (pos >= 0) && (pos < slist->length)) {
		
		circle_doublelist_node_t *current = (circle_doublelist_node_t *)slist;
		circle_doublelist_node_t *next = NULL;
		circle_doublelist_node_t *last = NULL; 
		
		for (i = 0; i < pos; i++) {
			current = current->next;
		}
		ret  = current->next; // ��ɾ����Ԫ�� 
		next = ret->next;     // ��һ��Ԫ��
		
		// ִ��ɾ���㷨
		current->next = next;
		next->pre = current;
			
		// ���ɾ�����ǵ�һ��Ԫ�� 
		if (current = (circle_doublelist_node_t *)slist) {
			
			// ���ҵ����һ��Ԫ�� 
			last = Circle_Double_List_Get(slist, slist->length -1);
			last->next = next;
			next->pre = last;
		}
		slist->length--;
		
		// ����α����ڵ�λ�ñ�ɾ����˳��һλ 
		if (slist->slider = ret) {
			slist->slider = next;	
		} 
		
		// �������Ϊ�� 
		if (slist->length == 0)  {
			current->next = NULL;
			current->pre = NULL; 
			slist->slider = NULL;
		}
	}

	return ret;
}

// 8. ɾ�������ĳһ���ڵ� 
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

// 9. �α긴λ 
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

// 10. ��ȡ��ǰλ�õ��α� 
circle_doublelist_node_t* Circle_Double_List_Current(Circle_Double_List* list)
{
	Dcirclelist_t *slist = (Dcirclelist_t *)list;
	circle_doublelist_node_t * ret = NULL;
	
	if(slist != NULL) {
		ret = slist->slider;
	}
	return ret;
}

// 11. �α���� 
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

// 12. �α�ǰ�� 
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
