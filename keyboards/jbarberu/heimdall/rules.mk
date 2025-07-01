QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes

SRC += lvgl_helpers.c 		\
	   display.c	  		\
	   lvgl/dejavu_sans_12.c	  	\
	   lvgl/dejavu_sans_18.c	  	\
	   lvgl/dejavu_sans_24.c	  	\
	   lvgl/dejavu_sans_32.c	  	\
	   lvgl/dejavu_sans_48.c
