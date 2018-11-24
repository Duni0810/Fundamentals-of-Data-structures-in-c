#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stdio.h>

#define  FONT_SIZE_6_8         0x00  /**< \biref 6x8  ���� */
#define  FONT_SIZE_6_12        0x01  /**< \biref 6x12 ���� */
#define  FONT_SIZE_12_24       0x02  /**< \biref 12x24���� */

/**
 * \brief ���ܺ����ṹ�� 
 */ 
struct oled_funcs {
	/** \brief ����������Ϣ */
	void (*oled_font_size_config)(void *p_drv, int request);
	
	/** \brief ��ʾ�ַ���   */ 
	void (*oled_str_show)(void *p_drv, const char *p_data);
	
	/** \brief ��ʾͼƬ */ 
	void (*oled_graph_show)(void *p_drv, const char *p_data, size_t size);
}; 

/** \brief oled���� */
typedef struct oled_serv{
	const struct oled_funcs *funcs; /**< \brief ���ܺ���       */
	void *p_arg;			        /**< \brief ������һ������ */ 
} oled_serv_t;


typedef oled_serv_t *oled_handle;  /**< oledͨ�÷����� */

/** broef �ַ���С���� */
inline
static void oled_font_size_cfg (oled_handle handle, int request)
{
	handle->funcs->oled_font_size_config(handle->p_arg,
									    request);
}

/** \brief ��ʾ�ַ� */
inline
static void oled_str_show(oled_handle handle, const char *p_str)
{
	 handle->funcs->oled_str_show(handle->p_arg,
							 	  p_str);
} 


/** \brief ��ʾͼƬ */
inline
static void oled_graph_show(oled_handle  handle, 
							const char  *p_buf, 
							size_t       size)
{
	 handle->funcs->oled_graph_show(handle->p_arg,
							 	    p_buf,
									size);
}

#endif 

/* end of file */

