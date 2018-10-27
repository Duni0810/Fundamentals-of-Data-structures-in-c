#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 使用递归 逆序输出字符串 
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

// 使用递归实现计算字符个数
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

//用递归实现 斐波那契数的计算
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

// 用递归实现汉诺塔
// n表示第一个位置碟子的个数， 后面三个参数表示 a 通过 b 到达 c 

static int g_hanoi_tick = 0; // 计数 汉诺塔进行的步骤 
void Hanoi(int n, char a, char b, char c)
{
	g_hanoi_tick++;
	if (n == 1) {
		printf("%c -> %c\n", a, c); 
	} else {
		// 先将盘子搬到 a->b 通过c 
		Hanoi(n - 1, a, c, b);
		
		printf("%c -> %c\n", a, c);
		
		// 然后将 a的盘子 - > 到 c
		Hanoi(n - 1, b, a, c);
	}
}

void test4() 
{
	Hanoi(3, 'a', 'b', 'c'); 
} 

// 去重全排列  
// 对字符串 start 位置到 end 位置的全排列 
#define SWAP(a,b,c)  {c = a; a = b; b = c;}

// 是否进行排列 
char IsSwap(char *s, int start, int i) 
{
	// 与前面比较，如果有相同的 就不执行换位 
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
		// 只有一个元素的全排列 只有一个 
		if (start == end) {
			printf("%s \n", s);
		} else {
			int i = 0;
			
			for (i = start; i <= end; i++) {
				char temp;
			
				if (IsSwap(s, start, i)) {
					// 换位 
					SWAP(s[start], s[i], temp);
				
					// 全排列 
					permutation(s, start + 1, end);
				
					// 换回来 
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

// 八皇后问题（回溯算法） ，直线与对角线上不能有皇后 

#define N   8  // 棋盘大小 
// 偏移量信息结构体 
typedef struct _tag_Pos {
	int pos_i;
	int pos_j;
} pos_t;

// 三个方向的偏移量，左上，上方，右上方，因为下面的还没有扫描，所以可以不用判断 
static pos_t pos[] = {{-1, -1}, {-1, 0}, {-1, 1}};

// 棋盘 
static board [N + 2][N + 2];
static int count = 0;

// 初始化棋盘 
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
	
	// 三个方位的判断 
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
// 从第几行开始 raw 
void find (int row)
{
	int i = 0;
	// 如果扫描到行数大于N时候显示 
	if (row > N) {
		count++;
		display();
		printf("Solution: %d\n\n", count);
		
	} else {
		for (i = 1; i <= N; i++) {
			if (check(row, i)) {
				board[row][i] = '*';
				
				// 继续查找下一行 
				find (row + 1);
				
				// 这步其实是保留原始现场 
				// 查找完还得将他还原，回溯的时候还会用到 
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














