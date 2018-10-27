#ifndef __SEQ_QUEUE_H__
#define __SEQ_QUEUE_H__

typedef void Seq_Queue;

// �������� 
void *SeqQueue_Creat(int capacity);

// �ݻٶ��� 
void SeqQueue_Destroy(Seq_Queue *queue);

// ��ն��� 
void SeqQueue_Clear(Seq_Queue *queue);

// ���
int SeqQueue_Append(Seq_Queue *queue, void *item);

// ����
void *SeqQueue_Poll(Seq_Queue *queue);

// ��ȡ����ͷ����Ϣ
void *SeqQueue_Header(Seq_Queue *queue);

// ��ȡ���г���
int SeqQueue_Length_Get(Seq_Queue *queue);

//��ȡ��������
int SeqQueue_Capacity(Seq_Queue *queue); 



#endif

