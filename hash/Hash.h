#ifndef _HASH_H_
#define _HASH_H_

typedef void Hash;
typedef void HashKey;
typedef void HashValue;

// �ȽϺ������Ͷ��� 
typedef int (Hash_Compare)(HashKey*, HashKey*);

// ����hash 
Hash* Hash_Create();

// �ݻ�hash 
void Hash_Destroy(Hash* hash);

// ���hash 
void Hash_Clear(Hash* hash);

// ���hash 
int Hash_Add(Hash* hash, HashKey* key, HashValue* value, Hash_Compare* compare);

// �Ƴ�hash 
HashValue* Hash_Remove (Hash* hash, HashKey* key, Hash_Compare* compare);

// ��ȡhash 
HashValue* Hash_Get(Hash* hash, HashKey* key, Hash_Compare* compare);

// hash�������� 
int Hash_Count(Hash* hash);


#endif
