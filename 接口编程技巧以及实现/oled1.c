#include "oled1.h"

typedef unsigned char uint8_t;

#define  OLED_DECL(handle, p_drv)  \
				oled1_handle handle = (oled1_handle) p_drv


/** broef �ַ���С���� */
static void __oled1_font_size_cfg (void *p_drv, int request)
{
	OLED_DECL(handle, p_drv);  // ���Ͷ��� 
	
	uint8_t data[][6] = {"6x8\0", "6x12\0", "12x24\0"};
	
	printf("dev is :%s\n", handle->info->name);  //�豸��Ϣ��ӡ������handle 
	
	printf("Set the oled font to %s \n",data[request]);
}

/** \brief ��ʾ�ַ� */
static void __oled1_str_show(void *p_drv, const char *p_str)
{
	OLED_DECL(handle, p_drv);  // ���Ͷ��� 
	printf("dev is :%s\n", handle->info->name); //�豸��Ϣ��ӡ������handle 
	
	printf("display data:%s\n",p_str);
} 


/** \brief ��ʾͼƬ */
static void __oled1_graph_show(void *p_drv, const char  *p_buf, size_t size)
{
	OLED_DECL(handle, p_drv);  // ���Ͷ��� 
	printf("dev is :%s\n", handle->info->name); //�豸��Ϣ��ӡ������handle 
	int i = 0;
	for (i = 0; i < size; i++) {
		printf("%c", *p_buf++);
	}
	printf("\n");
}


static const struct oled_funcs __g_oled1_funcs = {
	__oled1_font_size_cfg,
	__oled1_str_show,
	__oled1_graph_show,
};


/** \brief ��ʼ�� */
oled_handle oled1_init(oled1_handle        handle,
					   const oled1_info_t *info)
{
	// handle ��Ϣ��� 
	handle->info      = info;
	handle->isa.funcs = &__g_oled1_funcs;
	handle->isa.p_arg = handle;
	
	// run dev functions 
	
	printf("init oled1 ok\n");
	return (&handle->isa);
}


/** \brief ���ʼ�� */ 
void oled1_deinit(oled1_handle handle)
{
	printf("deinit %s \n", handle->info->name);
}







