#ifndef __CIRCLEDOUBLELIST_H
#define __CIRCLEDOUBLELIST_H


#define 		OK		1
#define			ERROR	0 


typedef void Circle_Double_List;

typedef struct _tag_Circle_DoubleList_node {
	struct _tag_Circle_DoubleList_node *next;  // 双向链表后继 
	struct _tag_Circle_DoubleList_node *pre;	// 双向链表前驱 
} circle_doublelist_node_t;

// 1.创建链表 
Circle_Double_List* Circle_Double_List_Create();

// 2.摧毁链表，释放空间 
int Circle_Double_List_Destroy(Circle_Double_List* list);

// 3.清空链表 
int Circle_Double_List_Clear(Circle_Double_List* list);

// 4. 获取链表大小 
int Circle_Double_List_Length_Get(Circle_Double_List* list);

// 5. 插入链表 
int Circle_Double_List_Insert(Circle_Double_List* list, circle_doublelist_node_t* node, int pos);

// 6. 获取链表节点 
circle_doublelist_node_t* Circle_Double_List_Get(Circle_Double_List* list, int pos);

// 7. 删除某个位置链表节点 
circle_doublelist_node_t* Circle_Double_List_Delete(Circle_Double_List* list, int pos);

// 8. 删除链表的某一个节点 
circle_doublelist_node_t* Circle_Double_List_DeleteNode(Circle_Double_List* list, circle_doublelist_node_t* node);

// 9. 游标复位 
circle_doublelist_node_t* Circle_Double_List_Reset(Circle_Double_List* list);

// 10. 获取当前位置的游标 
circle_doublelist_node_t* Circle_Double_List_Current(Circle_Double_List* list);

// 11. 游标后移 
circle_doublelist_node_t* Circle_Double_List_Next(Circle_Double_List* list);

// 12. 游标前移 
circle_doublelist_node_t* Circle_Double_List_Pre(Circle_Double_List* list);


#endif 

