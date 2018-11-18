#include <stdio.h>
#include <malloc.h>
#include "BSTree.h"

typedef struct _tag_BSTree TBSTree;

// �����������ڲ�����ṹ�� 
struct _tag_BSTree
{
    int count;			// �ڵ���� 
    BSTreeNode* root;	// ���ڵ���Ϣ 
};

// ��ӡ�� 
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

// �ݹ�������ڵ� 
static int recursive_count(BSTreeNode* root) // O(n)
{
    int ret = 0;
    
    if( root != NULL ) {
        ret = recursive_count(root->left) + 1 + recursive_count(root->right);
    }
    
    return ret;
}

// �ݹ�������ĸ߶� 
static int recursive_height(BSTreeNode* root) // O(n)
{
    int ret = 0;
    
    if( root != NULL ) {
        int lh = recursive_height(root->left);
        int rh = recursive_height(root->right);
        
        // �Ƚ����������������ĸ߶� 
        ret = ((lh > rh) ? lh : rh) + 1;
    }
    
    return ret;
}

// ���Ķ� 
static int recursive_degree(BSTreeNode* root) // O(n)
{
    int ret = 0;
    
    // ���ڵ㲻Ϊ�� 
    if( root != NULL ) {
    	
    	// ��ڵ㲻Ϊ�� 
        if( root->left != NULL ) {
            ret++;
        }
        
        // �ҽڵ㲻Ϊ�� 
        if( root->right != NULL ) {
            ret++;
        }
        
        // �����ڵ���ҽڵ�����һ��Ϊ�գ��ݹ� 
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
 *  \brief �����������Ĳ������
 *
 * param[in] root    �ڵ���Ϣ
 * param[in] node    ����Ľڵ�
 * param[in] compare �ȽϺ���
 *
 * \note �ȽϺ������û�����ģ����ǲ�֪�������ͣ��������û����д��� 
 */  
static int recursive_insert(BSTreeNode* root, BSTreeNode* node, BSTree_Compare* compare)
{
    int ret = 1;
    int r = compare(node->key, root->key);
    
    // ����� = 0  ��ʾ�ڶ��������Ѿ����ڸýڵ�, ����ʧ�� 
    if( r == 0 ) {
        ret = 0;
        
    } else if( r < 0 ) { // ѡ���������еݹ� 
		// �����������Ϊ�� ,�ݹ� 
        if( root->left != NULL ) {
            ret = recursive_insert(root->left, node, compare);
        } else {	// ������Ϊ�գ���ʾ�Ͳ��������λ���ˡ� 
            root->left = node;
        }
        
    } else if( r > 0 ) { // �������ݹ� 
    	// �����������Ϊ�� ,�ݹ� 
        if( root->right != NULL ) {
            ret = recursive_insert(root->right, node, compare);
        } else { // ������Ϊ�գ���ʾ�Ͳ��������λ���ˡ�
            root->right = node;
        }
    }
}

/**
 * \brief �ݹ����
 *
 * param[in] root    ���ҽڵ�
 * patam[in] key     ���ҵĹؼ���
 * param[in] compare �ȽϺ��� 
 */ 
static BSTreeNode* recursive_get(BSTreeNode* root, BSKey* key, BSTree_Compare* compare)
{
    BSTreeNode* ret = NULL;
    
    if( root != NULL ) {
        int r = compare(key, root->key);
        
        // ��� r = 0 ��ʾ�ҵ� 
        if( r == 0 ) {
            ret = root;
        
        // ��ڵ� �ݹ���� 
        } else if( r < 0 ) {
            ret = recursive_get(root->left, key, compare);
        // �ҽڵ� �ݹ���� 
        } else if( r > 0 ) {
            ret = recursive_get(root->right, key, compare);
        }
    }
    return ret;
}

/**
 * \brief ɾ���ڵ� 
 *
 * \note �������ָ��Ҫ����Ϊ������ɾ��������Ҫ���ָ������ 
 */ 
static BSTreeNode* delete_node(BSTreeNode** pRoot)
{
    BSTreeNode* ret = *pRoot;
    
    // �ҽڵ�Ϊ��ʱ����ڵ�ֱ����λ 
    if( (*pRoot)->right == NULL ) {
        *pRoot = (*pRoot)->left;
    
    // ��ڵ�Ϊ��ʱ���ҽڵ�ֱ����λ 
    } else if( (*pRoot)->left == NULL ) {
        *pRoot = (*pRoot)->right;
    
    // ��������ҽڵ㶼��Ϊ����Ҫ�����������ֱ��ǰ�� 
    } else {
        BSTreeNode* g = *pRoot;
        BSTreeNode* c = (*pRoot)->left;
        
        // ������Ϊ�յĽڵ�  
        while( c->right != NULL ) {
            g = c;
            c = c->right;
        }
        
        //�ж�while�Ƿ���ִ��
		//���û��ִ�б�ʾ��һ���ڵ�ֱ���������� 
        if( g != *pRoot ) {
            g->right = c->left;
        } else {
            g->left = c->left;
        }

		// ��λ���� 
        c->left = (*pRoot)->left;
        c->right = (*pRoot)->right;
        
        *pRoot = c;
    }
    
    return ret;
}

/**
 * \brief �ݹ�ɾ�� 
 *
 * param[in] pRoot     ɾ���ڵ���ʼλ��
 * param[in] key       �ؼ���
 * param[in] compare   �ȽϺ��� 
 *
 * retval ���ش�ɾ����Ԫ�� 
 */ 
static BSTreeNode* recursive_delete(BSTreeNode** pRoot, BSKey* key, BSTree_Compare* compare)
{
    BSTreeNode* ret = NULL;
    
    if( (pRoot != NULL) && (*pRoot != NULL) ) {
        int r = compare(key, (*pRoot)->key);
        
        // �ҵ�Ԫ�� 
        if( r == 0 ) {
            ret = delete_node(pRoot);
        // �������ݹ���� 
        } else if( r < 0 ) {
            ret = recursive_delete(&((*pRoot)->left), key, compare);
        // �������ݹ���� 
        } else if( r > 0 ) {
            ret = recursive_delete(&((*pRoot)->right), key, compare);
        }
    }
    
    return ret;
}

// ���������� 
BSTree* BSTree_Create() // O(1)
{
    TBSTree* ret = (TBSTree*)malloc(sizeof(TBSTree));
    
    if( ret != NULL ) {
        ret->count = 0;
        ret->root = NULL;
    }
    
    return ret;
}

// �ݻٶ����� 
void BSTree_Destroy(BSTree* tree) // O(1)
{
    free(tree);
}

// ��ն����� 
void BSTree_Clear(BSTree* tree) // O(1)
{
    TBSTree* btree = (TBSTree*)tree;
    
    if(btree != NULL) {
        btree->count = 0;
        btree->root = NULL;
    }
}

// ��������� 
int BSTree_Insert(BSTree* tree, BSTreeNode* node, BSTree_Compare* compare) 
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = (btree != NULL) && (node != NULL) && (compare != NULL);
    
    if(ret) {
    	// ����ڵ㸳ֵ 
        node->left = NULL;
        node->right = NULL;
        
        // ���ڵ� 
        if(btree->root == NULL) {
            btree->root = node;
        } else {
            ret = recursive_insert(btree->root, node, compare);
        }
        
        // ����ɹ� count++ 
        if(ret) {
            btree->count++;
        }
    }
    
    return ret;
}

//brief ��������ɾ�� 
BSTreeNode* BSTree_Delete(BSTree* tree, BSKey* key, BSTree_Compare* compare)
{
    TBSTree* btree = (TBSTree*)tree;
    BSTreeNode* ret = NULL; 
    
    if((btree != NULL) && (key != NULL) && (compare != NULL)) {
        ret = recursive_delete(&btree->root, key, compare);
        
        // ���ɾ���ɹ� count-- 
        if( ret != NULL )
        {
            btree->count--;
        }
    }
    
    return ret;
}

// �ڵ��ȡ 
BSTreeNode* BSTree_Get(BSTree* tree, BSKey* key, BSTree_Compare* compare)
{
    TBSTree* btree = (TBSTree*)tree;
    BSTreeNode* ret = NULL; 
    
    if((btree != NULL) && (key != NULL) && (compare != NULL)) {
        ret = recursive_get(btree->root, key, compare);
    }
    
    return ret;
}

// ���ڵ� 
BSTreeNode* BSTree_Root(BSTree* tree) // O(1)
{
    TBSTree* btree = (TBSTree*)tree;
    BSTreeNode* ret = NULL;
    
    if( btree != NULL ) {
        ret = btree->root;
    }
    
    return ret;
}

// ���� 
int BSTree_Height(BSTree* tree) // O(n)
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = 0;
    
    if(btree != NULL) {
        ret = recursive_height(btree->root);
    }
    
    return ret;
}

// ���ڵ��� 
int BSTree_Count(BSTree* tree) // O(1)
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = 0;
    
    if(btree != NULL) {
        ret = btree->count;
    }
    
    return ret;
}

// �������Ķ� 
int BSTree_Degree(BSTree* tree) // O(n)
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = 0;
    
    if(btree != NULL) {
        ret = recursive_degree(btree->root);
    }
    
    return ret;
}

// ��������ӡ 
void BSTree_Display(BSTree* tree, BSTree_Printf* pFunc, int gap, char div) // O(n)
{
    TBSTree* btree = (TBSTree*)tree;
    
    if( btree != NULL )
    {
        recursive_display(btree->root, pFunc, 0, gap, div);
    }
}
