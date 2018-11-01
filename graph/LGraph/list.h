#ifndef __LIST_H_
#define __LIST_H_

/* void *  做一个万能类型的匹配 */ 
typedef void LinkList; 

typedef struct LinkListNode {
	struct LinkListNode *next; /* 指向下一个节点的地址 */
} LinkListNode_t;

/**
 * \brief 创建一个节点 
 *
 * \ret  节点的地址 
 */ 
LinkList* LinkList_Create (void);

/**
 * \brief 摧毁整个链表 
 *
 * \param list[in]   节点的地址 
 */ 
void LinkList_Destroy (LinkList* list);

/**
 * \brief 清空整个链表 
 *
 * \param list[in]  链表的表头 
 */ 
void LinkList_Clear (LinkList* list);

/**
 * \brief 获取链表长度 
 *
 * \param list[in]  链表的头节点 
 *
 * \ret 链表的长度 
 */ 
int LinkList_Length_Get (LinkList* list);

/**
 * \brief 插入链表 
 *
 * \param list[in]  链表的表头 
 * \param node[in]  待插入的链表
 * \param pos[in]   待插入的位置  
 *
 * \ret 1 ok  else error 
 */ 
int LinkList_Insert (LinkList* list, LinkListNode_t* node, int pos);

/**
 * \brief 获取链表节点信息
 * 
 * \param list[in]
 * \param pos[in]
 *
 * \ret 返回节点的地址 
 */
LinkListNode_t* LinkList_Get (LinkList* list, int pos);

/**
 * \brief 删除一个节点 
 * 
 * \param list[in]  头节点
 * \param pos[in]   待删除的节点位置 
 * 
 * \ret 要删除的节点地址 
 */ 
LinkListNode_t* LinkList_Delete (LinkList* list, int pos);



#endif 

