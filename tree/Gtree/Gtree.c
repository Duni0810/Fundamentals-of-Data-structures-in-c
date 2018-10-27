#include <stdio.h>
#include <malloc.h> 
#include "list.h"
#include "Gtree.h"
 
 
 
 //		由于通用树结构不容易用现有的结构描述，这里我们用一个
 //	通链将他们串起来。 
 
 
 
// GTree 节点信息结构体 
typedef struct _tag_GTreeNode {
	GTreeData 			  *data;	// 节点数据 
	LinkList			  *child;	// 孩子节点 
	struct _tag_GTreeNode *parent;	// 父亲节点
} tree_node_t;

// 链式树节点 
typedef struct _tag_TLNode {
	LinkListNode_t header;
	tree_node_t *node; 
} tree_list_node_t;



/*************************************************************
*	static function 
*************************************************************/

/**
 *	format 表示从第几个符号开始分割  gap 表示每一级间空多少  div为分割符 
 */
static void Recursive_display(tree_node_t *node, Gtree_Printf pfunc, int format, int gap, char div)
{
	int i  = 0;
	
	if ((node != NULL) && (pfunc != NULL)) {
		for(i = 0; i < format; i++) {
			printf("%c", div);
		} 
		
		// 执行用户闯入的函数 
		pfunc(node->data);
		
		//  换行 
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
		// 保存父节点 
		tree_node_t *parent = node->parent;
		int index = -1;  // 位置信息
		int i = 0;
		
		// 遍历 数的通链 
		for (i = 0; i < LinkList_Length_Get(list); i++) {
			
			// 获取通链节点信息 
			tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(list, i);
			
			if(trnode->node == node) {
				// 删除通链节点 
				LinkList_Delete(list, i);
				free(trnode); 
				index = i;
				break;
			} 
		}  // 删除通链 
		
		// 找到要删除的节点 
		if (index  >= 0) {
			
			// 不是根节点 
			if (parent != NULL)  {
				
				// 循环找节点 删除该节点 
				for (i = 0; i < LinkList_Length_Get(parent->child); i++) {
					tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(parent->child, i);
					
					if (trnode->node == node) {
						LinkList_Delete(parent->child, i);
						free(trnode);
						break; 
					} 
				} // 查找 
			} // if (parent != NULL) 
			
			// 到这里为止 已经删除通链的节点 和 孩子节点 
			// 这里开始循环递归 删除 
			while (LinkList_Length_Get(node->child) > 0) {
				tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(node->child, 0);
				
				Recursive_delete(list, trnode->node); 
			} 
			
			// 摧毁链 
			LinkList_Destroy(node->child);
			
			// 清空节点信息 
			free(node); 
			
		}  // 删除孩子节点 
	}
} 

// 递归 找树的高度 
static int Recursive_hight(tree_node_t *node) 
{
	int ret = 0;
	
	if(node != NULL) {
		int subhight = 0;  // 子数的高度 
		int i = 0;
		
		for (i = 0; i < LinkList_Length_Get(node->child); i++) {
			tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(node->child, i);
			
			subhight = Recursive_hight(trnode->node);
			
			// 如果 返回的变量小于树的高度  赋值   
			if (subhight > ret) {
				ret = subhight;
			}
		}
		
		// 递归完成一个父节点  高度+1 
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
		
		// 根节点的长度 就是度 
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

// 1.创建树 
GTree *GTree_Create(void)
{
	return LinkList_Create();
}

// 2.摧毁树
void GTree_Destroy(GTree *tree)
{
	GTree_Clear(tree);
	LinkList_Destroy(tree);
} 

// 3.清空树
void GTree_Clear(GTree *tree)
{
	GTree_Delete(tree, 0); 
}

// 4.插入树元素 
int GTree_Insert(GTree *tree, GTreeData *data, int pPos)
{
	LinkList *list = (LinkList *)tree;  // 先转为通链的头 
	
	// pPos 表示父亲节点 
	int ret = ((list != NULL) && (data != NULL) && (pPos < LinkList_Length_Get(list)));
	
	if (ret) {
		// 树型通链空间申请  与 树形子链申请 
		tree_list_node_t *trnode  = (tree_list_node_t *)malloc(sizeof(tree_list_node_t));
		tree_list_node_t *cldnode = (tree_list_node_t *)malloc(sizeof(tree_list_node_t));
		
		// 获取 通链中的pPos点的数据 其实就为父节点 
		tree_list_node_t *pnode  = (tree_list_node_t *)LinkList_Get(list, pPos);
		
		// 创建树节点信息结构体空间
		tree_node_t *cnode = (tree_node_t *)malloc(sizeof(tree_node_t));
		
		ret = ((trnode != NULL) && (cldnode != NULL) && (cnode != NULL));
		
		if (ret) {
			cnode->data = data;
			cnode->child = LinkList_Create(); // 重新创建一个链
			cnode->parent = NULL;	// 先不做判断 ，因为可能是根节点
			
			trnode->node = cnode;
			cldnode->node = cnode; 
			
			// 将节点插入通链的最后一位 
			LinkList_Insert(list, (LinkListNode_t *)trnode, LinkList_Length_Get(list));
			
			// 如果插入的父节点不为空 
			if (pnode != NULL) {
				
				// 父节点指向 
				cnode->parent = pnode->node;
				
				// 插入子节点链式表中 
				LinkList_Insert(pnode->node->child, (LinkListNode_t *)cldnode, LinkList_Length_Get(pnode->node->child)); 
			} 
		} else {  //  空间申请失败 ,释放空间 
			free(trnode);
			free(cldnode);
			free(cnode); 
		} 
	}  
	
	return ret;
}

// 5.删除树元素
GTreeData *GTree_Delete(GTree *tree, int pos)
{
	// 获取树节点位置信息 
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, pos);
	GTreeData *ret = NULL;
	
	if (trnode != NULL) {
		// 保存数据 
		ret = trnode->node->data;
		
		// 递归删除分支节点下的叶节点 
		Recursive_delete(tree, trnode->node);
	} 
	return ret;
}

// 6.获取树节点
GTreeData *GTree_Get(GTree *tree, int pos)
{
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, pos);
	GTreeData *ret = NULL;
	if (trnode != NULL) {
		ret = trnode->node->data;
	}
	return ret;
}

// 7.获取树根节点
GTreeData *GTree_Root_Get(GTree *tree)
{
	return GTree_Get(tree, 0);
}

// 8.树的高度
int GTree_Hight_Get(GTree *tree)
{
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, 0);
	int ret = 0;
	if(trnode != NULL) {
		ret = Recursive_hight(trnode->node);
	}

	return ret;
}

// 9.树的节点数
int GTree_Count_Get(GTree *tree)
{
	return LinkList_Length_Get(tree);
}

// 10.树的度
int GTree_Degree_Get(GTree *tree)
{
	int ret = 0;
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, 0);
	
	if (trnode != NULL) {
		ret = Recursive_degree(trnode->node);
	}
	 
	return ret;
}

// 11.打印树结构
void GTree_Display(GTree *tree, Gtree_Printf pfunc, int gap, char div)
{
	// 获取根节点信息 
	tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, 0); 
	
	if ((trnode != NULL) && (pfunc != NULL)) {
		Recursive_display(trnode->node, pfunc, 0, gap, div);
	} 
} 

// 12.查找 并定位 
int GTree_Search(GTree *tree, GTreeData *data, Gtree_Printf pfun)
{
	// 获取根节点信息 
	LinkList *list = (LinkList *)tree;  // 先转为通链的头 
	int ret = -1;
	int i = 0;
	
	// 合法判断 
	if((list != NULL) && (data != NULL) && (pfun != NULL)) {
		
		// 遍历通链 
		for (i = 0; i < LinkList_Length_Get(list); i++) {
			tree_list_node_t *trnode = (tree_list_node_t *)LinkList_Get(tree, i); 
			
			// 找到数据 
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















