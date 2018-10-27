#ifndef __STATIC_LIST_H_
#define __STATIC_LIST_H_

typedef void StaticList;
typedef void StaticListNode;

/**
 * \brief ����һ���ڵ� 
 *
 * \ret  �ڵ�ĵ�ַ 
 */ 
StaticList *StaticList_Create (int capacity);

/**
 * \brief �ݻ��������� 
 *
 * \param list[in]   �ڵ�ĵ�ַ 
 */ 
void StaticList_Destroy (StaticList* list);

/**
 * \brief ����������� 
 *
 * \param list[in]  ����ı�ͷ 
 */ 
void StaticList_Clear (StaticList* list);

/**
 * \brief ��ȡ������ 
 *
 * \param list[in]  �����ͷ�ڵ� 
 *
 * \ret ����ĳ��� 
 */ 
int StaticList_Length_Get (StaticList* list);

/**
 * \brief ��ȡ�����С 
 *
 * \param list[in]  �����ͷ�ڵ� 
 *
 * \ret ����Ĵ�С 
 */ 
int StaticList_Capacity_Get (StaticList* list);
/**
 * \brief �������� 
 *
 * \param list[in]  ����ı�ͷ 
 * \param node[in]  �����������
 * \param pos[in]   �������λ��  
 *
 * \ret 1 ok  else error 
 */ 
int StaticList_Insert (StaticList* list, StaticListNode* node, int pos);

/**
 * \brief ��ȡ����ڵ���Ϣ
 * 
 * \param list[in]
 * \param pos[in]
 *
 * \ret ���ؽڵ�ĵ�ַ 
 */
StaticListNode* StaticList_Get (StaticList* list, int pos);

/**
 * \brief ɾ��һ���ڵ� 
 * 
 * \param list[in]  ͷ�ڵ�
 * \param pos[in]   ��ɾ���Ľڵ�λ�� 
 * 
 * \ret Ҫɾ���Ľڵ��ַ 
 */ 
StaticListNode* LinkList_Delete (StaticList* list, int pos);



#endif 

