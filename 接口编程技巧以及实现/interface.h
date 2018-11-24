#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stdio.h>

#define  FONT_SIZE_6_8         0x00  /**< \biref 6x8  字体 */
#define  FONT_SIZE_6_12        0x01  /**< \biref 6x12 字体 */
#define  FONT_SIZE_12_24       0x02  /**< \biref 12x24字体 */

/**
 * \brief 功能函数结构体 
 */ 
struct oled_funcs {
	/** \brief 配置字体信息 */
	void (*oled_font_size_config)(void *p_drv, int request);
	
	/** \brief 显示字符串   */ 
	void (*oled_str_show)(void *p_drv, const char *p_data);
	
	/** \brief 显示图片 */ 
	void (*oled_graph_show)(void *p_drv, const char *p_data, size_t size);
}; 

/** \brief oled服务 */
typedef struct oled_serv{
	const struct oled_funcs *funcs; /**< \brief 功能函数       */
	void *p_arg;			        /**< \brief 函数第一个参数 */ 
} oled_serv_t;


typedef oled_serv_t *oled_handle;  /**< oled通用服务句柄 */

/** broef 字符大小设置 */
inline
static void oled_font_size_cfg (oled_handle handle, int request)
{
	handle->funcs->oled_font_size_config(handle->p_arg,
									    request);
}

/** \brief 显示字符 */
inline
static void oled_str_show(oled_handle handle, const char *p_str)
{
	 handle->funcs->oled_str_show(handle->p_arg,
							 	  p_str);
} 


/** \brief 显示图片 */
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

