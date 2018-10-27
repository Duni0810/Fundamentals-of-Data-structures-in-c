#include <stdio.h>
#include <malloc.h> 
#include "list.h"
 
// �ڵ㶨�� 
typedef struct _tag_StaticListNode {
	unsigned int data;   // ���ݱ��� 
	int next;			       // ������һ�����ݵ�λ�� 
} staticlistnode_t;

// ��̬����Ľṹ��Ķ��� 
typedef struct _tag_StaticList {
	int              capacity;   // ��ʾ��̬������������ɶ��ٸ�Ԫ�� 
	staticlistnode_t header;     // ����ͷ�ڵ�
	staticlistnode_t node[];     // �������ݵ��������� 
} staticlist_t;


/**
 * \brief ����һ���ڵ� 
 *
 * \param capacity[in]   ��̬��������� 
 *
 * \ret  �ڵ�ĵ�ַ 
 */ 
StaticList *StaticList_Create (int capacity)
{
	staticlist_t *ret = NULL;  // �������� 
    int i = 0;
	
	if (capacity >= 0) {
		// ��̬�Ĵ���һ����̬����  ����Ҫ����Ŀռ�Ϊ����Ĵ�С ��ͷ + ��Ҫ��������Ŀռ��С
		// + 1 ��Ҫ����Ϊ��һ��Ԫ����Ϊ�˱�ͷ��Ϊ����������λ�á�����+1 
		ret = (staticlist_t *)malloc(sizeof(staticlist_t) + sizeof(staticlistnode_t) * (capacity + 1));
	} 
	if (NULL != ret) {
	
		ret->capacity 	 = capacity;
		ret->header.data = 0;
		ret->header.next = 0; 
		
		for(i = 1; i <= ret->capacity; i++) {
			ret->node[i].next = -1;  // �½��ռ�ʱ�����е�next��ָ��-1. 
		}
	} 
	return ret;
}

/**
 * \brief �ݻ��������� 
 *
 * \param list[in]   �ڵ�ĵ�ַ 
 */ 
void StaticList_Destroy (StaticList* list)
{
	free(list); 
}

/**
 * \brief ����������� 
 *
 * \param list[in]  ����ı�ͷ 
 */ 
void StaticList_Clear (StaticList* list)
{
	int i = 0; 
	// ������������һ����װ���Կ�ʼ��ʱ������Ӧ����һ�����͵�ת��
	staticlist_t * slist = (staticlist_t *)list; 
	
	if (NULL != slist) {
		// ������������Ԫ�ص����ݱ�ʾΪ����ĳ��� 
		slist->header.data = 0;
		slist->header.next = 0; 
		
		for(i = 1; i <= slist->capacity; i++) {
			slist->node[i].next = -1;  // clear����ʱ�����е�next��ָ��-1. 
		}
	}
} 

/**
 * \brief ��ȡ������ ��ʵ�ʳ��ȣ� 
 *
 * \param list[in]  �����ͷ�ڵ� 
 *
 * \ret ����ĳ��� 
 */ 
int StaticList_Length_Get (StaticList* list)
{
	staticlist_t *slist = (staticlist_t *)list;
	int ret = -1;
	 
	// �Ϸ����ж�
	if (NULL != slist) {
		ret = slist->header.data;
	} 
	 
	return ret; 
} 

/**
 * \brief ��ȡ�������������С 
 *
 * \param list[in]  �����ͷ�ڵ� 
 *
 * \ret ����Ĵ�С 
 */ 
int StaticList_Capacity_Get (StaticList* list)
{
	staticlist_t *slist = (staticlist_t *)list;
	int ret = -1;
	
	if (NULL != slist) {
		ret = slist->capacity ;
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
int StaticList_Insert (StaticList* list, StaticListNode* node, int pos)
{
	staticlist_t *slist = (staticlist_t *)list;
	int ret             = ((slist != NULL) && (node != NULL));
	int i               = 0; 
	int index           = 0; // �����¼�ҵ�����λ�õı�ʶ
	int current         = 0;
	 
	ret = ret && (slist->header.data + 1 <= slist->capacity); // ���ݴ�С�������
	ret = ret && (pos >= 0) && (pos < slist->capacity); 
	
	if (ret) {
		
		for (i = 0; i < slist->capacity; i++) { // ����������ֵ�� ��һ���ɲ���Ŀ���λ�� 
	
			if (slist->node[i].next == -1) {    // �ҵ�����λ��
				index = i;                      // ��¼����λ�� ,�����˳����ҿ���λ�� 
				break; 
			}
		} 
		
		slist->node[index].data = (unsigned int)node;    // ���ṹ��ڵ���Ϣ��ֵ 
		
		
		slist->node[0] = slist->header;                  // ��ֵ��̬����ͷ 
		
		for (i = 0; (i < pos) && (slist->node[current].next != 0); i++) {
			current = slist->node[current].next;   
		} 
		
		slist->node[index].next   = slist->node[current].next; 
		slist->node[current].next = index;
		
		slist->node[0].data++;          // ������ɣ��ǵ�����Ԫ�ص�+1 
		slist->header = slist->node[0]; // �������� 
	}
	
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
StaticListNode* StaticList_Get (StaticList* list, int pos)
{
	int i       = 0;
	int current = 0; 
	int object  = 0; 
	StaticListNode *ret = NULL;
	staticlist_t *slist = (staticlist_t *)slist;
	
	// �Ϸ����ж� 
	if ((NULL != slist) && (pos >= 0) && (pos < slist->header.data)) {

		slist->node[0] = slist->header; // ��0 ��Ԫ�ش������ǵ�ͷ�ڵ� 
		
		for (i = 0; i < pos; i++) {
			// next �������һ��Ԫ�ص������±� ��Ҫ���ҵ��±� ��Ϊ��һ��Ԫ����ͷ�����Բ��� 
			current = slist->node[current].next;
		} 
		//  �±� 
		object = slist->node[current].next;
		
		// ��ȡ��Ԫ�� 
		ret = (StaticListNode*)(slist->node[object].data);
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
StaticListNode* LinkList_Delete (StaticList* list, int pos)
{
	staticlist_t   *slist = (staticlist_t *)list;	
	StaticListNode *ret   = NULL; 
	int i = 0;
	int current = 0;
	int object  = 0;

	if((slist != NULL) && (pos >= 0) && (pos < slist->header.data)) {
		slist->node[0] = slist->header; // ����ͷ��ֵ 
		
		for (i = 0; i < pos; i++) {
			current = slist->node[current].next;
		} 
		 
		// ���Ҵ�ɾ����Ŀ���λ����Ϣ 
		object = slist->node[current].next;
		
		// �ڵ����� 
		slist->node[current].next = slist->node[object].next;
		
		slist->node[0].data--;           // ɾ��һ���ڵ��Ӧ���ݼ���1 
		slist->header = slist->node[0];  // �������� 
		slist->node[object].next = -1;   // ����λ��־ 
		
		ret = (StaticListNode *)(slist->node[object].data); // ����ɾ���ڵ������ 
	}
	return ret;
}

