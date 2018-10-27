#include <stdio.h>
#include <stdlib.h>

#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

typedef struct value {
	char a;
	short b;
	int c;
} value_t;


int main(int argc, char *argv[]) {
	printf("a:%d  b: %d   c :%d\n", offsetof(value_t, a),offsetof(value_t, b), offsetof(value_t, c));
	
	value_t value;
	
	printf("add_a:%d , add_b%d ,  add_c%d \n",&value.a , &value.b, &value.c);
	
	return 0;
}
