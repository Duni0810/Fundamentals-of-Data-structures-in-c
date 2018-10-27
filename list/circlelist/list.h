#ifndef __CIRCLELIST__
#define __CIRCLELIST__

#define OK      1
#define ERROR   0


typedef void CircleList; // ���ݷ�װ

typedef struct _tag_CircleListNode {
	struct _tag_CircleListNode *next;
} circlelist_node_t;


// 1.�������� 
CircleList *CircleList_Creat();

// 2.�ݻ����� 
int CircleList_Destroy(CircleList *list);

// 3.�������
int CircleList_clear(CircleList *list);

// 4.��ȡ����ĳ���
int CircleList_Length_Get(CircleList *list); 

// 5.����ڵ� 
int CircleList_Insert(CircleList *list, circlelist_node_t *node, int pos);

// 6.ɾ��λ�ýڵ� 
circlelist_node_t *CircleList_Delete(CircleList *list, int pos); 

// 7.ɾ����Ϣ�ڵ�
circlelist_node_t *CricleListNode_delete(CircleList *list, circlelist_node_t *node);
 
// 8.��ȡ�ڵ�
circlelist_node_t *CircleListNode_Get(CircleList *list, int pos); 

// 9. ��λѭ�������α�
circlelist_node_t *CircleList_reset(CircleList *list);

// 10.��ȡ�α�λ��
circlelist_node_t *CircleList_Current_Get(CircleList *list);

// 11.��ȡ�α���һ��λ��
circlelist_node_t *CircleList_Next_Get(CircleList *list);  
 
#endif
