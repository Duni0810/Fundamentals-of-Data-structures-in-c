#include <stdio.h>
#include <malloc.h>
#include "list.h" 

/** \brief ������Ϣ */
typedef struct _tag_ListNode {
	LinkListNode_t hander; /* �����ͷָ�� */ 
	int length;            /* ������     */ 
} TListNode_t;

/**
 * \brief ����һ���ڵ� 
 *
 * \ret  �ڵ�ĵ�ַ 
 */ 
LinkList* LinkList_Create (void)
{
    TListNode_t *ret = (TListNode_t *)malloc(sizeof(TListNode_t));
	
	if (ret != NULL) { /* ����ռ�ɹ�����ֵ */
		ret->hander.next = NULL;
		ret->length = 0; 
	} 
	return ret;
}

/**
 * \brief �ݻ��������� 
 *
 * \param list[in]   �ڵ�ĵ�ַ 
 */ 
void LinkList_Destroy (LinkList* list)
{
	free(list);  /* �ͷ������ռ� */ 
}

/**
 * \brief ����������� 
 *
 * \param list[in]  ����ı�ͷ 
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
 * \brief ��ȡ������ 
 *
 * \param list[in]  �����ͷ�ڵ� 
 *
 * \ret ����ĳ��� 
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
 * \brief �������� 
 *
 * \param list[in]  ����ı�ͷ 
 * \param node[in]  �����������
 * \param pos[in]   �������λ��  
 *
 * \ret 1 ok  else error 
 */ 
int LinkList_Insert (LinkList* list, LinkListNode_t* node, int pos)
{
	int i              = 0;
    TListNode_t *slist = (TListNode_t *)list; /* ����ͷ�ڵ� */
	int ret            = (NULL != slist) && 
	                     (NULL != node)  && 
						 (pos >= 0);
	
	/* �Ϸ��ж� */
	if (ret != 0) {
		
		LinkListNode_t *current = (LinkListNode_t *)slist; 
		
		/* ���ҵ���λ�� Ҫ��һ�������жϱ�֤��һ���ڵ㲻��ΪNULL */
		for (i = 0; (i < pos) && (slist->hander.next != NULL); i++) {
			current = current->next;
		} 
		
		node->next    = current->next; /* ���½ڵ��ָ��ֱ����һ���ڵ� */
		current->next = node;          /* ����һ���ڵ��λ��ָ���½ڵ� */ 
	
        (slist->length)++;	
	} /* ret */
	
	return ret;
}

/**
 * \brief ��ȡ����ڵ���Ϣ
 * 
 * \param list[in]
 * \param pos[in]
 *
 * \ret ���ؽڵ�ĵ�ַ 
 */
LinkListNode_t* LinkList_Get (LinkList* list, int pos)
{
	int             i     = 0; 
	LinkListNode_t *ret   = NULL;
	TListNode_t    *slist = (TListNode_t *)list; /* ͷ�ڵ���Ϣ���� */ 
	
	if ((NULL != slist) && (pos >= 0) && (pos < (slist->length))) {
		LinkListNode_t *current = (LinkListNode_t *)slist;
		
		/* �ҵ��������Ľڵ� */
		for (i = 0; i < pos; i++) {
			current = current->next;
		}
		ret = current->next; 
	}
	return ret;
}

/**
 * \brief ɾ��һ���ڵ� 
 * 
 * \param list[in]  ͷ�ڵ�
 * \param pos[in]   ��ɾ���Ľڵ�λ�� 
 * 
 * \ret Ҫɾ���Ľڵ��ַ 
 */ 
LinkListNode_t* LinkList_Delete (LinkList* list, int pos)
{
	int            i       = 0;
	LinkListNode_t *ret    = NULL;
	TListNode_t    *slist  = (TListNode_t *)list;
	
	/* �Ϸ��ж� */
	if ((slist != NULL) && (pos >= 0) && (slist->length > pos)) {
		
		LinkListNode_t *current = (LinkListNode_t *)slist;
		
		/* �ҵ�Ҫɾ���Ľڵ� */
		for(i = 0; i < pos; i++) {
			current = current->next;
		}
		ret = current->next;  /* ָ��Ҫɾ���Ľڵ� */
		current->next = ret->next;        /* ��һ���ڵ�Խ���һ���ڵ� */ 
		
		ret->next = NULL;
		
		(slist->length)--;              /* ���ȼ�һ */
	}
	return ret;
}




