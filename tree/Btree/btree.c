#include <stdio.h>
#include <malloc.h>
#include "btree.h"

typedef struct _tag_BTree {
	int count;
	BTreeNode *root;	
} btree_t;


// 递归查看节点个数 
static int Recusive_Count(BTreeNode *node)
{
	int ret = 0;
	
	if (node != NULL) {
		ret = Recusive_Count(node->left) + 1 + Recusive_Count(node->right);
	}
	
	return ret;
}

// 递归 计算 
static int Recursive_Height (BTreeNode *root)
{
	int ret = 0; 
	if (root != NULL) {
		int lh = Recursive_Height(root->left);
		int rh = Recursive_Height(root->right);
		
		 ret = ((lh > rh) ? lh : rh) + 1;
	}
	
	return ret;
}

// 递归计算度

static int Recursive_Degree (BTreeNode *root)
{
	int ret = 0;
	if (root != NULL) {
		if(root->left != NULL) {
			ret++;
		}
		
		if(root->right != NULL) {
			ret++;
		}
		
		if(ret == 1) {
			int ld = Recursive_Degree(root->left);
			int rd = Recursive_Degree(root->right);
			
			if(ret < ld) {
				ret = ld;
			}
			
			if (ret < rd) {
				ret = rd;
			}
		}
	} 

	return ret;
} 


static void Recursive_Display (BTreeNode *node, BTree_Printf pfunc, int format, int gap, char div)
{
	int i = 0;
	
	if((node != NULL) && (pfunc != NULL)) {
		for (i =0; i < format; i++) {
			printf("%c", div);
		}
		
		pfunc(node);
		
		printf("\n");
		
		if((node->left != NULL) || (node->right != NULL)) {
			Recursive_Display(node->left, pfunc, format + gap, gap, div);
			Recursive_Display(node->right, pfunc, format + gap, gap, div);
		}
	}  else { // 如果为空 保留二叉树的位置 
        for(i=0; i<format; i++)
        {
            printf("%c", div);
        }
        printf("\n");
	}
}
/********************************************************/ 
// 创建树 
BTree *BTree_Create()
{
	btree_t *ret = (btree_t *)malloc(sizeof (btree_t));
	if (ret != NULL) {
		ret->root = NULL;
		ret->count = 0;
	}
	return ret;
}

// 摧毁树 
void BTree_Destroy(BTree *tree)
{
	free(tree);	
} 

// 清空树 
void BTree_Clear(BTree *tree)
{
	btree_t *btree = (btree_t *)tree;
	if (btree != NULL) {
		btree->count = 0;
		btree->root = NULL;
	}
}

// 插入树节点
// count 表示你要走多少路  flag 表示默认插入的是左子树还是右子树 
int BTree_Insert(BTree *tree, BTreeNode *node, BTPos pos, int count, int flag)
{
	int bit = 0;
	btree_t *btree = (btree_t *)tree;
	int ret = ((btree != NULL) && (node != NULL));
	ret = ret && ((flag == BT_LEFT) || (flag == BT_RIGHT));
	
	// 合法性判断 
	if (ret) {
		// 用于保存父节点 
		BTreeNode *parent = NULL;
		
		// 当前节点 
		BTreeNode *current = btree->root; 
		
		// 给带插入的节点赋初值 
		node->left  = NULL;
		node->right = NULL; 		
		
		// 由于用的是指路法 相当于判断路标 用的是取出最后一位 
		// 依次判断怎么走路线 
		while ((count > 0) && (current != NULL)) {
			// 最低位与 移植 
			bit  = pos & 1;
			pos = pos >> 1; 
			
			// 给父节点赋值 
			parent = current;
			
			// 指路 
			if (bit == BT_LEFT) {
				current = current->left;
			} else if (bit == BT_RIGHT) {
				current = current->right;
			}
			count--;
		}
		
		// 默认插入是左子树 还是右子树 
		if (flag == BT_LEFT) {
			node->left = current;
		} else if (flag == BT_RIGHT) {
			node->right = current;
		}
		
		// 插入的节点不为根节点 
		if(parent != NULL ) {
			
			if(bit == BT_LEFT) {
				parent->left = node;
			} else if (bit == BT_RIGHT) {
				parent->right = node;
			}
		} else {	// 若插入为根节点 
			btree->root = node; 
		}
		btree->count++; 
	}	// 合法判断 ret 
	
	return ret;
}

// 删除树节点
// 删除节点得递归 
BTreeNode *BTree_Delete(BTree *tree, BTPos pos, int count)
{
	btree_t *btree = (btree_t *)tree;
	BTreeNode *ret = NULL;
	int bit = 0;
	
	if(btree != NULL) {
		BTreeNode *parent = NULL;
		BTreeNode *current = btree->root;
		
		// 找位置 
		while ((count > 0) && (current != NULL)) {
			bit = pos & 1;
			pos = pos >> 1;
			
			parent = current;
			
			// 走步 
			if (bit == BT_LEFT) {
				current = current->left; 
			} else if (bit == BT_RIGHT) {
			 	current =  current->right; 
			}
			
			count--;
		} // while 找点 
		
		// 找到节点后让父节点对应位置置为NULL
		if (parent != NULL) {
			if(bit == BT_LEFT) {
				parent->left = NULL;
			} else if (bit == BT_RIGHT) {
				parent->right = NULL;
			}
		} else { // 如果为根节点 
			btree->root = NULL;
		}
		
		// 保存返回值 
		ret  = current; 
		
		btree->count = btree->count - Recusive_Count(ret); 
		
	}
	
	return ret;
}

// 获取树节点
BTreeNode *BTree_Get(BTree *tree, BTPos pos,int count)
{
	BTreeNode *ret = NULL;
	btree_t *btree = (btree_t *)tree;
	int bit = 0;
	
	if (btree != NULL) {
		
		BTreeNode *current = (BTreeNode *)btree->root;
		while ((count > 0) && (current != NULL)) {
			bit = pos & 1;
			pos = pos >> 1;
			
			if( bit == BT_LEFT )
            {
                current = current->left;
            }
            else if( bit == BT_RIGHT )
            {
                current = current->right;
            }
            
            count--;
		}
		ret = current;
	}
	
	return ret; 
} 

// 获取根节点信息
BTreeNode *BTree_Root(BTree *tree)
{
	btree_t *btree = (btree_t *)tree;
	BTreeNode *ret = NULL;
	
	if(btree != NULL) {
		ret = btree->root;
	}
	return ret; 
}

// 树高
int	BTree_Height(BTree *tree)
{
    btree_t* btree = (btree_t *)tree;
    int ret = 0;
    
    if( btree != NULL )
    {
        ret = Recursive_Height(btree->root);
    }
    
    return ret;
}

// 树节点数
int BTree_Count(BTree *tree)
{
	btree_t *btree = (btree_t *)tree;
	int ret = 0;
	
	if (btree != NULL) {
		ret = btree->count;
	}  
	return ret;
} 

// 树的度
int BTree_Degree(BTree *tree)
{
    btree_t *btree = (btree_t *)tree;
    int ret = 0;
    
    if( btree != NULL )
    {
        ret = Recursive_Degree(btree->root);
    }
    
    return ret;
}

void BTree_Display(BTree *tree, BTree_Printf pFunc, int gap, int div)
{
    btree_t* btree = (btree_t*)tree;
    
    if( btree != NULL )
    {
        Recursive_Display(btree->root, pFunc, 0, gap, div);
    }
}


