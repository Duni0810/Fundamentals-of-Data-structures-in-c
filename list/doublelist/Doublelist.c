#include <stdio.h>
#include <malloc.h>
#include "DoubleList.h"

// �ڲ��ṹ�� 
typedef struct _tag_DoubleList {
	doublelist_node_t	header;   // ͷ�ڵ���Ϣ 
	doublelist_node_t	*slider;  // �α�
	int					length;   // ������ 
}doublelist_t;

// 1.�������� 
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

// 2.�ݻ������ͷſռ� 
int DoubleList_Destroy(DoubleList* list)
{
	if(list != NULL) {
		free(list);
		return OK;
	}
	return ERROR;
}

// 3.������� 
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

// 4. ��ȡ�����С 
int DoubleList_Length_Get(DoubleList* list)
{
	doublelist_t *slist = (doublelist_t *)list;
	int ret = -1;
	if(slist != NULL) {
		ret = slist->length;
	} 
	return ret;
} 

// 5. �������� 
int DoubleList_Insert(DoubleList* list, doublelist_node_t* node, int pos)
{
	int i = 0;
	doublelist_t *slist = (doublelist_t *)list;
	int ret = ((slist != NULL) && (node != NULL) && (pos >= 0));
	
	// �Ϸ����ж� 
	if (ret) {
		doublelist_node_t *current = (doublelist_node_t *)slist;
		doublelist_node_t *next = NULL; 
		 
		for(i = 0; (i < pos) && (current->next != NULL); i++) {
			current = current->next; 
		}
		next = current->next; // ������һ���ڵ�
		
		// ִ�в����㷨
		current->next = node;
		node->next = next; 
		
		// ��һ���ڵ㲻Ϊ NULL 
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
		if(current == (doublelist_node_t *)slist) {
			node->pre = NULL;
		} 
	}
	return ret;
}

// 6. ��ȡ����ڵ� 
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

// 7. ɾ��ĳ��λ������ڵ� 
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
		ret  = current->next; // ��ɾ����Ԫ�� 
		next = ret->next;     // ��һ��Ԫ��
		
		// ִ��ɾ���㷨
		current->next = next;
		if (next != NULL) {
			next->pre = current;
			// ���ɾ�����ǵ�һ��Ԫ�� 
			if (current = (doublelist_node_t *)slist) {
				next->pre = NULL; 
			}
		}
		slist->length--;
		
		// ����α����ڵ�λ�ñ�ɾ����˲��һλ 
		if (slist->slider = ret) {
			slist->slider = next;	
		} 
	}

	return ret;
}

// 8. ɾ�������ĳһ���ڵ� 
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

// 9. �α긴λ 
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

// 10. ��ȡ��ǰλ�õ��α� 
doublelist_node_t* DoubleList_Current(DoubleList* list)
{
	doublelist_t *slist = (doublelist_t *)list;
	doublelist_node_t * ret = NULL;
	
	if(slist != NULL) {
		ret = slist->slider;
	}
	return ret;
}

// 11. �α���� 
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

// 12. �α�ǰ�� 
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
