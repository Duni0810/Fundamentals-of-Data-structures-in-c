#ifndef __LINKSTACK_H
#define __LINKSTACK_H

typedef void LinkStack;

// 1.¥¥Ω®’ª 
LinkStack *LinkStack_Create();

// 2. ¥›ªŸ’ª 
int LinkStack_Destroy(LinkStack *stack);

// 3.«Âø’’ª
int LinkStack_Clear(LinkStack *stack);

// 4.—π’ª
int LinkStack_Push(LinkStack* stack, void *item);

// 5.µØ’ª
LinkStack *LinkStack_Pop(LinkStack *stack); 

// 6.’ª∂• 
LinkStack *LinkStack_Top(LinkStack *stack);

// 7.’ª¥Û–°
int LinkStack_Size(LinkStack *stack);

#endif

