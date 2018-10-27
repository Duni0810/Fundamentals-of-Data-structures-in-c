#include <stdio.h>
#include <malloc.h>
#include "btree.h"

typedef struct _tag_BTree {
	int count;
	BTreeNode *root;	
} btree_t;


// �ݹ�鿴�ڵ���� 
static int Recusive_Count(BTreeNode *node)
{
	int ret = 0;
	
	if (node != NULL) {
		ret = Recusive_Count(node->left) + 1 + Recusive_Count(node->right);
	}
	
	return ret;
}

// �ݹ� ���� 
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

// �ݹ�����

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
	}  else { // ���Ϊ�� ������������λ�� 
        for(i=0; i<format; i++)
        {
            printf("%c", div);
        }
        printf("\n");
	}
}
/********************************************************/ 
// ������ 
BTree *BTree_Create()
{
	btree_t *ret = (btree_t *)malloc(sizeof (btree_t));
	if (ret != NULL) {
		ret->root = NULL;
		ret->count = 0;
	}
	return ret;
}

// �ݻ��� 
void BTree_Destroy(BTree *tree)
{
	free(tree);	
} 

// ����� 
void BTree_Clear(BTree *tree)
{
	btree_t *btree = (btree_t *)tree;
	if (btree != NULL) {
		btree->count = 0;
		btree->root = NULL;
	}
}

// �������ڵ�
// count ��ʾ��Ҫ�߶���·  flag ��ʾĬ�ϲ���������������������� 
int BTree_Insert(BTree *tree, BTreeNode *node, BTPos pos, int count, int flag)
{
	int bit = 0;
	btree_t *btree = (btree_t *)tree;
	int ret = ((btree != NULL) && (node != NULL));
	ret = ret && ((flag == BT_LEFT) || (flag == BT_RIGHT));
	
	// �Ϸ����ж� 
	if (ret) {
		// ���ڱ��游�ڵ� 
		BTreeNode *parent = NULL;
		
		// ��ǰ�ڵ� 
		BTreeNode *current = btree->root; 
		
		// ��������Ľڵ㸳��ֵ 
		node->left  = NULL;
		node->right = NULL; 		
		
		// �����õ���ָ·�� �൱���ж�·�� �õ���ȡ�����һλ 
		// �����ж���ô��·�� 
		while ((count > 0) && (current != NULL)) {
			// ���λ�� ��ֲ 
			bit  = pos & 1;
			pos = pos >> 1; 
			
			// �����ڵ㸳ֵ 
			parent = current;
			
			// ָ· 
			if (bit == BT_LEFT) {
				current = current->left;
			} else if (bit == BT_RIGHT) {
				current = current->right;
			}
			count--;
		}
		
		// Ĭ�ϲ����������� ���������� 
		if (flag == BT_LEFT) {
			node->left = current;
		} else if (flag == BT_RIGHT) {
			node->right = current;
		}
		
		// ����Ľڵ㲻Ϊ���ڵ� 
		if(parent != NULL ) {
			
			if(bit == BT_LEFT) {
				parent->left = node;
			} else if (bit == BT_RIGHT) {
				parent->right = node;
			}
		} else {	// ������Ϊ���ڵ� 
			btree->root = node; 
		}
		btree->count++; 
	}	// �Ϸ��ж� ret 
	
	return ret;
}

// ɾ�����ڵ�
// ɾ���ڵ�õݹ� 
BTreeNode *BTree_Delete(BTree *tree, BTPos pos, int count)
{
	btree_t *btree = (btree_t *)tree;
	BTreeNode *ret = NULL;
	int bit = 0;
	
	if(btree != NULL) {
		BTreeNode *parent = NULL;
		BTreeNode *current = btree->root;
		
		// ��λ�� 
		while ((count > 0) && (current != NULL)) {
			bit = pos & 1;
			pos = pos >> 1;
			
			parent = current;
			
			// �߲� 
			if (bit == BT_LEFT) {
				current = current->left; 
			} else if (bit == BT_RIGHT) {
			 	current =  current->right; 
			}
			
			count--;
		} // while �ҵ� 
		
		// �ҵ��ڵ���ø��ڵ��Ӧλ����ΪNULL
		if (parent != NULL) {
			if(bit == BT_LEFT) {
				parent->left = NULL;
			} else if (bit == BT_RIGHT) {
				parent->right = NULL;
			}
		} else { // ���Ϊ���ڵ� 
			btree->root = NULL;
		}
		
		// ���淵��ֵ 
		ret  = current; 
		
		btree->count = btree->count - Recusive_Count(ret); 
		
	}
	
	return ret;
}

// ��ȡ���ڵ�
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

// ��ȡ���ڵ���Ϣ
BTreeNode *BTree_Root(BTree *tree)
{
	btree_t *btree = (btree_t *)tree;
	BTreeNode *ret = NULL;
	
	if(btree != NULL) {
		ret = btree->root;
	}
	return ret; 
}

// ����
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

// ���ڵ���
int BTree_Count(BTree *tree)
{
	btree_t *btree = (btree_t *)tree;
	int ret = 0;
	
	if (btree != NULL) {
		ret = btree->count;
	}  
	return ret;
} 

// ���Ķ�
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


