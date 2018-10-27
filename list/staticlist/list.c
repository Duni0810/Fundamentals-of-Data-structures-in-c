#include <stdio.h>
#include <malloc.h> 
#include "list.h"
 
// 节点定义 
typedef struct _tag_StaticListNode {
	unsigned int data;   // 数据保存 
	int next;			       // 保存下一个数据的位置 
} staticlistnode_t;

// 静态链表的结构体的定义 
typedef struct _tag_StaticList {
	int              capacity;   // 表示静态链表最多能容纳多少个元素 
	staticlistnode_t header;     // 保存头节点
	staticlistnode_t node[];     // 保存数据的柔性数组 
} staticlist_t;


/**
 * \brief 创建一个节点 
 *
 * \param capacity[in]   静态链表的容量 
 *
 * \ret  节点的地址 
 */ 
StaticList *StaticList_Create (int capacity)
{
	staticlist_t *ret = NULL;  // 创建链表 
    int i = 0;
	
	if (capacity >= 0) {
		// 动态的创建一个静态链表  我们要申请的空间为链表的大小 表头 + 需要创建链表的空间大小
		// + 1 主要是因为有一个元素作为了表头，为了替上他的位置。所以+1 
		ret = (staticlist_t *)malloc(sizeof(staticlist_t) + sizeof(staticlistnode_t) * (capacity + 1));
	} 
	if (NULL != ret) {
	
		ret->capacity 	 = capacity;
		ret->header.data = 0;
		ret->header.next = 0; 
		
		for(i = 1; i <= ret->capacity; i++) {
			ret->node[i].next = -1;  // 新建空间时，所有的next域指向-1. 
		}
	} 
	return ret;
}

/**
 * \brief 摧毁整个链表 
 *
 * \param list[in]   节点的地址 
 */ 
void StaticList_Destroy (StaticList* list)
{
	free(list); 
}

/**
 * \brief 清空整个链表 
 *
 * \param list[in]  链表的表头 
 */ 
void StaticList_Clear (StaticList* list)
{
	int i = 0; 
	// 由于我们做了一个封装所以开始的时候我们应该做一个类型的转化
	staticlist_t * slist = (staticlist_t *)list; 
	
	if (NULL != slist) {
		// 我们往往将首元素的数据表示为链表的长度 
		slist->header.data = 0;
		slist->header.next = 0; 
		
		for(i = 1; i <= slist->capacity; i++) {
			slist->node[i].next = -1;  // clear操作时，所有的next域指向-1. 
		}
	}
} 

/**
 * \brief 获取链表长度 （实际长度） 
 *
 * \param list[in]  链表的头节点 
 *
 * \ret 链表的长度 
 */ 
int StaticList_Length_Get (StaticList* list)
{
	staticlist_t *slist = (staticlist_t *)list;
	int ret = -1;
	 
	// 合法性判断
	if (NULL != slist) {
		ret = slist->header.data;
	} 
	 
	return ret; 
} 

/**
 * \brief 获取链表最大容量大小 
 *
 * \param list[in]  链表的头节点 
 *
 * \ret 链表的大小 
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
 * \brief 插入链表 
 *
 * \param list[in]  链表的表头 
 * \param node[in]  待插入的链表
 * \param pos[in]   待插入的位置  
 *
 * \ret 1 ok  else error 
 */ 
int StaticList_Insert (StaticList* list, StaticListNode* node, int pos)
{
	staticlist_t *slist = (staticlist_t *)list;
	int ret             = ((slist != NULL) && (node != NULL));
	int i               = 0; 
	int index           = 0; // 用与记录找到空闲位置的标识
	int current         = 0;
	 
	ret = ret && (slist->header.data + 1 <= slist->capacity); // 数据大小不能溢出
	ret = ret && (pos >= 0) && (pos < slist->capacity); 
	
	if (ret) {
		
		for (i = 0; i < slist->capacity; i++) { // 遍历空闲数值， 找一个可插入的空闲位置 
	
			if (slist->node[i].next == -1) {    // 找到空闲位置
				index = i;                      // 记录空闲位置 ,并且退出查找空闲位置 
				break; 
			}
		} 
		
		slist->node[index].data = (unsigned int)node;    // 给结构体节点信息赋值 
		
		
		slist->node[0] = slist->header;                  // 赋值静态链表头 
		
		for (i = 0; (i < pos) && (slist->node[current].next != 0); i++) {
			current = slist->node[current].next;   
		} 
		
		slist->node[index].next   = slist->node[current].next; 
		slist->node[current].next = index;
		
		slist->node[0].data++;          // 插入完成，记得数据元素得+1 
		slist->header = slist->node[0]; // 更新链表 
	}
	
	return ret;
}

/**
 * \brief 获取链表节点信息
 * 
 * \param list[in]
 * \param pos[in]
 *
 * \ret 返回节点的地址 
 */
StaticListNode* StaticList_Get (StaticList* list, int pos)
{
	int i       = 0;
	int current = 0; 
	int object  = 0; 
	StaticListNode *ret = NULL;
	staticlist_t *slist = (staticlist_t *)slist;
	
	// 合法性判断 
	if ((NULL != slist) && (pos >= 0) && (pos < slist->header.data)) {

		slist->node[0] = slist->header; // 第0 个元素代表我们的头节点 
		
		for (i = 0; i < pos; i++) {
			// next 存放着下一个元素的数字下标 主要是找到下标 因为第一个元素是头，所以不算 
			current = slist->node[current].next;
		} 
		//  下标 
		object = slist->node[current].next;
		
		// 获取的元素 
		ret = (StaticListNode*)(slist->node[object].data);
	}
	return ret;
}

/**
 * \brief 删除一个节点 
 * 
 * \param list[in]  头节点
 * \param pos[in]   待删除的节点位置 
 * 
 * \ret 要删除的节点地址 
 */ 
StaticListNode* LinkList_Delete (StaticList* list, int pos)
{
	staticlist_t   *slist = (staticlist_t *)list;	
	StaticListNode *ret   = NULL; 
	int i = 0;
	int current = 0;
	int object  = 0;

	if((slist != NULL) && (pos >= 0) && (pos < slist->header.data)) {
		slist->node[0] = slist->header; // 链表头赋值 
		
		for (i = 0; i < pos; i++) {
			current = slist->node[current].next;
		} 
		 
		// 查找待删除的目标的位置信息 
		object = slist->node[current].next;
		
		// 节点连接 
		slist->node[current].next = slist->node[object].next;
		
		slist->node[0].data--;           // 删除一个节点对应数据减少1 
		slist->header = slist->node[0];  // 更新链表 
		slist->node[object].next = -1;   // 空闲位标志 
		
		ret = (StaticListNode *)(slist->node[object].data); // 返回删除节点的数据 
	}
	return ret;
}

