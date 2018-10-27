#include <stdio.h>
#include <stdlib.h>
#include "Doublelist.h"

typedef struct value {
	doublelist_node_t header;
	int value;	
}value_t;

// ��ӡ���� 
void DoubleList_Print(DoubleList *list)
{
	int i = 0;
	value_t *pv = NULL;
	for (i = 0; i < DoubleList_Length_Get(list); i++) {
		pv = (value_t *)DoubleList_Get(list, i);
		printf("dat��%d \n", pv->value);	
	}
	 
}

// ������� 
int main(int argc, char *argv[]) {
	DoubleList *list = DoubleList_Create();
	
	value_t v1; 
	value_t v2; 
	value_t v3; 
	value_t v4; 
	value_t v5; 
	
	v1.value = 1;
	v2.value = 2;
	v3.value = 3;
	v4.value = 4;
	v5.value = 5;
	
	// ͷ�巨 
	DoubleList_Insert(list, (doublelist_node_t *)&v1, 0);
	DoubleList_Insert(list, (doublelist_node_t *)&v2, 0);
	DoubleList_Insert(list, (doublelist_node_t *)&v3, 0);
	
	// ɾ����һ��Ԫ�� 
	DoubleList_Delete(list, 1); 
	
	// ��ӡ���� 
	DoubleList_Print(list);
	
	// ������� 
	DoubleList_Clear(list);
	
	// �α����
	printf("\n======slider test ======\n");
	
	// β�巨 
	DoubleList_Insert(list, (doublelist_node_t *)&v1, DoubleList_Length_Get(list));
	DoubleList_Insert(list, (doublelist_node_t *)&v2, DoubleList_Length_Get(list));
	DoubleList_Insert(list, (doublelist_node_t *)&v3, DoubleList_Length_Get(list));
	DoubleList_Insert(list, (doublelist_node_t *)&v4, DoubleList_Length_Get(list));
	DoubleList_Insert(list, (doublelist_node_t *)&v5, DoubleList_Length_Get(list));
	
	// ��ӡ���� 
	DoubleList_Print(list);
	
	DoubleList_Reset(list);
	
	value_t *pv = (value_t *)DoubleList_Current(list);
	printf("1.slider : %d \n", pv->value);
	
	// ���� 2 λ ����һλ 
	DoubleList_Next(list);
	DoubleList_Next(list);
	DoubleList_Pre(list);
	 
	pv = (value_t *)DoubleList_Current(list);
	printf("2.slider : %d \n", pv->value);
		
	DoubleList_Destroy(list);

	return 0;
}
