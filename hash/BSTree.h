#ifndef _BSTREE_H_
#define _BSTREE_H_

typedef void BSTree;
typedef void BSKey;

typedef struct _tag_BSTreeNode BSTreeNode;

struct _tag_BSTreeNode
{
    BSKey* key;			// 查找关键字 
    BSTreeNode* left;	// 左子树 
    BSTreeNode* right;	// 右子树 
};

typedef void (BSTree_Printf)(BSTreeNode*);		// 打印函数 
typedef int (BSTree_Compare)(BSKey*, BSKey*);	// 比较函数 

// 1.创建二叉树 
BSTree* BSTree_Create();

// 2. 摧毁二叉树 
void BSTree_Destroy(BSTree* tree);

// 3. 清空二叉树 
void BSTree_Clear(BSTree* tree);

// 4. 插入数据 
int BSTree_Insert(BSTree* tree, BSTreeNode* node, BSTree_Compare* compare);

// 5. 删除数据 
BSTreeNode* BSTree_Delete(BSTree* tree, BSKey* key, BSTree_Compare* compare);

// 6. 获取数据 
BSTreeNode* BSTree_Get(BSTree* tree, BSKey* key, BSTree_Compare* compare);

// 7. 根节点 
BSTreeNode* BSTree_Root(BSTree* tree);

// 8. 树高 
int BSTree_Height(BSTree* tree);

// 9.数节点 
int BSTree_Count(BSTree* tree);

// 10. 树的度 
int BSTree_Degree(BSTree* tree);

// 11. 打印树 
void BSTree_Display(BSTree* tree, BSTree_Printf* pFunc, int gap, char div);

#endif

