#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// ʹ�õݹ� ��������ַ��� 
void Reverse_Order (char *s)
{
	if ((s != NULL) && (*s != '\0')) {
		Reverse_Order(s + 1);
		printf("%c", *s);
	}
}

void test1() 
{
	Reverse_Order("12345");
    printf("\n");
}

// ʹ�õݹ�ʵ�ּ����ַ�����
int String_Num_Get(char *s)
{
	if(s == NULL) {
		return -1;
	} else if (*s == '\0') {
		return 0;
	} else {
		return String_Num_Get(s + 1) + 1;
	}
}

void test2()
{
	 int ret = String_Num_Get("1234567890");
	 printf("%d \n",ret);	
} 

//�õݹ�ʵ�� 쳲��������ļ���
int Fibonacci(int n) 
{
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else if (n > 1) {
		return (Fibonacci(n - 1) + Fibonacci(n - 2));
	}
}

void test3 ()
{
	int i = 0;
	int n = 10;
	for (i = 0; i <= 20; i++) {
		int ret = Fibonacci(i);
		printf("i = %d\tFibonacci : %d \n",i, ret);
	}	
}

// �õݹ�ʵ�ֺ�ŵ��
// n��ʾ��һ��λ�õ��ӵĸ����� ��������������ʾ a ͨ�� b ���� c 

static int g_hanoi_tick = 0; // ���� ��ŵ�����еĲ��� 
void Hanoi(int n, char a, char b, char c)
{
	g_hanoi_tick++;
	if (n == 1) {
		printf("%c -> %c\n", a, c); 
	} else {
		// �Ƚ����Ӱᵽ a->b ͨ��c 
		Hanoi(n - 1, a, c, b);
		
		printf("%c -> %c\n", a, c);
		
		// Ȼ�� a������ - > �� c
		Hanoi(n - 1, b, a, c);
	}
}

void test4() 
{
	Hanoi(3, 'a', 'b', 'c'); 
} 

// ȥ��ȫ����  
// ���ַ��� start λ�õ� end λ�õ�ȫ���� 
#define SWAP(a,b,c)  {c = a; a = b; b = c;}

// �Ƿ�������� 
char IsSwap(char *s, int start, int i) 
{
	// ��ǰ��Ƚϣ��������ͬ�� �Ͳ�ִ�л�λ 
    while (start < i) {
        if (s[start] == s[i])
            return 0; //false
        start++;
	}
	return 1;
}

void permutation(char *s, int start, int end) 
{
	if ((s != NULL) && (start >= 0) && (end >= start)) {
		// ֻ��һ��Ԫ�ص�ȫ���� ֻ��һ�� 
		if (start == end) {
			printf("%s \n", s);
		} else {
			int i = 0;
			
			for (i = start; i <= end; i++) {
				char temp;
			
				if (IsSwap(s, start, i)) {
					// ��λ 
					SWAP(s[start], s[i], temp);
				
					// ȫ���� 
					permutation(s, start + 1, end);
				
					// ������ 
					SWAP(s[start], s[i], temp);
					
				}
			}		
		}
	}
}

void test5()
{
	char s[] = "add";
    permutation(s, 0, strlen(s) - 1);
} 

// �˻ʺ����⣨�����㷨�� ��ֱ����Խ����ϲ����лʺ� 

#define N   8  // ���̴�С 
// ƫ������Ϣ�ṹ�� 
typedef struct _tag_Pos {
	int pos_i;
	int pos_j;
} pos_t;

// ���������ƫ���������ϣ��Ϸ������Ϸ�����Ϊ����Ļ�û��ɨ�裬���Կ��Բ����ж� 
static pos_t pos[] = {{-1, -1}, {-1, 0}, {-1, 1}};

// ���� 
static board [N + 2][N + 2];
static int count = 0;

// ��ʼ������ 
void init() 
{
	int i = 0;
	int j = 0;
	
	for (i = 0; i < N + 2; i++) {
		board[0][i] = '#';
		board[N+1][i] = '#';
		board[i][0] = '#';
		board[i][N+1] = '#';
		 
	} 
	
	for(i = 1; i < N + 1; i++) {
		for (j = 1; j < N + 1; j++) {
			board[i][j] = ' ';
		}		
	} 

} 

void display()
{
    int i = 0;
    int j = 0;
    
    for(i=0; i<N+2; i++)
    {
        for(j=0; j<N+2; j++)
        {
            printf("%c", board[i][j]);
        }
        
        printf("\n");
    }	
}

int check(int i, int j) 
{
	int ret = 1;
	int x = 0;
	
	// ������λ���ж� 
	for (x = 0; x < 3; x++) {
		int ni = i;
		int nj = j;
		
		while(ret && (board[ni][nj] != '#')) {
			ni = ni + pos[x].pos_i;
			nj = nj + pos[x].pos_j;
			
			ret = ret && (board[ni][nj] != '*');
		}
	} 
	
	return ret;
}
// �ӵڼ��п�ʼ raw 
void find (int row)
{
	int i = 0;
	// ���ɨ�赽��������Nʱ����ʾ 
	if (row > N) {
		count++;
		display();
		printf("Solution: %d\n\n", count);
		
	} else {
		for (i = 1; i <= N; i++) {
			if (check(row, i)) {
				board[row][i] = '*';
				
				// ����������һ�� 
				find (row + 1);
				
				// �ⲽ��ʵ�Ǳ���ԭʼ�ֳ� 
				// �����껹�ý�����ԭ�����ݵ�ʱ�򻹻��õ� 
				board[row][i] = ' '; 
			}
		} 
	} 
	
}

void test6()
{
	init();
	find(1);
}


void main (int argc, char *argv[]) {
	//test1(); 
	//test2();
	//test3();
	//test4();
	//test5();
	test6();
}














