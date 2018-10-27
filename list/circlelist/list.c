#include <stdio.h>
#include <malloc.h>
#include "list.h"

// �ڲ���Ϣ�ṹ�� 
typedef struct _tag_circlelist {
	circlelist_node_t	header;   // ��������ͷ��Ϣ 
	circlelist_node_t	*slider;  // �α� 
	int 				length;   // ������ 
} circlelist_t;


// �������� 
// 1. malloc ����ռ� 
// 2. ��������Ϣ����ֵ 
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

// �ݻ����� 
// 1. free �ͷ��ڴ� 
int CircleList_Destroy(CircleList *list)
{
	if (NULL != NULL) {
		free(list);
		return OK;
	}
	return ERROR;
}

// �������
// 1.����������һ��Ԫ�ص�ָ��ָ��� 
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

// ��ȡ����ĳ���
// ������������Ϣ 
int CircleList_Length_Get(CircleList *list)
{
	int ret = -1; 
	circlelist_t *slist = (circlelist_t *)list;
	if (slist != NULL) {
		ret = slist->length;	
	}
	
	return ret;
}

// ����ڵ� 
// 1.�����Ϸ����ж�
// 2.�ҵ�����λ��
// 3.ʵʩ�����㷨������������Ϣ�ĳ��ȼ� 1 
// 4.�����м����Ƚ�����ĵط�������ǿգ�
//		(1)�������Ļ����α�ָ���һ��Ԫ�أ�
//		(2)����ǲ����ڵ�һ��Ԫ�صĻ�,���ǵ��ҵ���������һ��Ԫ�أ�������nextָ������Ԫ�� 
int CircleList_Insert(CircleList *list, circlelist_node_t *node, int pos)
{
	int i 				= 0;
	circlelist_t *slist = (circlelist_t *)list;  // ���ͽ��װ 
	int ret 			= ((slist != NULL) && (node != NULL) && (pos >= 0));
	
	// �����Ϸ�
	if (ret) {  
		circlelist_node_t *current = (circlelist_node_t *)slist;
		 
		 // ���������λ�� 
		 for (i = 0; (i < pos) && (current->next != NULL); i++) {
		 	current = current->next; 
		 }
		 
		 // �ҵ�λ��֮�� ��������  node ��������Ҫ���������
		 // ����Ĳ����͵�����һ�� 
		 node->next    = current->next;
		 current->next = node; 
		 
		 // ����ǵ�һ�β���Ļ�Ҫ�� node ָ���Լ�
		 if (slist->length == 0) {
		 	slist->slider = node;
		 } 
		 
		 // ����һ���ڵ�λ����ȻҪ�� 1 ���� 
		 slist->length++;
		  
		 // ��������������ѭ������ �����м��������λ����Ҫ�����Ĵ���
		 // ����  ����ǲ����һ��λ�õĻ� 
		 if (current == (circlelist_node_t *)slist) {
			// ��������λ����ͷָ�룬��ôҪ�ҵ����һ��Ԫ�أ�
			//Ȼ�����һ��Ԫ�ص���һ��λ��ָ��current����һ�� 
		 	circlelist_node_t *last = CircleListNode_Get(slist, slist->length - 1);
		 	last->next = current->next;
		 }
	}	
	return ret;
}

// ɾ��λ�ýڵ� 
// 1. �Ϸ����ж� 
// 2. �ҵ�Ҫɾ���Ľڵ�λ��
// 3. ʵʩɾ���㷨������������ -1 
// 4. ɾ��Ҳ�м����Ƚ���Ҫ�ĵ㣬�ر��ǣ����ɾ�����ǵ�һ���ڵ� 
//		(1) Ϊ����ߴ����Ч�����⣬�������Ҫɾ�����ǵ�һ���ڵ㣬Ӧ�������ҵ����һ���ڵ㣬
//			����ڵ㣬������ڵ� 3 ��֮ǰʵʩ�ж�,����ÿ�ζ�Ҫѭ���ҵ����һ���ڵ㡣
//		(2) ��������ɾ����һ���ڵ㣬���ǽ����һ���ڵ�ָ��ɾ���ڵ����һ���ڵ㣬�����α�Ҳ�ƶ���
//		(3) ����ڵ㶼��ɾ����(�ڵ�ĳ���Ϊ0)����ôһ�л� 0 
circlelist_node_t *CircleList_Delete(CircleList *list, int pos)
{
	// ���װ 
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL;
	int i = 0;
	 
	// �Ϸ����ж� 
	if ((slist != NULL) && (pos >= 0) && (slist->length > 0)) {
		circlelist_node_t *current = (circlelist_node_t *)slist;
		circlelist_node_t *last = NULL; // �������һ���ڵ� 
			
		for(i = 0; i < pos; i++) {
			current = current->next;
		}
		// ���ɾ�����ǵ�һ���ڵ�
		if(current == (circlelist_node_t *)slist) {
			last = CircleListNode_Get(slist, slist->length - 1);
		} 
		
		// ɾ���ڵ���� 
		ret = current->next;
		current->next = ret->next;
		slist->length--;
		
		// ɾ�����ǵ�һ���ڵ� 
		//��ͷ�ڵ��ָ��ɾ���ڵ����һ���ڵ㣬���һ���ڵ�Ҳָ��ɾ���ڵ����һ���ڵ� 
		if (last != NULL) {
			slist->header.next = ret->next;
			last->next = ret->next; 
		}
		
		// ����α����ڵ�λ�ñ�ɾ������ô�α�Ҳ˳������һλ 
		if (slist->slider == ret) {
			slist->slider = ret->next;
		}
		// ����ڵ㱻ɾ���ˣ���ͷ�ڵ�ָ��NULL���α�Ҳָ��NULL 
		if (slist->length == 0) {
			slist->header.next	= NULL;
			slist->slider		= NULL;
		} 
	} 
	return ret;
}

//ɾ����Ϣ�ڵ�
// 1.�Ϸ����ж�
// 2.�ҵ�Ҫɾ���Ľڵ�λ�� 
// 3.����ҵ��ڵ㣬����֮ǰ��ɾ����������û�������� NULl  
circlelist_node_t *CricleListNode_delete(CircleList *list, circlelist_node_t *node)
{
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL;	
	int i = 0;
	
	// �Ϸ����ж� 
	if ((slist != NULL) && (node != NULL)){
		circlelist_node_t *current = (circlelist_node_t *)slist;
		for(i = 0; i < slist->length; i++) {
			
			// �ж�λ�ã��ҵ�λ�ã�����λ���˳� for 
			if (node == current->next) {
				ret = current->next; 
				break;
			}
			current = current->next;
		} // ��λ�õ�for ѭ�� 
		
		// �ҵ�λ�ú����֮ǰ�ĺ���ɾ�� 
		if (ret != NULL) {
			CircleList_Delete(slist, i);
		} 
	}
	
	return ret;
}
 
// ��ȡ�ڵ�
// 1. �Ϸ����ж�
// 2. �ҵ����ҵĽڵ㲢���� 
circlelist_node_t *CircleListNode_Get(CircleList *list, int pos)
{
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL; 
	int i = 0;
	
	// �Ϸ����ж� 
	if ((slist != NULL) && (pos >= 0) && (slist->length > 0)) {
		
		circlelist_node_t *current = (circlelist_node_t *)slist; 
		for (i = 0; i < pos; i++) {
			current = current->next;
		} // ����posλ�� 
		ret = current->next; 
	}
	
	return ret;
}


// 9. ��λѭ�������α�
// 1.�Ϸ����ж�
// 2.�α�ָ���һ��λ�� 
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

// 10.��ȡ�α�λ��
// 1.�Ϸ����ж�
// 2.�����α�ĵ�ǰλ�� 
circlelist_node_t *CircleList_Current_Get(CircleList *list)
{
	circlelist_t *slist = (circlelist_t *)list;
	circlelist_node_t *ret = NULL;
	
	if (slist != NULL) {
		ret = slist->slider;
	}
	return ret; 
}

// 11.��ȡ�α���һ��λ��
// 1.�Ϸ����ж�
// 2.����һ���α�λ 
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
