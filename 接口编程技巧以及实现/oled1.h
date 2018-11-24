#ifndef __OLED1_H__
#define __OLED1_H__

#include "interface.h"


typedef struct oled1_info {
	const char *name; /* 设备名 */
	// Users can add members... idle
}oled1_info_t; 

/** \brief oled设备 */
typedef struct oled1 {
	oled_serv_t          isa;  /**< \brief 继承oled通用设备 */ 
	const oled1_info_t  *info; /**< \brief 设备信息         */ 
	// Users can add members... idle
}oled1_t;

/** \brief 设备句柄 */
typedef oled1_t *oled1_handle;


/** \brief 初始化 */
oled_handle oled1_init(oled1_handle        handle,
					   const oled1_info_t *info);


/** \brief 解初始化 */ 
void oled1_deinit(oled1_handle handle);


#endif

/* end of file */


