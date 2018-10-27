#ifndef __BTREE__H__
#define __BTREE__H__

#define 	BT_LEFT		0 // 左路 
#define 	BT_RIGHT	1 // 右路 

typedef void BTree;
 
typedef unsigned long long BTPos;


// 树节点结构体 
typedef struct _tag_BTreeNode {
	struct _tag_BTreeNode *left;		// 左子树 
	struct _tag_BTreeNode *right;		// 右子树 
} BTreeNode;

// 打印函数类型定义 
typedef void (*BTree_Printf)(BTreeNode *);

// 创建树 
BTree *BTree_Create();

// 摧毁树 
void BTree_Destroy(BTree *tree); 

// 清空树 
void BTree_Clear(BTree *tree);

// 插入树节点
int BTree_Insert(BTree *tree, BTreeNode *node, BTPos pos, int count, int flag);

// 删除树节点
BTreeNode *BTree_Delete(BTree *tree, BTPos pos, int count);

// 获取树节点
BTreeNode *BTree_Get(BTree *tree, BTPos pos,int count);

// 获取根节点信息
BTreeNode *BTree_Root(BTree *tree);

// 树高
int	BTree_Height(BTree *tree); 

// 树节点数
int BTree_Count(BTree *tree);

// 树的度
int BTree_Degree(BTree *tree);

void BTree_Display(BTree *tree, BTree_Printf pFunc, int gap, int div); 



#endif

