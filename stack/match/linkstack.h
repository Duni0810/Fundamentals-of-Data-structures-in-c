#ifndef __LINKSTACK_H
#define __LINKSTACK_H

typedef void LinkStack;

// 1.����ջ 
LinkStack *LinkStack_Create();

// 2. �ݻ�ջ 
int LinkStack_Destroy(LinkStack *stack);

// 3.���ջ
int LinkStack_Clear(LinkStack *stack);

// 4.ѹջ
int LinkStack_Push(LinkStack* stack, void *item);

// 5.��ջ
LinkStack *LinkStack_Pop(LinkStack *stack); 

// 6.ջ�� 
LinkStack *LinkStack_Top(LinkStack *stack);

// 7.ջ��С
int LinkStack_Size(LinkStack *stack);

#endif

