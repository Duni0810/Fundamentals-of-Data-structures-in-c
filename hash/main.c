#include <stdio.h>
#include <stdlib.h>
#include "Hash.h"

// 元素 
struct Student
{
    char* id;
    char* name;
    int age;
};

// 比较函数 这里用字符串比较 
int compare_id(HashKey* k1, HashKey* k2)
{
    return strcmp((char*)k1, (char*)k2);
}

int main(int argc, char *argv[]) 
{
    Hash* hash = Hash_Create();
    
    // 初始化数据 
    struct Student s1 = {"9001201", "Delphi", 30};
    struct Student s2 = {"0xABCDE", "Java", 20};
    struct Student s3 = {"koabc", "C++", 40};
    struct Student s4 = {"!@#$%^", "C#", 10};
    struct Student s5 = {"Python", "Python", 10};
    struct Student* ps = NULL;
    
	// 将数据插入hash 表 
    Hash_Add(hash, s1.id, &s1, compare_id);
    Hash_Add(hash, s2.id, &s2, compare_id);
    Hash_Add(hash, s3.id, &s3, compare_id);
    Hash_Add(hash, s4.id, &s4, compare_id);
    Hash_Add(hash, s5.id, &s5, compare_id);
    
    // 通过键值获取数据 
    ps = Hash_Get(hash, "koabc", compare_id);
    
    // 打印信息 
    printf("ID: %s\n", ps->id);
    printf("Name: %s\n", ps->name);
    printf("Age: %d\n", ps->age);
    
    // 释放空间 
    Hash_Destroy(hash);
    
	return 0;
}
