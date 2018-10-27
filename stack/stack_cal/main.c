#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"
#include "string.h"
/**
 * \brief 中缀表达式转后缀算法方案
 * 
 * 1.遍历中缀表达式中的数字和符号
 * 2.对于数字：直接输出
 * 3.对于符号：
 * 		（1）左括号：进栈
 * 		（2）运算符：与栈顶符号进行优先级比较
 *			（1）栈顶符号优先级低：进栈
 *			（2）栈顶符号优先级不低：将栈顶符号弹出并输出，之后进栈
 * 		（3）右括号：将栈顶符号弹出并输出，直到匹配左括号
 * 4.遍历结束：将栈中的所有符号弹出并输出
 */

// 数字之间用可空格隔开
static char temp_str[100] = {0}; // 后缀表达式字符保存 

// 是否为数字 
int IsNum (char c)
{
	return ((c >= '0') && (c <= '9'));		
} 

// 是否为符号 
int IsOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

// 是否为左符号 
int IsLeft(char c)
{
    return (c == '(');
}

// 是否为右符号 
int IsRight(char c)
{
    return (c == ')');
}

// 优先级判定 */ 的优先级高 +- 次 其他符号设置为最低 例如小括号（必须先进栈） 
int Priority(char c)
{
	// 其他符号优先级 
    int ret = 0;
    
    // +- 的优先级 
    if( (c == '+') || (c == '-') )
    {
        ret = 1;
    }
    
    // */ 优先级 
    if( (c == '*') || (c == '/') )
    {
        ret = 2;
    }
    
    return ret;
}

// 打印函数 
char output(char c)
{
    if( c != '\0')
    {
        printf("%c", c);
    }
    return c;
}

void transform(const char *code)
{
	int i = 0;	// 字符串扫描 
	int j = 0;	// 后缀输出保存 
	
	LinkStack *stack = LinkStack_Create();
	
	while (code[i] != '\0') {
		
		// 忽略空格 
		if (code[i] == ' ') {
			i++;
			continue;
		}
		
		// 为数字直接打印 
		 if (IsNum(code[i])) {
		 	if (IsOperator(temp_str[j - 1])) {
		 		temp_str[j++] = ' ';
			 }
		 	temp_str[j] = output(code[i]);
		 	j++;
		 	
		// 如果是运算符号 
		} else if (IsOperator(code[i])) {
			 
		 	// 扫描到的这个符号要比栈顶的优先级低 才进行压栈 否则就弹栈到低为止 
		 	while (Priority(code[i]) <= Priority((char)(int)LinkStack_Top(stack))) {
		 		temp_str[j++] = ' ';
		 		temp_str[j] = output((char)(int)LinkStack_Pop(stack));
		 		j++;
		 	} 
		 	
		 	temp_str[j++] = ' '; 
		 	// 压入符号到栈 
			LinkStack_Push(stack, (void *)(int)code[i]);
			
		// 如果是左符号 压栈 
		} else if(IsLeft(code[i])) {
			LinkStack_Push(stack, (void *)(int)code[i]);
			
		// 右符号 弹栈 （直到将左符号弹出为止） 
		} else if (IsRight(code[i])) {
			char c = '\0';
			
			while (!IsLeft((char)(int)LinkStack_Top(stack))) {
				temp_str[j++] = ' ';
				temp_str[j] = output((char)(int)LinkStack_Pop(stack));
				j++; 
			}
			
			// 将左符号弹出 
			LinkStack_Pop(stack);
			
		// 非法字符 报错推出 
		} else {
			printf("Invalid expression!\n");
            break;
		}
		i++; 
	} // 字符扫描完毕
	
	// 最后将栈空间全部弹出并打印
	while ((LinkStack_Size(stack) > 0) && (code[i] == '\0')) {
		temp_str[j++] = ' ';
		temp_str[j] = output((char)((int)LinkStack_Pop(stack)));
		j++;
	}
	printf("\n");
	LinkStack_Destroy(stack);	
}

/**
 * \brief 遍历后缀表达式中的数字和符号
 * 1.对于数字：进栈
 * 2.对于符号：
 * 	(1)从栈中弹出右操作数
 * 	(2)从栈中弹出左操作数
 * 	(3)根据符号进行运算
 * 	(4)将运算结果压入栈中
 * 3.遍历结束：栈中的唯一数字为计算结果
 */
int Value (char c) 
{
	return (c - '0');	
}

int Express(int left, int right, char op)
{
    int ret = 0;
    //printf("left: %d , right : %d \n", left, right);
    switch(op)
    {
        case '+':
            ret = left + right;
            break;
        case '-':
            ret = left - right;
            break;
        case '*':
            ret = left * right;
            break;
        case '/':
            ret = left / right;
            break;
        default:
            break;
    }
    
    return ret;
}

// 后缀计算 
int operation (char *code)
{
	int ret = 0;
	int i = 0;	// 字符串扫描 
	int temp_data = 0;
	int result;
	
	LinkStack *stack = LinkStack_Create();
	
	while (code[i] != '\0') {
		
		// 数字运算  这里我用 ' ' 做为分隔符 
		if ((IsNum(code[i])) || (code[i] == ' ')) {

			// 如果作为空格表示一段的数字扫描结束 
			if (code[i] == ' ') {
				
				// 如果是符号后面的空格 忽略 
				if (IsOperator(code[i - 1])) {
					i++;
					continue;
				}
				// 如果检测到的是符号前的空格 
				// 这里有一个bug 就是（void *）0 就是NULL,所以遇到0 会有bug 
				LinkStack_Push(stack, (void*)&temp_data);
				temp_data = 0;
				//flag = 0;
				i++;
				continue;
			}
			
			temp_data = temp_data * 10 + Value(code[i]);
			
		// 分别弹出右 左操作数 计算并将结果压入栈 
		} else if (IsOperator(code[i])) {
			
			int right = *(unsigned int *)LinkStack_Pop(stack);
            int left = *(unsigned int *)LinkStack_Pop(stack);
            
            result = Express(left, right, code[i]);	
			LinkStack_Push(stack, (void*)&result);
			i++;	
		} else {
			printf("Invalid expression!\n");
            break;
		} 
		
		i++;
	}
	
	if((LinkStack_Size(stack) == 1) && (code[i] == '\0')) {
        ret = *(unsigned int *)LinkStack_Pop(stack);
    } else {
        printf("Invalid expression!\n");
    }

	LinkStack_Destroy(stack);
	return ret;
}

int main(int argc, char *argv[]) {
    transform("88+(3+2)");
    printf("\ntemp_str:%s \n", temp_str);
    printf("ret: %d \n", operation(temp_str)); 
	return 0;
}


