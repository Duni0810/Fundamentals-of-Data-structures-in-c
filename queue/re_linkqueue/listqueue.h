#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

typedef void LinkQueue;

// 创建队列 
LinkQueue* LinkQueue_Create();

// 销毁队列 
void LinkQueue_Destroy(LinkQueue* queue);

// 清空队列 
void LinkQueue_Clear(LinkQueue* queue);

// 入队 
int LinkQueue_Append(LinkQueue* queue, void* item);

// 出队 
void* LinkQueue_Retrieve(LinkQueue* queue);

// 得到队列头信息 
void* LinkQueue_Header(LinkQueue* queue);

// 队列长度 
int LinkQueue_Length_Get(LinkQueue* queue);

#endif


