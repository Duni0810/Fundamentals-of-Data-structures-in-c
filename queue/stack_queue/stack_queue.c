#include <stdio.h>
#include <malloc.h>
#include "stack_queue.h"
#include "linkstack.h"

// 用两个栈实现的队列 
// 1.准备两个栈用于实现队列： instack 和 outstack
// 2.当有新元素入队时：将其压入instack中
// 3.当需要出队时
//	(1) 当outstack为空时：
//		1) 将instack中的元素逐个弹出压入outstack中
//		2) 将outstack的栈顶元素弹出
//	(2) 当outstack不为空时：
//		直接将outstack的栈顶元素弹出
  
typedef struct _tag_SQueue {
	// 两个栈的栈地址 
	LinkStack *instack;
	LinkStack *outstack;
} SQueue_t;

// 创建队列  
SQueue *SQueue_Create()
{
	SQueue_t *ret = (SQueue_t *)malloc(sizeof(SQueue_t));
	
	if (ret != NULL) {
		ret->instack = LinkStack_Create();
		ret->outstack =  LinkStack_Create();
		
		// 只要有一方申请失败都表示失败 
		if ((ret->instack == NULL) || (ret->outstack == NULL)) {
			LinkStack_Destroy(ret->instack);
			LinkStack_Destroy(ret->outstack);
			
			free(ret);
			ret = NULL;
		} 
		return ret;
	} 
}

//  摧毁队列 
void SQueue_Destroy(SQueue *queue)
{
	SQueue_Clear(queue);
	free(queue);
	 
} 

// 清空队列 
void SQueue_Clear(SQueue *queue)
{
	SQueue_t *squeue = (SQueue_t *)queue;
	
	if (queue != NULL) {
		LinkStack_Clear(squeue->instack);
		LinkStack_Clear(squeue->outstack);
	}
} 

// 入队 
// 入队直接压入 instack 上 
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
		// 如果outtack 为空 将 instack 元素弹出压入 outstack 中 再将第一个弹出 
		if (LinkStack_Size(squeue->outstack) == 0) {
			//弹出instack 并压入outstack 
			while (LinkStack_Size(squeue->instack) > 0) {
				LinkStack_Push(squeue->outstack, LinkStack_Pop(squeue->instack));
			} 
		} // outstack 是否为空 
		ret = LinkStack_Pop(squeue->outstack); 
	}
	 
	return ret;
} 

void *SQueue_Header(SQueue *queue)
{
	SQueue_t *squeue = (SQueue_t *)queue;
	void *ret = NULL;
	
	if (squeue != NULL) {
		// 如果outtack 为空 将 instack 元素弹出压入 outstack 中 再将第一个弹出 
		if (LinkStack_Size(squeue->outstack) == 0) {
			//弹出instack 并压入outstack 
			while (LinkStack_Size(squeue->instack) > 0) {
				LinkStack_Push(squeue->outstack, LinkStack_Pop(squeue->instack));
			} 
		} // outstack 是否为空 
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

