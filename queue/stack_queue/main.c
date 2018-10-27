#include <stdio.h>
#include <stdlib.h>
#include "stack_queue.h"


int main(int argc, char *argv[]) {
	SQueue * queue = SQueue_Create();
	int a[20] = {0};
	int i  =0;
	
	for (i = 0; i < 10; i++) {
		a[i] = i + 1;
		SQueue_Append(queue, (a + i));
	}
	
	printf("length: %d \n", SQueue_Length(queue));
	printf("header: %d \n", *(int *)SQueue_Header(queue));
	
	while (SQueue_Length(queue) > 0) {
		printf("data: %d \n", *(int *)SQueue_Poll(queue));
	}
	
	printf("length: %d \n", SQueue_Length(queue));
	
	SQueue_Destroy(queue);
	return 0;
}
