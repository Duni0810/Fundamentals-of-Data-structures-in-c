#include <stdio.h>
#include <malloc.h>
#include "Hash.h"
#include "BSTree.h"

typedef struct _tag_HashNode HashNode;

// hash �ڲ�����ṹ�� 
struct _tag_HashNode
{
    BSTreeNode header;		// ����Ϣ 
    HashValue* value;		// ֵ���� 
};

// �ݹ����hash ���ֹ�ڴ�й¶ 
void recursive_clear(BSTreeNode* node)
{
    if( node != NULL ) {
        recursive_clear(node->left);
        recursive_clear(node->right);
        // �ͷſռ� 
        free(node);
    }
}

// ����hash�� 
Hash* Hash_Create()
{
    return BSTree_Create();
}

// �ݻ�hash�� 
void Hash_Destroy(Hash* hash)
{
    Hash_Clear(hash);
    BSTree_Destroy(hash);
}

// ���hash �� 
void Hash_Clear(Hash* hash)
{
    recursive_clear(BSTree_Root(hash));
    BSTree_Clear(hash);
}

// �����ֵ��
int Hash_Add(Hash* hash, HashKey* key, HashValue* value, Hash_Compare* compare)
{
    int ret = 0;
    // ���� ���ݴ洢�ռ� 
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    
    if( ret = (node != NULL) ) {
    	// �ڵ��ʼ����ֵ 
        node->header.key = key;
        node->value = value;
        
        // ���ö����������еĲ������ 
        ret = BSTree_Insert(hash, (BSTreeNode*)node, compare);
        
        // �������ʧ�ܣ��ͷſռ� 
        if( !ret ) {
            free(node);
        }
    }
    
    return ret;
}

// hash ��ɾ������ 
HashValue* Hash_Remove(Hash* hash, HashKey* key, Hash_Compare* compare)
{
    HashValue* ret = NULL;
    HashNode* node = (HashNode*)BSTree_Delete(hash, key, compare);
    
    if( node != NULL ) {
        ret = node->value;
        
        free(node);
    }
    
    return ret;
}

// ͨ����ֵ��ȡhashֵ 
HashValue* Hash_Get(Hash* hash, HashKey* key, Hash_Compare* compare)
{
    HashValue* ret = NULL;
    HashNode* node = (HashNode*)BSTree_Get(hash, key, compare);
    
    if( node != NULL ) {
        ret = node->value;
    }
    
    return ret;
}

// hash�����ݻ�ȡ 
int Hash_Count(Hash* hash)
{
    return BSTree_Count(hash);
}
