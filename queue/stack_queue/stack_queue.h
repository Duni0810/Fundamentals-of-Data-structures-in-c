#ifndef __STACK_QUEUE_H__
#define __STACK_QUEUE_H__

typedef void SQueue;

SQueue *SQueue_Create();

void SQueue_Destroy(SQueue *queue);

void SQueue_Clear(SQueue *queue);

int SQueue_Append(SQueue *queue, void *item);

void *SQueue_Poll(SQueue *queue);

void *SQueue_Header(SQueue *queue);

int SQueue_Length(SQueue *queue);

#endif


