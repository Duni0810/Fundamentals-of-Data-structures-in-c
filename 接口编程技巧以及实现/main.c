#include <stdio.h>
#include <stdlib.h>
#include "hwconf_oled1.h"

#define   FOEVER       for(;;)

int main(int argc, char *argv[]) {
	
	// 初始化 
	oled_handle handle = oled1_inst_init();
	
	// 字体设置 
	oled_font_size_cfg(handle, FONT_SIZE_12_24);
	printf("\n"); 
	
	// 打印字符 
	oled_str_show(handle, "young_test\n"); 
	printf("\n"); 
	
	char p_data[] = {0x31, 0x32, 0x41, 0x42}; // 12AB 
	oled_graph_show(handle, p_data, sizeof(p_data));
	
	oled1_inst_deinit(handle); 
		
	return 1;
}
