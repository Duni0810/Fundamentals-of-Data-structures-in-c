#ifndef __OLED1_H__
#define __OLED1_H__

#include "interface.h"


typedef struct oled1_info {
	const char *name; /* �豸�� */
	// Users can add members... idle
}oled1_info_t; 

/** \brief oled�豸 */
typedef struct oled1 {
	oled_serv_t          isa;  /**< \brief �̳�oledͨ���豸 */ 
	const oled1_info_t  *info; /**< \brief �豸��Ϣ         */ 
	// Users can add members... idle
}oled1_t;

/** \brief �豸��� */
typedef oled1_t *oled1_handle;


/** \brief ��ʼ�� */
oled_handle oled1_init(oled1_handle        handle,
					   const oled1_info_t *info);


/** \brief ���ʼ�� */ 
void oled1_deinit(oled1_handle handle);


#endif

/* end of file */


