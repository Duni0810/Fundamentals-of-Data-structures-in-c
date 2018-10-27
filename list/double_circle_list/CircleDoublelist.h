#ifndef __CIRCLEDOUBLELIST_H
#define __CIRCLEDOUBLELIST_H


#define 		OK		1
#define			ERROR	0 


typedef void Circle_Double_List;

typedef struct _tag_Circle_DoubleList_node {
	struct _tag_Circle_DoubleList_node *next;  // ˫�������� 
	struct _tag_Circle_DoubleList_node *pre;	// ˫������ǰ�� 
} circle_doublelist_node_t;

// 1.�������� 
Circle_Double_List* Circle_Double_List_Create();

// 2.�ݻ������ͷſռ� 
int Circle_Double_List_Destroy(Circle_Double_List* list);

// 3.������� 
int Circle_Double_List_Clear(Circle_Double_List* list);

// 4. ��ȡ�����С 
int Circle_Double_List_Length_Get(Circle_Double_List* list);

// 5. �������� 
int Circle_Double_List_Insert(Circle_Double_List* list, circle_doublelist_node_t* node, int pos);

// 6. ��ȡ����ڵ� 
circle_doublelist_node_t* Circle_Double_List_Get(Circle_Double_List* list, int pos);

// 7. ɾ��ĳ��λ������ڵ� 
circle_doublelist_node_t* Circle_Double_List_Delete(Circle_Double_List* list, int pos);

// 8. ɾ�������ĳһ���ڵ� 
circle_doublelist_node_t* Circle_Double_List_DeleteNode(Circle_Double_List* list, circle_doublelist_node_t* node);

// 9. �α긴λ 
circle_doublelist_node_t* Circle_Double_List_Reset(Circle_Double_List* list);

// 10. ��ȡ��ǰλ�õ��α� 
circle_doublelist_node_t* Circle_Double_List_Current(Circle_Double_List* list);

// 11. �α���� 
circle_doublelist_node_t* Circle_Double_List_Next(Circle_Double_List* list);

// 12. �α�ǰ�� 
circle_doublelist_node_t* Circle_Double_List_Pre(Circle_Double_List* list);


#endif 

