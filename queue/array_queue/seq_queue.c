#include <stdio.h>
#include <malloc.h>
#include "seq_queue.h"

/* ˳�����ʵ�� */

// ���ͱ仯����Ҫ��Ϊ�˱����ַ 
typedef unsigned int SeqQueue_Node;

// ͷ�ڵ���Ϣ 
typedef struct _tag_SeqQueue {
	int capacity;	// ����
	int length;		// ���ǳ���
	int front;		// ����ͷλ��
	int rear;		// ������ʵλ��
	SeqQueue_Node *node; //�ڵ��ַ���� 
} Seq_queue_t; 

// �������� 
void *SeqQueue_Creat(int capacity)
{
	Seq_queue_t *ret = NULL;
	
	// ����������С���ڴ�ռ� 
	if (capacity >= 0) {
		ret = (Seq_queue_t *)malloc(sizeof(Seq_queue_t) + 
									sizeof(SeqQueue_Node) * capacity);
	}
	
	// ��ʼ���ɹ� 
	if (ret != NULL) {
		ret->capacity = capacity;
		ret->front = 0;
		ret->rear  = 0;
		ret->length = 0;
		ret->node = (SeqQueue_Node *)(ret + 1); //ָ����һ�ڴ�ռ� 
	} 
	return ret; 
}

// �ݻٶ��� 
void SeqQueue_Destroy(Seq_Queue *queue)
{
	free(queue);
} 

// ��ն��� 
void SeqQueue_Clear(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	
	// ���ֻ��Ҫ�������е�������ռ��� 
	if (squeue != NULL) {
		squeue->front = 0;
		squeue->rear = 0;
		squeue->length = 0;
	}
}

// ���
int SeqQueue_Append(Seq_Queue *queue, void *item)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue; 
	int ret = ((squeue != NULL) && (item != NULL));
	
	// �������󳤶ȴ��� ����������Ҳ�ǲ��ɹ��� 
	ret = (ret && (squeue->length + 1 <= squeue->capacity));
	
	if (ret) {
		squeue->node[squeue->rear] = (SeqQueue_Node)item;
		squeue->rear = (squeue->rear + 1) % squeue->capacity;
		squeue->length++;
	}
	return ret;
}

// ����
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

// ��ȡ����ͷ����Ϣ
void *SeqQueue_Header(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	void *ret = NULL;
	
	if ((squeue != NULL) && (squeue->length > 0)) {
		ret = (void *)(squeue->node[squeue->front]);
	}
	
	return ret;
}

// ��ȡ���г���
int SeqQueue_Length_Get(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	int ret = -1;
	
	if (squeue != NULL) {
		ret = squeue->length; 
	}
	return  ret;
}

//��ȡ��������
int SeqQueue_Capacity(Seq_Queue *queue)
{
	Seq_queue_t *squeue = (Seq_queue_t *)queue;
	int ret = -1;
	
	if (squeue != NULL) {
		ret = squeue->capacity; 
	}
	return  ret;
}

