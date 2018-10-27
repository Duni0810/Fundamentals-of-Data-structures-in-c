#ifndef __DOUBLELIST_H
#define __DOUBLELIST_H


#define 		OK		1
#define			ERROR	0 


typedef void DoubleList;

typedef struct _tag_DoubleList_node {
	struct _tag_DoubleList_node *next;  // 双向链表后继 
	struct _tag_DoubleList_node *pre;	// 双向链表前驱 
} doublelist_node_t;

// 1.创建链表 
DoubleList* DoubleList_Create();

// 2.摧毁链表，释放空间 
int DoubleList_Destroy(DoubleList* list);

// 3.清空链表 
int DoubleList_Clear(DoubleList* list);

// 4. 获取链表大小 
int DoubleList_Length_Get(DoubleList* list);

// 5. 插入链表 
int DoubleList_Insert(DoubleList* list, doublelist_node_t* node, int pos);

// 6. 获取链表节点 
doublelist_node_t* DoubleList_Get(DoubleList* list, int pos);

// 7. 删除某个位置链表节点 
doublelist_node_t* DoubleList_Delete(DoubleList* list, int pos);

// 8. 删除链表的某一个节点 
doublelist_node_t* DoubleList_DeleteNode(DoubleList* list, doublelist_node_t* node);

// 9. 游标复位 
doublelist_node_t* DoubleList_Reset(DoubleList* list);

// 10. 获取当前位置的游标 
doublelist_node_t* DoubleList_Current(DoubleList* list);

// 11. 游标后移 
doublelist_node_t* DoubleList_Next(DoubleList* list);

// 12. 游标前移 
doublelist_node_t* DoubleList_Pre(DoubleList* list);






#endif 
