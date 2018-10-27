#include <stdio.h>
#include <malloc.h>
#include "seq_queue.h"

/* 顺序队列实现 */

// 类型变化，主要是为了保存地址 
typedef unsigned int SeqQueue_Node;

// 头节点信息 
typedef struct _tag_SeqQueue {
	int capacity;	// 容量
	int length;		// 真是长度
	int front;		// 队列头位置
	int rear;		// 队列真实位置
	SeqQueue_Node *node; //节点地址保存 
} Seq_queue_t; 

// 创建队列 
void *SeqQueue_Creat(int capacity)
{
	Seq_queue_t *ret = NULL;
	
	// 申请连续大小的内存空间 
	if (capacity >= 0) {
		ret = (Seq_queue_t *)malloc(sizeof(Seq_queue_t) + 
									sizeof(SeqQueue_Node) * capacity);
	}
	
	// 初始化成功 
	if (ret != NULL) {
		ret->capacity = capacity;
		ret->front = 0;
		ret->rear  = 0;
		ret->length = 0;
		ret->node = (SeqQueue_Node *)(ret + 1); //指向下一内存空间 
	} 
	return ret; 
}

// 摧毁队列 
void SeqQueue_Destroy(Seq_Queue *queue)
{
	free(queue);
} 

// 清空队列 
void SeqQueue_Clear(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	
	// 清空只需要将队列中的数据清空即可 
	if (squeue != NULL) {
		squeue->front = 0;
		squeue->rear = 0;
		squeue->length = 0;
	}
}

// 入队
int SeqQueue_Append(Seq_Queue *queue, void *item)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue; 
	int ret = ((squeue != NULL) && (item != NULL));
	
	// 如果加入后长度大于 队列容量，也是不成功的 
	ret = (ret && (squeue->length + 1 <= squeue->capacity));
	
	if (ret) {
		squeue->node[squeue->rear] = (SeqQueue_Node)item;
		squeue->rear = (squeue->rear + 1) % squeue->capacity;
		squeue->length++;
	}
	return ret;
}

// 出队
void *SeqQueue_Poll(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	void *ret = SeqQueue_Header(queue);
	
	if (ret != NULL) {
		squeue->front = (squeue->front + 1) % squeue->capacity;
		squeue->length--;
	}
	
	return ret;
	
}

// 获取队列头的信息
void *SeqQueue_Header(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	void *ret = NULL;
	
	if ((squeue != NULL) && (squeue->length > 0)) {
		ret = (void *)(squeue->node[squeue->front]);
	}
	
	return ret;
}

// 获取队列长度
int SeqQueue_Length_Get(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	int ret = -1;
	
	if (squeue != NULL) {
		ret = squeue->length; 
	}
	return  ret;
}

//获取队列容量
int SeqQueue_Capacity(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	int ret = -1;
	
	if (squeue != NULL) {
		ret = squeue->capacity; 
	}
	return  ret;
}

