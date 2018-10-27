#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"
#include "string.h"
/**
 * \brief ��׺���ʽת��׺�㷨����
 * 
 * 1.������׺���ʽ�е����ֺͷ���
 * 2.�������֣�ֱ�����
 * 3.���ڷ��ţ�
 * 		��1�������ţ���ջ
 * 		��2�����������ջ�����Ž������ȼ��Ƚ�
 *			��1��ջ���������ȼ��ͣ���ջ
 *			��2��ջ���������ȼ����ͣ���ջ�����ŵ����������֮���ջ
 * 		��3�������ţ���ջ�����ŵ����������ֱ��ƥ��������
 * 4.������������ջ�е����з��ŵ��������
 */

// ����֮���ÿɿո����
static char temp_str[100] = {0}; // ��׺���ʽ�ַ����� 

// �Ƿ�Ϊ���� 
int IsNum (char c)
{
	return ((c >= '0') && (c <= '9'));		
} 

// �Ƿ�Ϊ���� 
int IsOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

// �Ƿ�Ϊ����� 
int IsLeft(char c)
{
    return (c == '(');
}

// �Ƿ�Ϊ�ҷ��� 
int IsRight(char c)
{
    return (c == ')');
}

// ���ȼ��ж� */ �����ȼ��� +- �� ������������Ϊ��� ����С���ţ������Ƚ�ջ�� 
int Priority(char c)
{
	// �����������ȼ� 
    int ret = 0;
    
    // +- �����ȼ� 
    if( (c == '+') || (c == '-') )
    {
        ret = 1;
    }
    
    // */ ���ȼ� 
    if( (c == '*') || (c == '/') )
    {
        ret = 2;
    }
    
    return ret;
}

// ��ӡ���� 
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
	int i = 0;	// �ַ���ɨ�� 
	int j = 0;	// ��׺������� 
	
	LinkStack *stack = LinkStack_Create();
	
	while (code[i] != '\0') {
		
		// ���Կո� 
		if (code[i] == ' ') {
			i++;
			continue;
		}
		
		// Ϊ����ֱ�Ӵ�ӡ 
		 if (IsNum(code[i])) {
		 	if (IsOperator(temp_str[j - 1])) {
		 		temp_str[j++] = ' ';
			 }
		 	temp_str[j] = output(code[i]);
		 	j++;
		 	
		// ������������ 
		} else if (IsOperator(code[i])) {
			 
		 	// ɨ�赽���������Ҫ��ջ�������ȼ��� �Ž���ѹջ ����͵�ջ����Ϊֹ 
		 	while (Priority(code[i]) <= Priority((char)(int)LinkStack_Top(stack))) {
		 		temp_str[j++] = ' ';
		 		temp_str[j] = output((char)(int)LinkStack_Pop(stack));
		 		j++;
		 	} 
		 	
		 	temp_str[j++] = ' '; 
		 	// ѹ����ŵ�ջ 
			LinkStack_Push(stack, (void *)(int)code[i]);
			
		// ���������� ѹջ 
		} else if(IsLeft(code[i])) {
			LinkStack_Push(stack, (void *)(int)code[i]);
			
		// �ҷ��� ��ջ ��ֱ��������ŵ���Ϊֹ�� 
		} else if (IsRight(code[i])) {
			char c = '\0';
			
			while (!IsLeft((char)(int)LinkStack_Top(stack))) {
				temp_str[j++] = ' ';
				temp_str[j] = output((char)(int)LinkStack_Pop(stack));
				j++; 
			}
			
			// ������ŵ��� 
			LinkStack_Pop(stack);
			
		// �Ƿ��ַ� �����Ƴ� 
		} else {
			printf("Invalid expression!\n");
            break;
		}
		i++; 
	} // �ַ�ɨ�����
	
	// ���ջ�ռ�ȫ����������ӡ
	while ((LinkStack_Size(stack) > 0) && (code[i] == '\0')) {
		temp_str[j++] = ' ';
		temp_str[j] = output((char)((int)LinkStack_Pop(stack)));
		j++;
	}
	printf("\n");
	LinkStack_Destroy(stack);	
}

/**
 * \brief ������׺���ʽ�е����ֺͷ���
 * 1.�������֣���ջ
 * 2.���ڷ��ţ�
 * 	(1)��ջ�е����Ҳ�����
 * 	(2)��ջ�е����������
 * 	(3)���ݷ��Ž�������
 * 	(4)��������ѹ��ջ��
 * 3.����������ջ�е�Ψһ����Ϊ������
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

// ��׺���� 
int operation (char *code)
{
	int ret = 0;
	int i = 0;	// �ַ���ɨ�� 
	int temp_data = 0;
	int result;
	
	LinkStack *stack = LinkStack_Create();
	
	while (code[i] != '\0') {
		
		// ��������  �������� ' ' ��Ϊ�ָ��� 
		if ((IsNum(code[i])) || (code[i] == ' ')) {

			// �����Ϊ�ո��ʾһ�ε�����ɨ����� 
			if (code[i] == ' ') {
				
				// ����Ƿ��ź���Ŀո� ���� 
				if (IsOperator(code[i - 1])) {
					i++;
					continue;
				}
				// �����⵽���Ƿ���ǰ�Ŀո� 
				// ������һ��bug ���ǣ�void *��0 ����NULL,��������0 ����bug 
				LinkStack_Push(stack, (void*)&temp_data);
				temp_data = 0;
				//flag = 0;
				i++;
				continue;
			}
			
			temp_data = temp_data * 10 + Value(code[i]);
			
		// �ֱ𵯳��� ������� ���㲢�����ѹ��ջ 
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


