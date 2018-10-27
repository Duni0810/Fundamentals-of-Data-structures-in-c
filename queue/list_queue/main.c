#include <stdio.h>
#include <stdlib.h>
#include "link_queue.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	LinkQueue *queue = LinkQueue_Create();
	int a[20] = {0};
	int i = 0;
	for (i = 0; i < 10; i++) {
		a[i] = i + 1;
		LinkQueue_Append(queue, (a + i));
	}
	
	printf("length  = %d \n", LinkQueue_Length(queue));
	
	while (LinkQueue_Length(queue) > 0) {
		printf("data = %d \n", *(int *)LinkQueue_Poll(queue));
	}
	LinkQueue_Destroy(queue);
	return 0;
}
