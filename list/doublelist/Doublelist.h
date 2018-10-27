#ifndef __DOUBLELIST_H
#define __DOUBLELIST_H


#define 		OK		1
#define			ERROR	0 


typedef void DoubleList;

typedef struct _tag_DoubleList_node {
	struct _tag_DoubleList_node *next;  // ˫�������� 
	struct _tag_DoubleList_node *pre;	// ˫������ǰ�� 
} doublelist_node_t;

// 1.�������� 
DoubleList* DoubleList_Create();

// 2.�ݻ������ͷſռ� 
int DoubleList_Destroy(DoubleList* list);

// 3.������� 
int DoubleList_Clear(DoubleList* list);

// 4. ��ȡ�����С 
int DoubleList_Length_Get(DoubleList* list);

// 5. �������� 
int DoubleList_Insert(DoubleList* list, doublelist_node_t* node, int pos);

// 6. ��ȡ����ڵ� 
doublelist_node_t* DoubleList_Get(DoubleList* list, int pos);

// 7. ɾ��ĳ��λ������ڵ� 
doublelist_node_t* DoubleList_Delete(DoubleList* list, int pos);

// 8. ɾ�������ĳһ���ڵ� 
doublelist_node_t* DoubleList_DeleteNode(DoubleList* list, doublelist_node_t* node);

// 9. �α긴λ 
doublelist_node_t* DoubleList_Reset(DoubleList* list);

// 10. ��ȡ��ǰλ�õ��α� 
doublelist_node_t* DoubleList_Current(DoubleList* list);

// 11. �α���� 
doublelist_node_t* DoubleList_Next(DoubleList* list);

// 12. �α�ǰ�� 
doublelist_node_t* DoubleList_Pre(DoubleList* list);






#endif 
