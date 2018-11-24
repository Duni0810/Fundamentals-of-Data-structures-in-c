#include "hwconf_oled1.h"
#include "oled1.h"


static const  oled1_info_t __g_oled_info = {
	"oled1\0",  /**< \brief �豸�� */
};

static  oled1_t __g_oled_dev;

/** \brief ʵ����ʼ�� */
oled_handle oled1_inst_init()
{
	return oled1_init(&__g_oled_dev, &__g_oled_info);
}


/** \brief ʵ����ʼ�� */
void oled1_inst_deinit(oled_handle handle)
{
	oled1_deinit(handle->p_arg);
}

/* end of file */

