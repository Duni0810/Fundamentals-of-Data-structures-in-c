#include <stdio.h>
#include <malloc.h>
#include "link_queue.h" 

// ��ʽ�ڵ���Ϣ 
typedef struct _tag_LinkQueue_Node {
	struct _tag_LinkQueue_Node *next;
	void *item;
} LinkQueue_Node_t;

// ��ʽͷ��Ϣ 
typedef struct _tag_LinkQueue {
	LinkQueue_Node_t *front;
	LinkQueue_Node_t *rear;
	int length;
} LinkQueue_t;


// �������� 
LinkQueue* LinkQueue_Create()
{
	LinkQueue_t *ret = (LinkQueue_t *)malloc(sizeof(LinkQueue_t));
	if (ret != NULL) {
		ret->length = 0;
		ret->front = NULL;
		ret->rear = NULL;
	}
	return ret;
}
 

// �ݻٶ��� 
void LinkQueue_Destroy(LinkQueue *queue)
{
	LinkQueue_Clear(queue);
	free(queue);
}

// ��ն��� 
void LinkQueue_Clear(LinkQueue *queue)
{
	while(LinkQueue_Length(queue) > 0) {
		LinkQueue_Poll(queue);
	}
}

// ��� 
int LinkQueue_Append(LinkQueue *queue, void *item)
{
	LinkQueue_t *squeue = (LinkQueue_t *)queue;
	LinkQueue_Node_t *node = (LinkQueue_Node_t *)malloc(sizeof(LinkQueue_Node_t));
	int ret = ((squeue != NULL) && (item != NULL) && (node != NULL));
	
	if (ret) {
		node->item = item;
		
		// �������Ϊ�� ԭ���Ѿ���Ԫ�� ���������λ�� ��rearָ�����λ�� 
		if (squeue->length > 0) {
			squeue->rear->next = node;
			squeue->rear = node; 
			node->next = NULL;
		} else {
			squeue->front = node;
			squeue->rear = node;
			node->next = NULL;
		}
		squeue->length++;
	}
	
	if (!ret) {
		free(node);
	}
	
	return ret;
}

// ���� 
void *LinkQueue_Poll(LinkQueue *queue)
{
	LinkQueue_t *squeue = (LinkQueue_t *)queue;
	LinkQueue_Node_t *node = NULL;
	void *ret = NULL;
	if ((squeue != NULL) && (squeue->length > 0)) {
		node = squeue->front;
		// front �α���� 
		squeue->front = node->next;
		
		ret = node->item;
		
		free(node);
		
		squeue->length--;
		
		if (squeue->length == 0) {
			squeue->front = NULL;
			squeue->rear = NULL;
		} 
	}
	return ret;
}

// ��ȡ����ͷԪ�� 
void *LinkQueue_Header(LinkQueue *queue)
{
	LinkQueue_t *squeue = (LinkQueue_t *)queue;
	void *ret = NULL;
	if (squeue != NULL) {
		ret = squeue->front;
	}
	return ret;
}

// ��ȡ���д�С 
int LinkQueue_Length(LinkQueue *queue)
{
	LinkQueue_t *squeue = (LinkQueue_t *)queue;
	int ret = -1;
	if (squeue != NULL) {
		ret = squeue->length;
	}
	return ret;
}


