objects = main.o hwconf_oled1.o oled1.o   # 项目文件
CC = gcc                                 # 全局定义编译器 

a.out : $(objects)                     # 目标
	$(CC) -o a.out $(objects)

.PHONY : clean
clean:
	rm a.out $(objects) -rf 
	clear
	ls