#ifndef __STATIC_LIST_H_
#define __STATIC_LIST_H_

typedef void StaticList;
typedef void StaticListNode;

/**
 * \brief 创建一个节点 
 *
 * \ret  节点的地址 
 */ 
StaticList *StaticList_Create (int capacity);

/**
 * \brief 摧毁整个链表 
 *
 * \param list[in]   节点的地址 
 */ 
void StaticList_Destroy (StaticList* list);

/**
 * \brief 清空整个链表 
 *
 * \param list[in]  链表的表头 
 */ 
void StaticList_Clear (StaticList* list);

/**
 * \brief 获取链表长度 
 *
 * \param list[in]  链表的头节点 
 *
 * \ret 链表的长度 
 */ 
int StaticList_Length_Get (StaticList* list);

/**
 * \brief 获取链表大小 
 *
 * \param list[in]  链表的头节点 
 *
 * \ret 链表的大小 
 */ 
int StaticList_Capacity_Get (StaticList* list);
/**
 * \brief 插入链表 
 *
 * \param list[in]  链表的表头 
 * \param node[in]  待插入的链表
 * \param pos[in]   待插入的位置  
 *
 * \ret 1 ok  else error 
 */ 
int StaticList_Insert (StaticList* list, StaticListNode* node, int pos);

/**
 * \brief 获取链表节点信息
 * 
 * \param list[in]
 * \param pos[in]
 *
 * \ret 返回节点的地址 
 */
StaticListNode* StaticList_Get (StaticList* list, int pos);

/**
 * \brief 删除一个节点 
 * 
 * \param list[in]  头节点
 * \param pos[in]   待删除的节点位置 
 * 
 * \ret 要删除的节点地址 
 */ 
StaticListNode* LinkList_Delete (StaticList* list, int pos);



#endif 

