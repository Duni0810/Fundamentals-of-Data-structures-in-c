#ifndef __LINK_QUEUE_H__
#define __LINK_QUEUE_H__

typedef void LinkQueue;

// �������� 
LinkQueue* LinkQueue_Create();

// �ݻٶ��� 
void LinkQueue_Destroy(LinkQueue *queue);

// ��ն��� 
void LinkQueue_Clear(LinkQueue *queue);

// ��� 
int LinkQueue_Append(LinkQueue *queue, void *item);

// ���� 
void* LinkQueue_Poll(LinkQueue *queue);

// ��ȡ����ͷԪ�� 
void* LinkQueue_Header(LinkQueue *queue);

// ��ȡ���д�С 
int LinkQueue_Length(LinkQueue *queue);




#endif

