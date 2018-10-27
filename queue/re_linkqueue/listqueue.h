#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

typedef void LinkQueue;

// �������� 
LinkQueue* LinkQueue_Create();

// ���ٶ��� 
void LinkQueue_Destroy(LinkQueue* queue);

// ��ն��� 
void LinkQueue_Clear(LinkQueue* queue);

// ��� 
int LinkQueue_Append(LinkQueue* queue, void* item);

// ���� 
void* LinkQueue_Retrieve(LinkQueue* queue);

// �õ�����ͷ��Ϣ 
void* LinkQueue_Header(LinkQueue* queue);

// ���г��� 
int LinkQueue_Length_Get(LinkQueue* queue);

#endif


