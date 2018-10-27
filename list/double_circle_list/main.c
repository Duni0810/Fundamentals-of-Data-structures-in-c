#include <stdio.h>
#include <stdlib.h>
#include "CircleDoublelist.h"

typedef struct value {
	circle_doublelist_node_t header;
	int value;	
}value_t;

// ��ӡ���� 
void Circle_Double_List_Print(Circle_Double_List *list)
{
	int i = 0;
	value_t *pv = NULL;
	for (i = 0; i < Circle_Double_List_Length_Get(list); i++) {
		pv = (value_t *)Circle_Double_List_Get(list, i);
		printf("dat��%d \n", pv->value);	
	}
	 
}

// ������� 
int main(int argc, char *argv[]) {
	Circle_Double_List *list = Circle_Double_List_Create();
	
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
	
	
	// �α����
	printf("\n======slider test ======\n");
	
	// β�巨 
	Circle_Double_List_Insert(list, (circle_doublelist_node_t *)&v1, Circle_Double_List_Length_Get(list));
	Circle_Double_List_Insert(list, (circle_doublelist_node_t *)&v2, Circle_Double_List_Length_Get(list));
	Circle_Double_List_Insert(list, (circle_doublelist_node_t *)&v3, Circle_Double_List_Length_Get(list));
	Circle_Double_List_Insert(list, (circle_doublelist_node_t *)&v4, Circle_Double_List_Length_Get(list));
	Circle_Double_List_Insert(list, (circle_doublelist_node_t *)&v5, Circle_Double_List_Length_Get(list));
	
	// ��ӡ���� 
	Circle_Double_List_Print(list);
	
	Circle_Double_List_Reset(list);
	
	value_t *pv = (value_t *)Circle_Double_List_Current(list);
	printf("1.slider : %d \n", pv->value);
	

	Circle_Double_List_Pre(list);
	 
	pv = (value_t *)Circle_Double_List_Current(list);
	printf("2.slider : %d \n", pv->value);
		
	Circle_Double_List_Destroy(list);

	return 0;
}
