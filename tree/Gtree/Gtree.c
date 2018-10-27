#include <stdio.h>
#include <malloc.h> 
#include "list.h"
#include "Gtree.h"
 
 
 
 //		����ͨ�����ṹ�����������еĽṹ����������������һ��
 //	ͨ�������Ǵ������� 
 
 
 
// GTree �ڵ���Ϣ�ṹ�� 
typedef struct _tag_GTreeNode {
	GTreeData 			  *data;	// �ڵ����� 
	LinkList			  *child;	// ���ӽڵ� 
	struct _tag_GTreeNode *parent;	// ���׽ڵ�
} tree_node_t;

// ��ʽ���ڵ� 
typedef struct _tag_TLNode {
	LinkListNode_t header;
	tree_node_t *node; 
} tree_list_node_t;



/*************************************************************
*	static function 
*************************************************************/

/**
 *	format ��ʾ�ӵڼ������ſ�ʼ�ָ�  gap ��ʾÿһ����ն���  divΪ�ָ�� 
 */
static void Recursive_display(tree_node_t *node, Gtree_Printf pfunc, int format, int gap, char div)
{
	int i  = 0;
	
	if ((node != NULL) && (pfunc != NULL)) {
		for(i = 0; i < format; i++) {
			printf("%c", div);
		} 
		
		// ִ���û�����ĺ��� 
		pfunc(node->data);
		
		//  ���� 
		printf("\n");
		
		for (i = 0; i < LinkList_Length_Get(node->child); i++) {
			tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(node->child, i);
			Recursive_display(trnode->node, pfunc, format + gap, gap, div);
		} 
	} 
}


static void Recursive_delete (LinkList *list, tree_node_t *node) 
{
	if ((list != NULL) && (node != NULL)) {
		// ���游�ڵ� 
		tree_node_t *parent = node->parent;
		int index = -1;  // λ����Ϣ
		int i = 0;
		
		// ���� ����ͨ�� 
		for (i = 0; i < LinkList_Length_Get(list); i++) {
			
			// ��ȡͨ���ڵ���Ϣ 
			tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(list, i);
			
			if(trnode->node == node) {
				// ɾ��ͨ���ڵ� 
				LinkList_Delete(list, i);
				free(trnode); 
				index = i;
				break;
			} 
		}  // ɾ��ͨ�� 
		
		// �ҵ�Ҫɾ���Ľڵ� 
		if (index  >= 0) {
			
			// ���Ǹ��ڵ� 
			if (parent != NULL)  {
				
				// ѭ���ҽڵ� ɾ���ýڵ� 
				for (i = 0; i < LinkList_Length_Get(parent->child); i++) {
					tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(parent->child, i);
					
					if (trnode->node == node) {
						LinkList_Delete(parent->child, i);
						free(trnode);
						break; 
					} 
				} // ���� 
			} // if (parent != NULL) 
			
			// ������Ϊֹ �Ѿ�ɾ��ͨ���Ľڵ� �� ���ӽڵ� 
			// ���￪ʼѭ���ݹ� ɾ�� 
			while (LinkList_Length_Get(node->child) > 0) {
				tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(node->child, 0);
				
				Recursive_delete(list, trnode->node); 
			} 
			
			// �ݻ��� 
			LinkList_Destroy(node->child);
			
			// ��սڵ���Ϣ 
			free(node); 
			
		}  // ɾ�����ӽڵ� 
	}
} 

// �ݹ� �����ĸ߶� 
static int Recursive_hight(tree_node_t *node) 
{
	int ret = 0;
	
	if(node != NULL) {
		int subhight = 0;  // �����ĸ߶� 
		int i = 0;
		
		for (i = 0; i < LinkList_Length_Get(node->child); i++) {
			tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(node->child, i);
			
			subhight = Recursive_hight(trnode->node);
			
			// ��� ���صı���С�����ĸ߶�  ��ֵ   
			if (subhight > ret) {
				ret = subhight;
			}
		}
		
		// �ݹ����һ�����ڵ�  �߶�+1 
		ret = ret + 1;
	} 	
	return ret; 
}

static int Recursive_degree(tree_node_t *node)
{
	int ret = -1;
	if(node != NULL) {
		int subdegree = 0;
		int i = 0;
		
		// ���ڵ�ĳ��� ���Ƕ� 
		ret =LinkList_Length_Get(node->child);
		
		for (i = 0; i < LinkList_Length_Get(node->child); i++) {
			tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(node->child, i);
			
			subdegree =  Recursive_degree(trnode->node);
	
			if (subdegree > ret) {
				ret = subdegree;
			}
		} 
	}
	
	return ret;
}

static void Recursive_search(tree_node_t *node, Gtree_Printf pfunc)
{
	if (node != NULL) {
		
		if (node->parent == NULL) {
			pfunc(node->data);
		} else {
			Recursive_search(node->parent, pfunc);
			printf("->");
			pfunc(node->data);
		} 
	}
}


/*************************************************************
*	user function 
*************************************************************/

// 1.������ 
GTree *GTree_Create(void)
{
	return LinkList_Create();
}

// 2.�ݻ���
void GTree_Destroy(GTree *tree)
{
	GTree_Clear(tree);
	LinkList_Destroy(tree);
} 

// 3.�����
void GTree_Clear(GTree *tree)
{
	GTree_Delete(tree, 0); 
}

// 4.������Ԫ�� 
int GTree_Insert(GTree *tree, GTreeData *data, int pPos)
{
	LinkList *list = (LinkList *)tree;  // ��תΪͨ����ͷ 
	
	// pPos ��ʾ���׽ڵ� 
	int ret = ((list != NULL) && (data != NULL) && (pPos < LinkList_Length_Get(list)));
	
	if (ret) {
		// ����ͨ���ռ�����  �� ������������ 
		tree_list_node_t *trnode  = (tree_list_node_t *)malloc(sizeof(tree_list_node_t));
		tree_list_node_t *cldnode = (tree_list_node_t *)malloc(sizeof(tree_list_node_t));
		
		// ��ȡ ͨ���е�pPos������� ��ʵ��Ϊ���ڵ� 
		tree_list_node_t *pnode  = (tree_list_node_t *)LinkList_Get(list, pPos);
		
		// �������ڵ���Ϣ�ṹ��ռ�
		tree_node_t *cnode = (tree_node_t *)malloc(sizeof(tree_node_t));
		
		ret = ((trnode != NULL) && (cldnode != NULL) && (cnode != NULL));
		
		if (ret) {
			cnode->data = data;
			cnode->child = LinkList_Create(); // ���´���һ����
			cnode->parent = NULL;	// �Ȳ����ж� ����Ϊ�����Ǹ��ڵ�
			
			trnode->node = cnode;
			cldnode->node = cnode; 
			
			// ���ڵ����ͨ�������һλ 
			LinkList_Insert(list, (LinkListNode_t *)trnode, LinkList_Length_Get(list));
			
			// �������ĸ��ڵ㲻Ϊ�� 
			if (pnode != NULL) {
				
				// ���ڵ�ָ�� 
				cnode->parent = pnode->node;
				
				// �����ӽڵ���ʽ���� 
				LinkList_Insert(pnode->node->child, (LinkListNode_t *)cldnode, LinkList_Length_Get(pnode->node->child)); 
			} 
		} else {  //  �ռ�����ʧ�� ,�ͷſռ� 
			free(trnode);
			free(cldnode);
			free(cnode); 
		} 
	}  
	
	return ret;
}

// 5.ɾ����Ԫ��
GTreeData *GTree_Delete(GTree *tree, int pos)
{
	// ��ȡ���ڵ�λ����Ϣ 
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, pos);
	GTreeData *ret = NULL;
	
	if (trnode != NULL) {
		// �������� 
		ret = trnode->node->data;
		
		// �ݹ�ɾ����֧�ڵ��µ�Ҷ�ڵ� 
		Recursive_delete(tree, trnode->node);
	} 
	return ret;
}

// 6.��ȡ���ڵ�
GTreeData *GTree_Get(GTree *tree, int pos)
{
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, pos);
	GTreeData *ret = NULL;
	if (trnode != NULL) {
		ret = trnode->node->data;
	}
	return ret;
}

// 7.��ȡ�����ڵ�
GTreeData *GTree_Root_Get(GTree *tree)
{
	return GTree_Get(tree, 0);
}

// 8.���ĸ߶�
int GTree_Hight_Get(GTree *tree)
{
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, 0);
	int ret = 0;
	if(trnode != NULL) {
		ret = Recursive_hight(trnode->node);
	}

	return ret;
}

// 9.���Ľڵ���
int GTree_Count_Get(GTree *tree)
{
	return LinkList_Length_Get(tree);
}

// 10.���Ķ�
int GTree_Degree_Get(GTree *tree)
{
	int ret = 0;
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, 0);
	
	if (trnode != NULL) {
		ret = Recursive_degree(trnode->node);
	}
	 
	return ret;
}

// 11.��ӡ���ṹ
void GTree_Display(GTree *tree, Gtree_Printf pfunc, int gap, char div)
{
	// ��ȡ���ڵ���Ϣ 
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, 0); 
	
	if ((trnode != NULL) && (pfunc != NULL)) {
		Recursive_display(trnode->node, pfunc, 0, gap, div);
	} 
} 

// 12.���� ����λ 
int GTree_Search(GTree *tree, GTreeData *data, Gtree_Printf pfun)
{
	// ��ȡ���ڵ���Ϣ 
	LinkList *list = (LinkList *)tree;  // ��תΪͨ����ͷ 
	int ret = -1;
	int i = 0;
	
	// �Ϸ��ж� 
	if((list != NULL) && (data != NULL) && (pfun != NULL)) {
		
		// ����ͨ�� 
		for (i = 0; i < LinkList_Length_Get(list); i++) {
			tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, i); 
			
			// �ҵ����� 
			if (trnode->node->data == data) {
				ret = i;
				printf("position: %d\n", i);
				Recursive_search(trnode->node, pfun);
				printf("\n");
				break;
			}
		}	
	}	
	return ret;
}















