#ifndef __LIST_H_
#define __LIST_H_

/* void *  ��һ���������͵�ƥ�� */ 
typedef void LinkList; 

typedef struct LinkListNode {
	struct LinkListNode *next; /* ָ����һ���ڵ�ĵ�ַ */
} LinkListNode_t;

/**
 * \brief ����һ���ڵ� 
 *
 * \ret  �ڵ�ĵ�ַ 
 */ 
LinkList* LinkList_Create (void);

/**
 * \brief �ݻ��������� 
 *
 * \param list[in]   �ڵ�ĵ�ַ 
 */ 
void LinkList_Destroy (LinkList* list);

/**
 * \brief ����������� 
 *
 * \param list[in]  ����ı�ͷ 
 */ 
void LinkList_Clear (LinkList* list);

/**
 * \brief ��ȡ������ 
 *
 * \param list[in]  �����ͷ�ڵ� 
 *
 * \ret ����ĳ��� 
 */ 
int LinkList_Length_Get (LinkList* list);

/**
 * \brief �������� 
 *
 * \param list[in]  ����ı�ͷ 
 * \param node[in]  �����������
 * \param pos[in]   �������λ��  
 *
 * \ret 1 ok  else error 
 */ 
int LinkList_Insert (LinkList* list, LinkListNode_t* node, int pos);

/**
 * \brief ��ȡ����ڵ���Ϣ
 * 
 * \param list[in]
 * \param pos[in]
 *
 * \ret ���ؽڵ�ĵ�ַ 
 */
LinkListNode_t* LinkList_Get (LinkList* list, int pos);

/**
 * \brief ɾ��һ���ڵ� 
 * 
 * \param list[in]  ͷ�ڵ�
 * \param pos[in]   ��ɾ���Ľڵ�λ�� 
 * 
 * \ret Ҫɾ���Ľڵ��ַ 
 */ 
LinkListNode_t* LinkList_Delete (LinkList* list, int pos);



#endif 

