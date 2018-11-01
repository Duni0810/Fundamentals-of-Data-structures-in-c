#ifndef __LINK_QUEUE_H__
#define __LINK_QUEUE_H__

typedef void LinkQueue;

// 创建队列 
LinkQueue* LinkQueue_Create();

// 摧毁队列 
void LinkQueue_Destroy(LinkQueue *queue);

// 清空队列 
void LinkQueue_Clear(LinkQueue *queue);

// 入队 
int LinkQueue_Append(LinkQueue *queue, void *item);

// 出队 
void* LinkQueue_Poll(LinkQueue *queue);

// 获取队列头元素 
void* LinkQueue_Header(LinkQueue *queue);

// 获取队列大小 
int LinkQueue_Length(LinkQueue *queue);




#endif

