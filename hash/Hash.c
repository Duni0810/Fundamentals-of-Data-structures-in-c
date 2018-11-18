#include <stdio.h>
#include <malloc.h>
#include "Hash.h"
#include "BSTree.h"

typedef struct _tag_HashNode HashNode;

// hash 内部管理结构体 
struct _tag_HashNode
{
    BSTreeNode header;		// 链信息 
    HashValue* value;		// 值保留 
};

// 递归清空hash 表防止内存泄露 
void recursive_clear(BSTreeNode* node)
{
    if( node != NULL ) {
        recursive_clear(node->left);
        recursive_clear(node->right);
        // 释放空间 
        free(node);
    }
}

// 创建hash表 
Hash* Hash_Create()
{
    return BSTree_Create();
}

// 摧毁hash表 
void Hash_Destroy(Hash* hash)
{
    Hash_Clear(hash);
    BSTree_Destroy(hash);
}

// 清空hash 表 
void Hash_Clear(Hash* hash)
{
    recursive_clear(BSTree_Root(hash));
    BSTree_Clear(hash);
}

// 加入键值对
int Hash_Add(Hash* hash, HashKey* key, HashValue* value, Hash_Compare* compare)
{
    int ret = 0;
    // 申请 数据存储空间 
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    
    if( ret = (node != NULL) ) {
    	// 节点初始化赋值 
        node->header.key = key;
        node->value = value;
        
        // 调用二叉排序树中的插入操作 
        ret = BSTree_Insert(hash, (BSTreeNode*)node, compare);
        
        // 如果插入失败，释放空间 
        if( !ret ) {
            free(node);
        }
    }
    
    return ret;
}

// hash 表删除操作 
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

// 通过键值获取hash值 
HashValue* Hash_Get(Hash* hash, HashKey* key, Hash_Compare* compare)
{
    HashValue* ret = NULL;
    HashNode* node = (HashNode*)BSTree_Get(hash, key, compare);
    
    if( node != NULL ) {
        ret = node->value;
    }
    
    return ret;
}

// hash表数据获取 
int Hash_Count(Hash* hash)
{
    return BSTree_Count(hash);
}
