#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"

// Õ»º¯Êý²âÊÔº¯Êý¿é 
void Test()
{
	LinkStack *stack = LinkStack_Create();
	int a[20];
	int i = 0;
	
	// ¸³Öµ ²¢Ñ¹Õ» 
	for (i = 0; i < 20; i++) {
		a[i] = i;
		LinkStack_Push(stack, &a[i]); 
	}
	
	printf("top:%d \n", *(int *)LinkStack_Top(stack));
	printf("stack size:%d \n", LinkStack_Size(stack));
	
	// Çå¿ÕÕ»²âÊÔ 
	//LinkStack_Clear(stack);
	
	// µ¯Õ»²âÊÔ
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
