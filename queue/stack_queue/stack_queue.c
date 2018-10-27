#include <stdio.h>
#include <malloc.h>
#include "stack_queue.h"
#include "linkstack.h"

// ������ջʵ�ֵĶ��� 
// 1.׼������ջ����ʵ�ֶ��У� instack �� outstack
// 2.������Ԫ�����ʱ������ѹ��instack��
// 3.����Ҫ����ʱ
//	(1) ��outstackΪ��ʱ��
//		1) ��instack�е�Ԫ���������ѹ��outstack��
//		2) ��outstack��ջ��Ԫ�ص���
//	(2) ��outstack��Ϊ��ʱ��
//		ֱ�ӽ�outstack��ջ��Ԫ�ص���
  
typedef struct _tag_SQueue {
	// ����ջ��ջ��ַ 
	LinkStack *instack;
	LinkStack *outstack;
} SQueue_t;

// ��������  
SQueue *SQueue_Create()
{
	SQueue_t *ret = (SQueue_t *)malloc(sizeof(SQueue_t));
	
	if (ret != NULL) {
		ret->instack = LinkStack_Create();
		ret->outstack =  LinkStack_Create();
		
		// ֻҪ��һ������ʧ�ܶ���ʾʧ�� 
		if ((ret->instack == NULL) || (ret->outstack == NULL)) {
			LinkStack_Destroy(ret->instack);
			LinkStack_Destroy(ret->outstack);
			
			free(ret);
			ret = NULL;
		} 
		return ret;
	} 
}

//  �ݻٶ��� 
void SQueue_Destroy(SQueue *queue)
{
	SQueue_Clear(queue);
	free(queue);
	 
} 

// ��ն��� 
void SQueue_Clear(SQueue *queue)
{
	SQueue_t *squeue = (SQueue_t *)queue;
	
	if (queue != NULL) {
		LinkStack_Clear(squeue->instack);
		LinkStack_Clear(squeue->outstack);
	}
} 

// ��� 
// ���ֱ��ѹ�� instack �� 
int SQueue_Append(SQueue *queue, void *item)
{
	SQueue_t *squeue = (SQueue_t *)queue;
	int ret = ((squeue != NULL) && (item != NULL));
	
	if (ret) {
		ret = LinkStack_Push(squeue->instack, item);
	}
	return ret; 
} 

void *SQueue_Poll(SQueue *queue)
{
	SQueue_t *squeue = (SQueue_t *)queue;
	void *ret = NULL;
	
	if (squeue != NULL) {
		// ���outtack Ϊ�� �� instack Ԫ�ص���ѹ�� outstack �� �ٽ���һ������ 
		if (LinkStack_Size(squeue->outstack) == 0) {
			//����instack ��ѹ��outstack 
			while (LinkStack_Size(squeue->instack) > 0) {
				LinkStack_Push(squeue->outstack, LinkStack_Pop(squeue->instack));
			} 
		} // outstack �Ƿ�Ϊ�� 
		ret = LinkStack_Pop(squeue->outstack); 
	}
	 
	return ret;
} 

void *SQueue_Header(SQueue *queue)
{
	SQueue_t *squeue = (SQueue_t *)queue;
	void *ret = NULL;
	
	if (squeue != NULL) {
		// ���outtack Ϊ�� �� instack Ԫ�ص���ѹ�� outstack �� �ٽ���һ������ 
		if (LinkStack_Size(squeue->outstack) == 0) {
			//����instack ��ѹ��outstack 
			while (LinkStack_Size(squeue->instack) > 0) {
				LinkStack_Push(squeue->outstack, LinkStack_Pop(squeue->instack));
			} 
		} // outstack �Ƿ�Ϊ�� 
		ret = LinkStack_Top(squeue->outstack); 
	}
	 
	return ret;
}

int SQueue_Length(SQueue *queue)
{
	SQueue_t *squeue = (SQueue_t *)queue;
	int ret = -1;
	if (squeue != NULL) {
		ret = LinkStack_Size(squeue->instack) + LinkStack_Size(squeue->outstack);
	}
	
	return ret; 
} 

