#ifndef __BTREE__H__
#define __BTREE__H__

#define 	BT_LEFT		0 // ��· 
#define 	BT_RIGHT	1 // ��· 

typedef void BTree;
 
typedef unsigned long long BTPos;


// ���ڵ�ṹ�� 
typedef struct _tag_BTreeNode {
	struct _tag_BTreeNode *left;		// ������ 
	struct _tag_BTreeNode *right;		// ������ 
} BTreeNode;

// ��ӡ�������Ͷ��� 
typedef void (*BTree_Printf)(BTreeNode *);

// ������ 
BTree *BTree_Create();

// �ݻ��� 
void BTree_Destroy(BTree *tree); 

// ����� 
void BTree_Clear(BTree *tree);

// �������ڵ�
int BTree_Insert(BTree *tree, BTreeNode *node, BTPos pos, int count, int flag);

// ɾ�����ڵ�
BTreeNode *BTree_Delete(BTree *tree, BTPos pos, int count);

// ��ȡ���ڵ�
BTreeNode *BTree_Get(BTree *tree, BTPos pos,int count);

// ��ȡ���ڵ���Ϣ
BTreeNode *BTree_Root(BTree *tree);

// ����
int	BTree_Height(BTree *tree); 

// ���ڵ���
int BTree_Count(BTree *tree);

// ���Ķ�
int BTree_Degree(BTree *tree);

void BTree_Display(BTree *tree, BTree_Printf pFunc, int gap, int div); 



#endif

