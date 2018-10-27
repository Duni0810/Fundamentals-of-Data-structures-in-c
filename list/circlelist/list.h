#ifndef __CIRCLELIST__
#define __CIRCLELIST__

#define OK      1
#define ERROR   0


typedef void CircleList; // 数据封装

typedef struct _tag_CircleListNode {
	struct _tag_CircleListNode *next;
} circlelist_node_t;


// 1.创建链表 
CircleList *CircleList_Creat();

// 2.摧毁链表 
int CircleList_Destroy(CircleList *list);

// 3.清空链表
int CircleList_clear(CircleList *list);

// 4.获取链表的长度
int CircleList_Length_Get(CircleList *list); 

// 5.插入节点 
int CircleList_Insert(CircleList *list, circlelist_node_t *node, int pos);

// 6.删除位置节点 
circlelist_node_t *CircleList_Delete(CircleList *list, int pos); 

// 7.删除信息节点
circlelist_node_t *CricleListNode_delete(CircleList *list, circlelist_node_t *node);
 
// 8.获取节点
circlelist_node_t *CircleListNode_Get(CircleList *list, int pos); 

// 9. 复位循环链表游标
circlelist_node_t *CircleList_reset(CircleList *list);

// 10.获取游标位置
circlelist_node_t *CircleList_Current_Get(CircleList *list);

// 11.获取游标下一个位置
circlelist_node_t *CircleList_Next_Get(CircleList *list);  
 
#endif
