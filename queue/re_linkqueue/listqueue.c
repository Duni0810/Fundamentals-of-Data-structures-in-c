#include <stdio.h>
#include <malloc.h>
#include "list.h"
#include "listqueue.h"

// 链式信息 
typedef struct _tag_LinkQueueNode
{
    LinkListNode_t header;
    void* item;				// 保存信息 
} LinkQeueNode_t;

// 创建队列 
LinkQueue* LinkQueue_Create() 
{
    return LinkList_Create();
}

// 销毁队列 
void LinkQueue_Destroy(LinkQueue* queue)
{
    LinkQueue_Clear(queue);
    LinkList_Destroy(queue);
}

// 清空队列 
void LinkQueue_Clear(LinkQueue* queue) 
{
    while( LinkQueue_Length_Get(queue) > 0 )
    {
        LinkQueue_Retrieve(queue);
    }
}

// 入队 将信息插入队列空间的最后 
int LinkQueue_Append(LinkQueue* queue, void* item) 
{
    LinkQeueNode_t* node = (LinkQeueNode_t*)malloc(sizeof(LinkQeueNode_t));
    int ret = (item != NULL) && (node != NULL);
    
    if(ret)
    {
        node->item = item;
        
        ret = LinkList_Insert(queue, (LinkListNode_t*)node, LinkList_Length_Get(queue));
    }
    
    if(!ret)
    {
        free(node);
    }
    
    return ret;
}

// 出队   从第一个位置出列 
void* LinkQueue_Retrieve(LinkQueue* queue) 
{
    LinkQeueNode_t* node = (LinkQeueNode_t*)LinkList_Delete(queue, 0);
    void* ret = NULL;
    
    if(node != NULL) 
    {
        ret = node->item;
        
        free(node);
    }
    
    return ret;
}

// 返回队列的头信息 
void* LinkQueue_Header(LinkQueue* queue) 
{
    LinkQeueNode_t* node = (LinkQeueNode_t*)LinkList_Get(queue, 0);
    void* ret = NULL;
    
    if(node != NULL)
    {
        ret = node->item;
    }
    
    return ret;
}

// 返回队列的长度 
int LinkQueue_Length_Get(LinkQueue* queue) 
{
    return LinkList_Length_Get(queue);
}

