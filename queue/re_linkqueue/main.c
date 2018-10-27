#include <stdio.h>
#include <stdlib.h>
#include "listqueue.h"

int main(int argc, char *argv[]) {
	
	LinkQueue *queue = LinkQueue_Create();
	
	int value[20] = {0};
	int i = 0;
	
	// 入队 
	for (i = 0; i < 20; i++) {
		value[i] = i + 1;
		LinkQueue_Append(queue, value + i);
	}

	printf("Header: %d\n", *(int*)LinkQueue_Header(queue));
    printf("Length: %d\n", LinkQueue_Length_Get(queue));

    // 出队列 
    while( LinkQueue_Length_Get(queue) > 0)
    {
        printf("Retrieve: %d\n", *(int*)LinkQueue_Retrieve(queue));
    }

	LinkQueue_Destroy(queue);
	return 0;
}
