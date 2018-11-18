#include <stdio.h>
#include <malloc.h>
#include "BSTree.h"

typedef struct _tag_BSTree TBSTree;

// 二叉排序树内部管理结构体 
struct _tag_BSTree
{
    int count;			// 节点计数 
    BSTreeNode* root;	// 根节点信息 
};

// 打印树 
static void recursive_display(BSTreeNode* node, BSTree_Printf* pFunc, int format, int gap, char div) // O(n)
{
    int i = 0;
    
    if((node != NULL) && (pFunc != NULL)) {
        for(i=0; i<format; i++) {
            printf("%c", div);
        }
        
        pFunc(node);
        
        printf("\n");
        
        if( (node->left != NULL) || (node->right != NULL) ) {
            recursive_display(node->left, pFunc, format + gap, gap, div);
            recursive_display(node->right, pFunc, format + gap, gap, div);
        }
    } else {
        for(i=0; i<format; i++) {
            printf("%c", div);
        }
        printf("\n");
    }
}

// 递归计算数节点 
static int recursive_count(BSTreeNode* root) // O(n)
{
    int ret = 0;
    
    if( root != NULL ) {
        ret = recursive_count(root->left) + 1 + recursive_count(root->right);
    }
    
    return ret;
}

// 递归计算树的高度 
static int recursive_height(BSTreeNode* root) // O(n)
{
    int ret = 0;
    
    if( root != NULL ) {
        int lh = recursive_height(root->left);
        int rh = recursive_height(root->right);
        
        // 比较左子树和右子树的高度 
        ret = ((lh > rh) ? lh : rh) + 1;
    }
    
    return ret;
}

// 树的度 
static int recursive_degree(BSTreeNode* root) // O(n)
{
    int ret = 0;
    
    // 根节点不为空 
    if( root != NULL ) {
    	
    	// 左节点不为空 
        if( root->left != NULL ) {
            ret++;
        }
        
        // 右节点不为空 
        if( root->right != NULL ) {
            ret++;
        }
        
        // 如果左节点或右节点其中一个为空，递归 
        if( ret == 1 ) {
            int ld = recursive_degree(root->left);
            int rd = recursive_degree(root->right);
            
            if( ret < ld ) {
                ret = ld;
            }
            
            if( ret < rd ) {
                ret = rd;
            }
        }
    }
    
    return ret;
}

/**
 *  \brief 二叉排序树的插入操作
 *
 * param[in] root    节点信息
 * param[in] node    插入的节点
 * param[in] compare 比较函数
 *
 * \note 比较函数是用户传入的，我们不知数据类型，所以由用户自行处理 
 */  
static int recursive_insert(BSTreeNode* root, BSTreeNode* node, BSTree_Compare* compare)
{
    int ret = 1;
    int r = compare(node->key, root->key);
    
    // 如果ｒ = 0  表示在二叉树中已经存在该节点, 插入失败 
    if( r == 0 ) {
        ret = 0;
        
    } else if( r < 0 ) { // 选择左子树中递归 
		// 如果左子树不为空 ,递归 
        if( root->left != NULL ) {
            ret = recursive_insert(root->left, node, compare);
        } else {	// 左子树为空，表示就插入在这个位置了。 
            root->left = node;
        }
        
    } else if( r > 0 ) { // 右子树递归 
    	// 如果右子树不为空 ,递归 
        if( root->right != NULL ) {
            ret = recursive_insert(root->right, node, compare);
        } else { // 右子树为空，表示就插入在这个位置了。
            root->right = node;
        }
    }
}

/**
 * \brief 递归查找
 *
 * param[in] root    查找节点
 * patam[in] key     查找的关键字
 * param[in] compare 比较函数 
 */ 
static BSTreeNode* recursive_get(BSTreeNode* root, BSKey* key, BSTree_Compare* compare)
{
    BSTreeNode* ret = NULL;
    
    if( root != NULL ) {
        int r = compare(key, root->key);
        
        // 如果 r = 0 表示找到 
        if( r == 0 ) {
            ret = root;
        
        // 左节点 递归查找 
        } else if( r < 0 ) {
            ret = recursive_get(root->left, key, compare);
        // 右节点 递归查找 
        } else if( r > 0 ) {
            ret = recursive_get(root->right, key, compare);
        }
    }
    return ret;
}

/**
 * \brief 删除节点 
 *
 * \note 传入二级指主要是因为我们在删除操作需要需改指针数据 
 */ 
static BSTreeNode* delete_node(BSTreeNode** pRoot)
{
    BSTreeNode* ret = *pRoot;
    
    // 右节点为空时候，左节点直接上位 
    if( (*pRoot)->right == NULL ) {
        *pRoot = (*pRoot)->left;
    
    // 左节点为空时，右节点直接上位 
    } else if( (*pRoot)->left == NULL ) {
        *pRoot = (*pRoot)->right;
    
    // 如果做左右节点都不为空需要找中序遍历的直接前驱 
    } else {
        BSTreeNode* g = *pRoot;
        BSTreeNode* c = (*pRoot)->left;
        
        // 右子树为空的节点  
        while( c->right != NULL ) {
            g = c;
            c = c->right;
        }
        
        //判断while是否有执行
		//如果没有执行表示下一个节点直接满足条件 
        if( g != *pRoot ) {
            g->right = c->left;
        } else {
            g->left = c->left;
        }

		// 上位操作 
        c->left = (*pRoot)->left;
        c->right = (*pRoot)->right;
        
        *pRoot = c;
    }
    
    return ret;
}

/**
 * \brief 递归删除 
 *
 * param[in] pRoot     删除节点起始位置
 * param[in] key       关键字
 * param[in] compare   比较函数 
 *
 * retval 返回待删除的元素 
 */ 
static BSTreeNode* recursive_delete(BSTreeNode** pRoot, BSKey* key, BSTree_Compare* compare)
{
    BSTreeNode* ret = NULL;
    
    if( (pRoot != NULL) && (*pRoot != NULL) ) {
        int r = compare(key, (*pRoot)->key);
        
        // 找到元素 
        if( r == 0 ) {
            ret = delete_node(pRoot);
        // 左子树递归查找 
        } else if( r < 0 ) {
            ret = recursive_delete(&((*pRoot)->left), key, compare);
        // 右子树递归查找 
        } else if( r > 0 ) {
            ret = recursive_delete(&((*pRoot)->right), key, compare);
        }
    }
    
    return ret;
}

// 创建二叉树 
BSTree* BSTree_Create() // O(1)
{
    TBSTree* ret = (TBSTree*)malloc(sizeof(TBSTree));
    
    if( ret != NULL ) {
        ret->count = 0;
        ret->root = NULL;
    }
    
    return ret;
}

// 摧毁二叉树 
void BSTree_Destroy(BSTree* tree) // O(1)
{
    free(tree);
}

// 清空二叉树 
void BSTree_Clear(BSTree* tree) // O(1)
{
    TBSTree* btree = (TBSTree*)tree;
    
    if(btree != NULL) {
        btree->count = 0;
        btree->root = NULL;
    }
}

// 插入二叉树 
int BSTree_Insert(BSTree* tree, BSTreeNode* node, BSTree_Compare* compare) 
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = (btree != NULL) && (node != NULL) && (compare != NULL);
    
    if(ret) {
    	// 插入节点赋值 
        node->left = NULL;
        node->right = NULL;
        
        // 根节点 
        if(btree->root == NULL) {
            btree->root = node;
        } else {
            ret = recursive_insert(btree->root, node, compare);
        }
        
        // 插入成功 count++ 
        if(ret) {
            btree->count++;
        }
    }
    
    return ret;
}

//brief 二叉树的删除 
BSTreeNode* BSTree_Delete(BSTree* tree, BSKey* key, BSTree_Compare* compare)
{
    TBSTree* btree = (TBSTree*)tree;
    BSTreeNode* ret = NULL; 
    
    if((btree != NULL) && (key != NULL) && (compare != NULL)) {
        ret = recursive_delete(&btree->root, key, compare);
        
        // 如果删除成功 count-- 
        if( ret != NULL )
        {
            btree->count--;
        }
    }
    
    return ret;
}

// 节点获取 
BSTreeNode* BSTree_Get(BSTree* tree, BSKey* key, BSTree_Compare* compare)
{
    TBSTree* btree = (TBSTree*)tree;
    BSTreeNode* ret = NULL; 
    
    if((btree != NULL) && (key != NULL) && (compare != NULL)) {
        ret = recursive_get(btree->root, key, compare);
    }
    
    return ret;
}

// 根节点 
BSTreeNode* BSTree_Root(BSTree* tree) // O(1)
{
    TBSTree* btree = (TBSTree*)tree;
    BSTreeNode* ret = NULL;
    
    if( btree != NULL ) {
        ret = btree->root;
    }
    
    return ret;
}

// 树高 
int BSTree_Height(BSTree* tree) // O(n)
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = 0;
    
    if(btree != NULL) {
        ret = recursive_height(btree->root);
    }
    
    return ret;
}

// 树节点数 
int BSTree_Count(BSTree* tree) // O(1)
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = 0;
    
    if(btree != NULL) {
        ret = btree->count;
    }
    
    return ret;
}

// 二叉树的度 
int BSTree_Degree(BSTree* tree) // O(n)
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = 0;
    
    if(btree != NULL) {
        ret = recursive_degree(btree->root);
    }
    
    return ret;
}

// 二叉树打印 
void BSTree_Display(BSTree* tree, BSTree_Printf* pFunc, int gap, char div) // O(n)
{
    TBSTree* btree = (TBSTree*)tree;
    
    if( btree != NULL )
    {
        recursive_display(btree->root, pFunc, 0, gap, div);
    }
}
