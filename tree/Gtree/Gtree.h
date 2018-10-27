#ifndef __GTREE_H
#define __GTREE_H

// �������� 
typedef void GTree;

// ���е��������� 
typedef void GTreeData;

// ���Ĵ�ӡ���� 
typedef void (*Gtree_Printf)(GTreeData *);


// 1.������ 
GTree *GTree_Create(void);

// 2.�ݻ���
void GTree_Destroy(GTree *tree); 

// 3.�����
void GTree_Clear(GTree *tree); 

// 4.������Ԫ�� 
int GTree_Insert(GTree *tree, GTreeData *data, int pos);

// 5.ɾ����Ԫ��
GTreeData *GTree_Delete(GTree *tree, int pos);

// 6.��ȡ���ڵ�
GTreeData *GTree_Get(GTree *tree, int pos);

// 7.��ȡ�����ڵ�
GTreeData *GTree_Root_Get(GTree *tree);

// 8.���ĸ߶�
int GTree_Hight_Get(GTree *tree); 

// 9.���Ľڵ���
int GTree_Count_Get(GTree *tree);

// 10.���Ķ�
int GTree_Degree_Get(GTree *tree);

// 11.��ӡ���ṹ
void GTree_Display(GTree *tree, Gtree_Printf pfun, int gap, char div); 

// 12. ���Ĳ��Һ���
int GTree_Search(GTree *tree, GTreeData *data, Gtree_Printf pfun); 
 
#endif

