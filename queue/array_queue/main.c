#include <stdio.h>
#include <stdlib.h>
#include "seq_queue.h" 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Seq_Queue *queue  = SeqQueue_Creat(20);
	
	int a[20] = {0};
	int i = 0;
	
	for (i = 0; i < 10; i++) {
		a[i] = i + 1;
		SeqQueue_Append(queue, (a + i)); 
	}
	
	printf("capcity  = %d \n", SeqQueue_Capacity(queue));
	printf("length  = %d \n", SeqQueue_Length_Get(queue));
	
	while (SeqQueue_Length_Get(queue) > 0) {
		printf("length  = %d \n", *(int *)SeqQueue_Poll(queue));
	}

	SeqQueue_Destroy(queue);
	
	return 0;
}
