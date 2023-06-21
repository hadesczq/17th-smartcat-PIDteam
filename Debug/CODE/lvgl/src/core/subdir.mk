################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/lvgl/src/core/lv_disp.c \
../CODE/lvgl/src/core/lv_event.c \
../CODE/lvgl/src/core/lv_group.c \
../CODE/lvgl/src/core/lv_indev.c \
../CODE/lvgl/src/core/lv_indev_scroll.c \
../CODE/lvgl/src/core/lv_obj.c \
../CODE/lvgl/src/core/lv_obj_class.c \
../CODE/lvgl/src/core/lv_obj_draw.c \
../CODE/lvgl/src/core/lv_obj_pos.c \
../CODE/lvgl/src/core/lv_obj_scroll.c \
../CODE/lvgl/src/core/lv_obj_style.c \
../CODE/lvgl/src/core/lv_obj_style_gen.c \
../CODE/lvgl/src/core/lv_obj_tree.c \
../CODE/lvgl/src/core/lv_refr.c \
../CODE/lvgl/src/core/lv_theme.c 

OBJS += \
./CODE/lvgl/src/core/lv_disp.o \
./CODE/lvgl/src/core/lv_event.o \
./CODE/lvgl/src/core/lv_group.o \
./CODE/lvgl/src/core/lv_indev.o \
./CODE/lvgl/src/core/lv_indev_scroll.o \
./CODE/lvgl/src/core/lv_obj.o \
./CODE/lvgl/src/core/lv_obj_class.o \
./CODE/lvgl/src/core/lv_obj_draw.o \
./CODE/lvgl/src/core/lv_obj_pos.o \
./CODE/lvgl/src/core/lv_obj_scroll.o \
./CODE/lvgl/src/core/lv_obj_style.o \
./CODE/lvgl/src/core/lv_obj_style_gen.o \
./CODE/lvgl/src/core/lv_obj_tree.o \
./CODE/lvgl/src/core/lv_refr.o \
./CODE/lvgl/src/core/lv_theme.o 

COMPILED_SRCS += \
./CODE/lvgl/src/core/lv_disp.src \
./CODE/lvgl/src/core/lv_event.src \
./CODE/lvgl/src/core/lv_group.src \
./CODE/lvgl/src/core/lv_indev.src \
./CODE/lvgl/src/core/lv_indev_scroll.src \
./CODE/lvgl/src/core/lv_obj.src \
./CODE/lvgl/src/core/lv_obj_class.src \
./CODE/lvgl/src/core/lv_obj_draw.src \
./CODE/lvgl/src/core/lv_obj_pos.src \
./CODE/lvgl/src/core/lv_obj_scroll.src \
./CODE/lvgl/src/core/lv_obj_style.src \
./CODE/lvgl/src/core/lv_obj_style_gen.src \
./CODE/lvgl/src/core/lv_obj_tree.src \
./CODE/lvgl/src/core/lv_refr.src \
./CODE/lvgl/src/core/lv_theme.src 

C_DEPS += \
./CODE/lvgl/src/core/lv_disp.d \
./CODE/lvgl/src/core/lv_event.d \
./CODE/lvgl/src/core/lv_group.d \
./CODE/lvgl/src/core/lv_indev.d \
./CODE/lvgl/src/core/lv_indev_scroll.d \
./CODE/lvgl/src/core/lv_obj.d \
./CODE/lvgl/src/core/lv_obj_class.d \
./CODE/lvgl/src/core/lv_obj_draw.d \
./CODE/lvgl/src/core/lv_obj_pos.d \
./CODE/lvgl/src/core/lv_obj_scroll.d \
./CODE/lvgl/src/core/lv_obj_style.d \
./CODE/lvgl/src/core/lv_obj_style_gen.d \
./CODE/lvgl/src/core/lv_obj_tree.d \
./CODE/lvgl/src/core/lv_refr.d \
./CODE/lvgl/src/core/lv_theme.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/lvgl/src/core/%.src: ../CODE/lvgl/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/car/2022.7.28  bisaichengxu_zanding/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --io-streams --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=0 --compact-max-size=500 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<" -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/lvgl/src/core/%.o: ./CODE/lvgl/src/core/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


