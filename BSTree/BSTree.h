#ifndef _BSTREE_H_
#define _BSTREE_H_

typedef void BSTree;
typedef void BSKey;

typedef struct _tag_BSTreeNode BSTreeNode;

struct _tag_BSTreeNode
{
    BSKey* key;			// ���ҹؼ��� 
    BSTreeNode* left;	// ������ 
    BSTreeNode* right;	// ������ 
};

typedef void (BSTree_Printf)(BSTreeNode*);		// ��ӡ���� 
typedef int (BSTree_Compare)(BSKey*, BSKey*);	// �ȽϺ��� 

// 1.���������� 
BSTree* BSTree_Create();

// 2. �ݻٶ����� 
void BSTree_Destroy(BSTree* tree);

// 3. ��ն����� 
void BSTree_Clear(BSTree* tree);

// 4. �������� 
int BSTree_Insert(BSTree* tree, BSTreeNode* node, BSTree_Compare* compare);

// 5. ɾ������ 
BSTreeNode* BSTree_Delete(BSTree* tree, BSKey* key, BSTree_Compare* compare);

// 6. ��ȡ���� 
BSTreeNode* BSTree_Get(BSTree* tree, BSKey* key, BSTree_Compare* compare);

// 7. ���ڵ� 
BSTreeNode* BSTree_Root(BSTree* tree);

// 8. ���� 
int BSTree_Height(BSTree* tree);

// 9.���ڵ� 
int BSTree_Count(BSTree* tree);

// 10. ���Ķ� 
int BSTree_Degree(BSTree* tree);

// 11. ��ӡ�� 
void BSTree_Display(BSTree* tree, BSTree_Printf* pFunc, int gap, char div);

#endif

