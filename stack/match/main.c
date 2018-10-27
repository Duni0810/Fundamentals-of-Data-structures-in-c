#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"

/**
 * \brief ����ƥ���㷨˼·
 *
 * 1. �ӵ�һ���ַ���ʼɨ�� 
 * 2. ��������ͨ�ַ�ʱ���ԣ������������ʱѹ��ջ 
 * 3. �������ҷ���ʱ��ջ�е���ջ������ 
 * 4. ����ƥ�� 
 *		��1�� ƥ��ɹ�������������һ���ַ� 
 * 		��2�� ƥ��ʧ�ܣ�����ֹͣ��������
 * 5. ������
 *		��1�� �ɹ��������ַ�ɨ����ϣ���ջΪ��
 *		��2�� ƥ��ʧ�ܻ��������ַ���ɨ�����֮��ջ��Ϊ�� 
 */ 

// ����� 
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

// �ҷ��� 
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
	
	int sign_a = 0;  // ������ 
	int sign_b = 0;  // ˫���� 
	
	// ѭ���ַ������ı���Ϣ�� 
	while (code[i] != '\0') {
		if (IsLeft(code[i])) {
			LinkStack_Push(stack, (void *)(code + i)); 
			
			// ������Ϊ 0 ��ʾ��һ�� 
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
			
		} // Ϊ����� �ж� 
		
		if (IsRight(code[i])) {
			char *c = LinkStack_Pop(stack);
			
			if (code[i] == '\'') {
				sign_a = 0;
			}
			
			if (code[i] == '\"') {
				sign_b = 0;
			}
			
			// ��ƥ�� 
			if ((c == NULL) || (!Char_Match(*c, code[i]))) {
				printf("%c does not match!\n", code[i]);
				ret = 0;
				break;
			}
		}
		
		i++; // �ַ����� 1 
	} // ѭ������Ƿ���� 
	
	// ������֮��Ҫ�ж�ջ�ռ��Ƿ�Ϊ�� �����Ѿ�ɨ����� 
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
