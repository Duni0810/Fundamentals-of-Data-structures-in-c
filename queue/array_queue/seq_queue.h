#ifndef __SEQ_QUEUE_H__
#define __SEQ_QUEUE_H__

typedef void Seq_Queue;

// 创建队列 
void *SeqQueue_Creat(int capacity);

// 摧毁队列 
void SeqQueue_Destroy(Seq_Queue *queue);

// 清空队列 
void SeqQueue_Clear(Seq_Queue *queue);

// 入队
int SeqQueue_Append(Seq_Queue *queue, void *item);

// 出队
void *SeqQueue_Poll(Seq_Queue *queue);

// 获取队列头的信息
void *SeqQueue_Header(Seq_Queue *queue);

// 获取队列长度
int SeqQueue_Length_Get(Seq_Queue *queue);

//获取队列容量
int SeqQueue_Capacity(Seq_Queue *queue); 



#endif

