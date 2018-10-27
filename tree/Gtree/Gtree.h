#ifndef __GTREE_H
#define __GTREE_H

// 树的类型 
typedef void GTree;

// 树中的数据类型 
typedef void GTreeData;

// 树的打印函数 
typedef void (*Gtree_Printf)(GTreeData *);


// 1.创建树 
GTree *GTree_Create(void);

// 2.摧毁树
void GTree_Destroy(GTree *tree); 

// 3.清空树
void GTree_Clear(GTree *tree); 

// 4.插入树元素 
int GTree_Insert(GTree *tree, GTreeData *data, int pos);

// 5.删除树元素
GTreeData *GTree_Delete(GTree *tree, int pos);

// 6.获取树节点
GTreeData *GTree_Get(GTree *tree, int pos);

// 7.获取树根节点
GTreeData *GTree_Root_Get(GTree *tree);

// 8.树的高度
int GTree_Hight_Get(GTree *tree); 

// 9.树的节点数
int GTree_Count_Get(GTree *tree);

// 10.树的度
int GTree_Degree_Get(GTree *tree);

// 11.打印树结构
void GTree_Display(GTree *tree, Gtree_Printf pfun, int gap, char div); 

// 12. 树的查找函数
int GTree_Search(GTree *tree, GTreeData *data, Gtree_Printf pfun); 
 
#endif

