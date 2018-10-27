#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"

// ջ�������Ժ����� 
void Test()
{
	LinkStack *stack = LinkStack_Create();
	int a[20];
	int i = 0;
	
	// ��ֵ ��ѹջ 
	for (i = 0; i < 20; i++) {
		a[i] = i;
		LinkStack_Push(stack, &a[i]); 
	}
	
	printf("top:%d \n", *(int *)LinkStack_Top(stack));
	printf("stack size:%d \n", LinkStack_Size(stack));
	
	// ���ջ���� 
	//LinkStack_Clear(stack);
	
	// ��ջ����
	while(LinkStack_Size(stack) > 0) {
		printf("pop: %d \n", *(int *)LinkStack_Pop(stack));
	}
	
	LinkStack_Destroy(stack);
} 
 
int main(int argc, char *argv[]) 
{
	Test();
	 
	return 0;
}
