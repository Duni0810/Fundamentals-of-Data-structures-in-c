#ifndef _HASH_H_
#define _HASH_H_

typedef void Hash;
typedef void HashKey;
typedef void HashValue;

// 比较函数类型定义 
typedef int (Hash_Compare)(HashKey*, HashKey*);

// 创建hash 
Hash* Hash_Create();

// 摧毁hash 
void Hash_Destroy(Hash* hash);

// 清空hash 
void Hash_Clear(Hash* hash);

// 添加hash 
int Hash_Add(Hash* hash, HashKey* key, HashValue* value, Hash_Compare* compare);

// 移除hash 
HashValue* Hash_Remove (Hash* hash, HashKey* key, Hash_Compare* compare);

// 获取hash 
HashValue* Hash_Get(Hash* hash, HashKey* key, Hash_Compare* compare);

// hash表数据量 
int Hash_Count(Hash* hash);


#endif
