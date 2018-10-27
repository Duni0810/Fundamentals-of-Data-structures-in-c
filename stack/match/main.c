#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"

/**
 * \brief 符号匹配算法思路
 *
 * 1. 从第一个字符开始扫描 
 * 2. 当遇到普通字符时忽略，当遇到左符号时压入栈 
 * 3. 当遇到右符号时从栈中弹出栈顶符号 
 * 4. 进行匹配 
 *		（1） 匹配成功：继续读入下一个字符 
 * 		（2） 匹配失败：立即停止，并报错
 * 5. 结束：
 *		（1） 成功：所有字符扫描完毕，且栈为空
 *		（2） 匹配失败或者所有字符串扫描完毕之后栈不为空 
 */ 

// 左符号 
int IsLeft(char c)
{
	int ret = 0;
	
	switch (c) 
	{
		case '<':
		case '(':
		case '[':
		case '{':
		case '\"':
		case '\'':
			ret = 1;
			break;
			
		default :
			ret = 0;
			break;
	}
	return ret;	
}

// 右符号 
int IsRight(char c)
{
	int ret = 0;
	
	switch (c) 
	{
		case '>':
		case ')':
		case ']':
		case '}':
		case '\"':
		case '\'':
			ret = 1;
			break;
			
		default :
			ret = 0;
			break;
	}
	return ret;	
}

int Char_Match (char left, char right)
{
	int ret = 0;
	
	switch(left)
	{
		case '<':
			ret = (right == '>');
			break;
		case '(':
			ret = (right == ')');
			break;
		case '[':
			ret = (right == ']');
			break;
		case '{':
			ret = (right == '}');
			break;
		case '\"':
			ret = (right == '\"');
			break;
		case '\'':
			ret = (right == '\'');
			break;
			
		default :
			ret = 0;
			break;
	}
	
	return ret;
} 


int scanner(const char *code)
{
	LinkStack* stack = LinkStack_Create();
	int i = 0;
	int ret = 0;
	
	int sign_a = 0;  // 单引号 
	int sign_b = 0;  // 双引号 
	
	// 循环字符串（文本信息） 
	while (code[i] != '\0') {
		if (IsLeft(code[i])) {
			LinkStack_Push(stack, (void *)(code + i)); 
			
			// 单引号为 0 表示第一次 
			if ((code[i] == '\'') && sign_a == 0) {
				sign_a += 1;
				i++;
				continue; 
			} 
			if ((code[i] == '\'') && sign_a != 0) {
				LinkStack_Pop(stack);
			} 
			
			if ((code[i] == '\"') && sign_b == 0) {
				sign_b += 1;
				i++;
				continue; 
			}
			if ((code[i] == '\"') && sign_a != 0) {
				LinkStack_Pop(stack);
			} 
			
		} // 为左符号 判断 
		
		if (IsRight(code[i])) {
			char *c = LinkStack_Pop(stack);
			
			if (code[i] == '\'') {
				sign_a = 0;
			}
			
			if (code[i] == '\"') {
				sign_b = 0;
			}
			
			// 不匹配 
			if ((c == NULL) || (!Char_Match(*c, code[i]))) {
				printf("%c does not match!\n", code[i]);
				ret = 0;
				break;
			}
		}
		
		i++; // 字符串加 1 
	} // 循环检测是否结束 
	
	// 检测完毕之后要判断栈空间是否为空 并且已经扫描完毕 
	if((LinkStack_Size(stack) == 0 ) && (code[i] == '\0')) {
		printf("success!\n");
		ret = 1; 
	} else {
		printf("Invalid code!\n");
        ret = 0;
	}
	
	LinkStack_Destroy(stack);

	return ret;
}


int main(int argc, char *argv[]) {
	
	const char* code = "#,. <> {} [] () \' \' \'\' dasd ";
	scanner(code);
	return 0;
}
