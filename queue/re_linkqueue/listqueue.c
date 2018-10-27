#include <stdio.h>
#include <malloc.h>
#include "list.h"
#include "listqueue.h"

// ��ʽ��Ϣ 
typedef struct _tag_LinkQueueNode
{
    LinkListNode_t header;
    void* item;				// ������Ϣ 
} LinkQeueNode_t;

// �������� 
LinkQueue* LinkQueue_Create() 
{
    return LinkList_Create();
}

// ���ٶ��� 
void LinkQueue_Destroy(LinkQueue* queue)
{
    LinkQueue_Clear(queue);
    LinkList_Destroy(queue);
}

// ��ն��� 
void LinkQueue_Clear(LinkQueue* queue) 
{
    while( LinkQueue_Length_Get(queue) > 0 )
    {
        LinkQueue_Retrieve(queue);
    }
}

// ��� ����Ϣ������пռ����� 
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

// ����   �ӵ�һ��λ�ó��� 
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

// ���ض��е�ͷ��Ϣ 
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

// ���ض��еĳ��� 
int LinkQueue_Length_Get(LinkQueue* queue) 
{
    return LinkList_Length_Get(queue);
}

